#!/usr/bin/env python3
from collections import deque
from math import atan2, cos, sin, hypot

import numpy as np
import rclpy
from rclpy.node import Node
from rclpy.time import Time
from sensor_msgs.msg import Image, CameraInfo
from geometry_msgs.msg import Twist
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener


def rotation_matrix(q):
    x, y, z, w = q.x, q.y, q.z, q.w
    return np.array([
        [1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)],
        [2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)],
        [2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)]])


class TruckFollower(Node):
    def __init__(self):
        super().__init__("truck_follower")

        self.declare_parameter('~/linear_vel', 0.4)
        self.declare_parameter('~/target_distance', 2.5)
        self.declare_parameter('~/k_distance', 0.15)
        self.declare_parameter('~/k_angle', 0.3)
        self.declare_parameter('~/approach_limit', 0.04)
        self.declare_parameter('~/arm_position', 1.5)
        self.declare_parameter('~/shore_percentile', 50.0)
        self.declare_parameter('~/base_frame', 'VSV/base')
        self.declare_parameter('~/world_frame', 'world')
        self.linear_vel_ = self.get_parameter('~/linear_vel').get_parameter_value().double_value
        self.target_distance_ = self.get_parameter('~/target_distance').get_parameter_value().double_value
        self.k_distance_ = self.get_parameter('~/k_distance').get_parameter_value().double_value
        self.k_angle_ = self.get_parameter('~/k_angle').get_parameter_value().double_value
        self.approach_limit_ = self.get_parameter('~/approach_limit').get_parameter_value().double_value
        self.arm_position_ = self.get_parameter('~/arm_position').get_parameter_value().double_value
        self.shore_percentile_ = self.get_parameter('~/shore_percentile').get_parameter_value().double_value
        self.base_frame_ = self.get_parameter('~/base_frame').get_parameter_value().string_value
        self.world_frame_ = self.get_parameter('~/world_frame').get_parameter_value().string_value

        self.focal = None
        self.depth = None
        # Puntos de orilla ya vistos, en el mundo: unos 10 m de recorrido
        self.shore = deque(maxlen=200)

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        self.twist_pub_ = self.create_publisher(Twist, "~/twist", 1)
        self.info_sub_ = self.create_subscription(CameraInfo, "~/camera_info", self.info_callback, 1)
        self.depth_sub_ = self.create_subscription(Image, "~/depth", self.depth_callback, 1)
        self.image_sub_ = self.create_subscription(Image, "~/image", self.image_callback, 1)

    def info_callback(self, info):
        self.focal = info.k[4]
        self.center = info.k[5]

    def depth_callback(self, data):
        # El simulador publica la profundidad con las filas al reves que la imagen
        self.depth = np.frombuffer(data.data, dtype=np.float32)[::-1]

    def image_callback(self, data):
        if self.focal is None or self.depth is None:
            return
        try:
            sensor = self.tf_buffer.lookup_transform(self.base_frame_, data.header.frame_id, Time())
            base = self.tf_buffer.lookup_transform(self.world_frame_, self.base_frame_, Time())
        except TransformException:
            return

        # El laser barre el suelo de lado a lado unos metros por delante del camion.
        # Cada pixel se lleva al marco del camion: x hacia delante, y hacia la izquierda
        rgb = np.frombuffer(data.data, dtype=np.uint8).reshape(-1, 3).astype(np.float32)
        rows = np.arange(rgb.shape[0]) - self.center
        points = np.stack([np.zeros_like(self.depth), self.depth * rows / self.focal, self.depth], axis=1)
        t = sensor.transform.translation
        points = points @ rotation_matrix(sensor.transform.rotation).T + np.array([t.x, t.y, t.z])
        ahead = points[:, 0]
        right = -points[:, 1]

        # La tierra es verde o marron (poco azul), las baldosas del lago son grises.
        # La orilla es la primera tierra a la derecha del eje del camion
        earth = (rgb[:, 2] < 0.65 * rgb[:, 1]) & (right > 0)
        # Una orilla muy lejana (entrada estrecha del lago) no debe tirar del camion
        far_limit = self.target_distance_ + 1.5
        far = far_limit
        far_ahead = float(np.median(ahead))
        if earth.any():
            i = np.argmin(np.where(earth, right, np.inf))
            far = min(float(right[i]), far_limit)
            far_ahead = float(ahead[i])

        # Ese punto se guarda en el mundo: cuando el camion avance dara la distancia
        # a la orilla a la altura del brazo
        bx = base.transform.translation.x
        by = base.transform.translation.y
        q = base.transform.rotation
        yaw = atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z))
        c, s = cos(yaw), sin(yaw)
        wx = bx + c * far_ahead + s * far
        wy = by + s * far_ahead - c * far
        if not self.shore or hypot(wx - self.shore[-1][0], wy - self.shore[-1][1]) > 0.05:
            self.shore.append((wx, wy))
        seen = np.array(self.shore) - np.array([bx, by])
        seen_ahead = c * seen[:, 0] + s * seen[:, 1]
        seen_right = s * seen[:, 0] - c * seen[:, 1]
        beside = np.abs(seen_ahead - self.arm_position_) < 2.0
        # La mediana ignora las entradas y los salientes mas estrechos que la ventana.
        # Un percentil mas bajo aleja el camion de los salientes de tierra
        near = float(np.percentile(seen_right[beside], self.shore_percentile_)) if beside.any() else far

        # y: distancia lateral a la orilla junto al brazo. theta: angulo de la orilla
        # respecto al camion, de la recta entre ese punto y el que ve ahora el laser
        y = near - self.target_distance_
        theta = atan2(far - near, far_ahead - self.arm_position_)
        out = Twist()
        out.linear.x = self.linear_vel_
        # Orilla lejos o que se aleja: girar a la derecha (angular.z negativo)
        out.angular.z = -self.k_distance_ * y - self.k_angle_ * theta
        # Hacia la orilla se gira poco, alejarse de ella no tiene limite
        out.angular.z = max(out.angular.z, -self.approach_limit_)
        self.twist_pub_.publish(out)


def main(args=None):
    rclpy.init(args=args)

    follower = TruckFollower()

    rclpy.spin(follower)

    follower.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

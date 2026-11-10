#!/usr/bin/env python3

import pytorch_models_base.venv_hack
from pytorch_models_base.model import CNNModel

import rclpy
from rclpy.node import Node
from rclpy.time import Time

from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener

import torch
import numpy as np

import cv2
# cv_bridge2 is a local version of cv_bridge compiled with numpy 2
from cv_bridge2 import CvBridge

# Planos de recorte de la kinect en la escena
KINECT_NEAR = 0.2
KINECT_FAR = 3.5


class ArmFollower(Node):
    def __init__(self):
        super().__init__("arm_follower")

        self.declare_parameter('~/model', "")
        self.declare_parameter('~/dropout', 0.2)
        self.declare_parameter('~/lateral_vel', 0.5)
        self.declare_parameter('~/target_height', 0.4)
        self.declare_parameter('~/height_gain', 1.0)
        self.declare_parameter('~/vertical_vel', 0.3)
        self.declare_parameter('~/max_reach', 3.9)
        self.declare_parameter('~/base_frame', 'VSV/base')
        self.declare_parameter('~/tool_frame', 'VSV/Tool')
        self.model_ = self.get_parameter('~/model').get_parameter_value().string_value
        self.dropout = self.get_parameter('~/dropout').get_parameter_value().double_value
        self.lateral_vel_ = self.get_parameter('~/lateral_vel').get_parameter_value().double_value
        self.target_height_ = self.get_parameter('~/target_height').get_parameter_value().double_value
        self.height_gain_ = self.get_parameter('~/height_gain').get_parameter_value().double_value
        self.vertical_vel_ = self.get_parameter('~/vertical_vel').get_parameter_value().double_value
        self.max_reach_ = self.get_parameter('~/max_reach').get_parameter_value().double_value
        self.base_frame_ = self.get_parameter('~/base_frame').get_parameter_value().string_value
        self.tool_frame_ = self.get_parameter('~/tool_frame').get_parameter_value().string_value

        self.lateral = 0.0
        self.vertical = 0.0
        self.last_lateral = -1e10
        self.last_depth = -1e10

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        self.br = CvBridge()
        self.twist_pub_ = self.create_publisher(Twist, "~/twist", 1)
        if self.model_ != "":
            self.load_model()
            self.image_sub_ = self.create_subscription(Image, "~/image", self.image_callback, 1)
        else:
            # Sin modelo estamos grabando la demostracion: el lateral lo pone la persona
            self.get_logger().info("No model: lateral command taken from the joystick")
            self.teleop_sub_ = self.create_subscription(Twist, "~/teleop_twist", self.teleop_callback, 1)
        self.depth_sub_ = self.create_subscription(Image, "~/depth", self.depth_callback, 1)
        self.timer = self.create_timer(0.05, self.timer_callback)

    def now(self):
        return self.get_clock().now().nanoseconds / 1e9

    def load_model(self):
        device = torch.device('cpu')
        self.get_logger().info("Loding pytorch model '" + self.model_ + "'")
        self.model = CNNModel(3, 3, self.dropout)
        self.model.load_state_dict(torch.load(self.model_, weights_only=True, map_location=device))
        self.model.eval()
        self.get_logger().info("Model loaded, ready to run")

    def image_callback(self, data):
        # Objetivo 2a. Misma preparacion que en el entrenamiento: BGR, 32x32, entre 0 y 1
        raw = self.br.imgmsg_to_cv2(data, "bgr8")
        img = cv2.resize(raw, (0, 0), fx=32.0 / data.height, fy=32.0 / data.width, interpolation=cv2.INTER_AREA)
        img = np.rollaxis(np.expand_dims(img, axis=0), 3, 1)
        img = torch.from_numpy(img.astype(np.float32) / 255.)
        with torch.no_grad():
            res = self.model(img).numpy()
        # Clases del grabador: 0 hacia el camion, 1 quieto, 2 hacia fuera.
        # La esperanza de la orden suaviza el control frente al argmax
        self.lateral = self.lateral_vel_ * float(res[0, 2] - res[0, 0])
        self.last_lateral = self.now()

    def teleop_callback(self, twist):
        self.lateral = twist.linear.x
        self.last_lateral = self.now()

    def depth_callback(self, data):
        # Objetivo 2b. La kinect mira hacia abajo: su profundidad es la altura sobre el suelo
        depth = np.frombuffer(data.data, dtype=np.float32)
        valid = depth[(depth > KINECT_NEAR + 0.01) & (depth < KINECT_FAR - 0.01)]
        if valid.size < depth.size / 2:
            # Lo que queda mas cerca que el plano cercano no se ve: subir
            self.vertical = self.vertical_vel_
        else:
            # Manda lo mas cercano de la imagen, asi la herramienta sube antes de un obstaculo
            closest = float(np.percentile(valid, 5))
            self.vertical = float(np.clip(self.height_gain_ * (self.target_height_ - closest),
                                          -self.vertical_vel_, self.vertical_vel_))
        self.last_depth = self.now()

    def timer_callback(self):
        out = Twist()
        now = self.now()
        # Una medida vieja no debe seguir moviendo el brazo
        if now - self.last_lateral < 0.5:
            out.linear.x = self.lateral
        if now - self.last_depth < 0.5:
            out.linear.z = self.vertical
        # Estirado del todo el brazo ya no puede subir: cerca del limite no se aleja mas
        try:
            t = self.tf_buffer.lookup_transform(self.base_frame_, self.tool_frame_, Time())
            if -t.transform.translation.y > self.max_reach_:
                out.linear.x = min(out.linear.x, 0.0)
        except TransformException:
            pass
        self.twist_pub_.publish(out)


def main(args=None):
    rclpy.init(args=args)

    follower = ArmFollower()

    rclpy.spin(follower)

    follower.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

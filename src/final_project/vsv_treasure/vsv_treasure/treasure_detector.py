#!/usr/bin/env python3
from collections import deque
from math import hypot

import numpy as np
import rclpy
from rclpy.node import Node
from rclpy.time import Time
from std_msgs.msg import Float32
from visualization_msgs.msg import Marker, MarkerArray
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener


class TreasureDetector(Node):
    def __init__(self):
        super().__init__("treasure_detector")

        self.declare_parameter('~/threshold', 0.2)
        self.declare_parameter('~/merge_distance', 3.0)
        # Modelo del detector en el script de la escena: exp(-d^2 / (2 sigma^2)) + U(0, noise)
        self.declare_parameter('~/sigma', 2.0)
        self.declare_parameter('~/noise', 0.1)
        self.declare_parameter('~/grid_step', 0.1)
        self.declare_parameter('~/grid_margin', 5.0)
        self.declare_parameter('~/world_frame', 'world')
        self.declare_parameter('~/tool_frame', 'VSV/Tool')
        self.threshold_ = self.get_parameter('~/threshold').get_parameter_value().double_value
        self.merge_distance_ = self.get_parameter('~/merge_distance').get_parameter_value().double_value
        self.sigma_ = self.get_parameter('~/sigma').get_parameter_value().double_value
        self.noise_ = self.get_parameter('~/noise').get_parameter_value().double_value
        self.grid_step_ = self.get_parameter('~/grid_step').get_parameter_value().double_value
        self.grid_margin_ = self.get_parameter('~/grid_margin').get_parameter_value().double_value
        self.world_frame_ = self.get_parameter('~/world_frame').get_parameter_value().string_value
        self.tool_frame_ = self.get_parameter('~/tool_frame').get_parameter_value().string_value

        # Ultimos 5 s de medidas (x, y, z, valor): las de antes de un paso tambien informan
        self.recent = deque(maxlen=100)
        self.samples = None
        self.above = 0
        self.below = 0
        # Objetos localizados: {'x', 'y', 'peak', 'samples' con todas sus medidas}
        self.treasures = []

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        self.marker_pub_ = self.create_publisher(MarkerArray, "~/markers", 1)
        self.detector_sub_ = self.create_subscription(Float32, "~/detector", self.detector_callback, 10)
        self.timer = self.create_timer(1.0, self.publish_markers)

    def detector_callback(self, msg):
        try:
            t = self.tf_buffer.lookup_transform(self.world_frame_, self.tool_frame_, Time())
        except TransformException:
            return
        p = t.transform.translation
        sample = (p.x, p.y, p.z, msg.data)
        # Parado en el mismo sitio no se acumulan medidas
        if self.recent and hypot(p.x - self.recent[-1][0], p.y - self.recent[-1][1]) < 0.01:
            return
        self.recent.append(sample)
        if self.samples is None:
            if msg.data > self.threshold_:
                self.samples = list(self.recent)
                self.above = 1
                self.below = 0
            return
        self.samples.append(sample)
        if msg.data > self.threshold_:
            self.above += 1
            self.below = 0
        else:
            # El ruido puede hundir una medida suelta: el paso acaba tras 20 medidas por debajo
            self.below += 1
            if self.below > 20:
                self.end_of_pass()

    def model(self, d2):
        # Valor esperado del detector a una distancia d: el ruido suma en media noise / 2
        return np.minimum(np.exp(-d2 / (2 * self.sigma_ ** 2)) + self.noise_ / 2, 1.0)

    def vote(self, samples):
        # Modelo inverso por votacion: cada punto del suelo cerca del paso recibe el error
        # cuadratico entre las medidas y lo que el detector habria medido con el objeto alli.
        # Gana el punto que mejor explica todas las medidas, aunque la herramienta no pasara encima
        x, y, z, v = samples.T
        gx = np.arange(x.min() - self.grid_margin_, x.max() + self.grid_margin_, self.grid_step_)
        gy = np.arange(y.min() - self.grid_margin_, y.max() + self.grid_margin_, self.grid_step_)
        GX, GY = np.meshgrid(gx, gy, indexing='ij')
        sse = np.zeros(GX.shape)
        for xi, yi, zi, vi in samples:
            sse += (vi - self.model((GX - xi) ** 2 + (GY - yi) ** 2 + zi ** 2)) ** 2
        k = np.unravel_index(np.argmin(sse), sse.shape)
        return gx[k[0]], gy[k[1]], np.sqrt(sse[k] / len(samples))

    def end_of_pass(self):
        samples = np.array(self.samples)
        above = self.above
        self.samples = None
        if above < 10:
            # Unas pocas medidas sueltas sobre el umbral son ruido del detector
            return
        x, y, rms = self.vote(samples)
        peak = samples[:, 3].max()

        for i, known in enumerate(self.treasures):
            if hypot(x - known['x'], y - known['y']) < self.merge_distance_:
                # Mismo objeto visto en otra vuelta: se vuelve a votar con las medidas de todos los pasos
                known['samples'] = np.vstack([known['samples'], samples])
                known['x'], known['y'], rms = self.vote(known['samples'])
                known['peak'] = max(known['peak'], peak)
                self.get_logger().info("Treasure %d seen again, now at (%.2f, %.2f), %d measurements, fit error %.3f" % (
                    i + 1, known['x'], known['y'], len(known['samples']), rms))
                break
        else:
            self.treasures.append({'x': x, 'y': y, 'peak': peak, 'samples': samples})
            self.get_logger().info("Treasure %d found at (%.2f, %.2f), peak %.2f, %d measurements, fit error %.3f" % (
                len(self.treasures), x, y, peak, len(samples), rms))
        self.publish_markers()

    def publish_markers(self):
        markers = MarkerArray()
        stamp = self.get_clock().now().to_msg()
        for i, known in enumerate(self.treasures):
            x, y, peak = known['x'], known['y'], known['peak']
            m = Marker()
            m.header.frame_id = self.world_frame_
            m.header.stamp = stamp
            m.ns = "treasure"
            m.id = i
            m.type = Marker.CYLINDER
            m.action = Marker.ADD
            m.pose.position.x = x
            m.pose.position.y = y
            m.pose.position.z = 0.5
            m.pose.orientation.w = 1.0
            m.scale.x = 0.6
            m.scale.y = 0.6
            m.scale.z = 1.0
            m.color.r = 1.0
            m.color.g = 0.1
            m.color.b = 0.1
            m.color.a = 0.9
            markers.markers.append(m)

            label = Marker()
            label.header = m.header
            label.ns = "treasure_label"
            label.id = i
            label.type = Marker.TEXT_VIEW_FACING
            label.action = Marker.ADD
            label.pose.position.x = x
            label.pose.position.y = y
            label.pose.position.z = 2.0
            label.pose.orientation.w = 1.0
            label.scale.z = 1.0
            label.color.r = 1.0
            label.color.g = 1.0
            label.color.b = 1.0
            label.color.a = 1.0
            label.text = "%d (%.1f, %.1f) peak %.2f" % (i + 1, x, y, peak)
            markers.markers.append(label)
        self.marker_pub_.publish(markers)


def main(args=None):
    rclpy.init(args=args)

    detector = TreasureDetector()

    rclpy.spin(detector)

    detector.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

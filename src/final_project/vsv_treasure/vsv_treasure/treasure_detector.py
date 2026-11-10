#!/usr/bin/env python3
from math import hypot

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

        self.declare_parameter('~/threshold', 0.3)
        self.declare_parameter('~/merge_distance', 3.0)
        self.declare_parameter('~/world_frame', 'world')
        self.declare_parameter('~/tool_frame', 'VSV/Tool')
        self.threshold_ = self.get_parameter('~/threshold').get_parameter_value().double_value
        self.merge_distance_ = self.get_parameter('~/merge_distance').get_parameter_value().double_value
        self.world_frame_ = self.get_parameter('~/world_frame').get_parameter_value().string_value
        self.tool_frame_ = self.get_parameter('~/tool_frame').get_parameter_value().string_value

        # Medidas (x, y, valor) del paso en curso por encima del umbral
        self.samples = []
        self.below = 0
        # Objetos ya localizados: [x, y, peso acumulado, valor maximo]
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
        x = t.transform.translation.x
        y = t.transform.translation.y
        if msg.data > self.threshold_:
            self.below = 0
            # Parado sobre el objeto no se acumulan medidas: sesgarian la media
            if not self.samples or hypot(x - self.samples[-1][0], y - self.samples[-1][1]) > 0.02:
                self.samples.append((x, y, msg.data))
        elif self.samples:
            # El ruido puede hundir una medida suelta: el paso acaba tras 1 s por debajo
            self.below += 1
            if self.below > 20:
                self.end_of_pass()

    def end_of_pass(self):
        # Todas las medidas del paso se funden en una sola estimacion: la media de las
        # posiciones de la herramienta, pesada por lo que la senal supera al umbral
        weight = sum(v - self.threshold_ for _, _, v in self.samples)
        x = sum(px * (v - self.threshold_) for px, _, v in self.samples) / weight
        y = sum(py * (v - self.threshold_) for _, py, v in self.samples) / weight
        peak = max(v for _, _, v in self.samples)
        count = len(self.samples)
        self.samples = []
        self.below = 0
        if count < 10:
            # Unas pocas medidas sueltas sobre el umbral son ruido del detector
            return

        for i, known in enumerate(self.treasures):
            if hypot(x - known[0], y - known[1]) < self.merge_distance_:
                # Mismo objeto visto en otra vuelta: se promedia con lo anterior
                total = known[2] + weight
                known[0] = (known[0] * known[2] + x * weight) / total
                known[1] = (known[1] * known[2] + y * weight) / total
                known[2] = total
                known[3] = max(known[3], peak)
                self.get_logger().info("Treasure %d seen again, now at (%.2f, %.2f)" % (i + 1, known[0], known[1]))
                break
        else:
            self.treasures.append([x, y, weight, peak])
            self.get_logger().info("Treasure %d found at (%.2f, %.2f), peak %.2f, %d measurements" % (
                len(self.treasures), x, y, peak, count))
        self.publish_markers()

    def publish_markers(self):
        markers = MarkerArray()
        stamp = self.get_clock().now().to_msg()
        for i, (x, y, _, peak) in enumerate(self.treasures):
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

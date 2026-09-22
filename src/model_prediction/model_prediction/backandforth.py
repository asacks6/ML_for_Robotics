#!/usr/bin/env python3
import random
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, TwistStamped


def build_demo_program():
    segments = []

    def hold(value, duration, noise=0.0):
        segments.append((duration, value, value, noise))

    def ramp(start, end, duration):
        segments.append((duration, start, end, 0.0))

    def sweep(value, duration):
        hold(value, duration)
        hold(-value, duration)
        hold(0.0, 0.6)

    hold(0.0, 1.5)
    sweep(0.5, 0.7)
    sweep(1.0, 0.45)
    sweep(0.25, 1.0)

    for a in (1.0, -1.0, 0.6, -0.6):
        hold(a, 0.25)
        hold(0.0, 0.9)

    ramp(0.0, 0.8, 0.8)
    ramp(0.8, -0.8, 1.0)
    ramp(-0.8, 0.0, 0.8)
    hold(0.0, 0.8)

    for i in range(12):
        hold(0.7 if i % 2 == 0 else -0.7, 0.35)
    hold(0.0, 1.2)

    hold(0.0, 10.0, 0.35)
    hold(0.0, 2.0)
    return segments


def build_program(seed):
    rng = random.Random(seed)
    segments = []

    def hold(value, duration, noise=0.0):
        segments.append((duration, value, value, noise))

    def ramp(start, end, duration):
        segments.append((duration, start, end, 0.0))

    hold(0.0, 2.0)

    levels = [0.5, -0.5, 1.0, -1.0, 0.25, -0.75]
    rng.shuffle(levels)
    for v in levels:
        hold(v, 3.0)
        hold(0.0, 2.5)

    for i in range(10):
        hold(0.8 if i % 2 == 0 else -0.8, 0.6)
    hold(0.0, 2.0)

    bursts = [1.0, -1.0, 0.6, -0.6, 0.35, -0.35]
    rng.shuffle(bursts)
    for a in bursts:
        hold(a, 0.25)
        hold(0.0, 1.5)

    ramp(0.0, 1.0, 5.0)
    ramp(1.0, -1.0, 8.0)
    ramp(-1.0, 0.4, 4.0)
    hold(0.4, 1.0)
    ramp(0.4, 0.0, 2.0)

    for _ in range(45):
        hold(rng.uniform(-1.0, 1.0), rng.uniform(0.25, 2.0))

    hold(0.0, 2.0)
    hold(0.45, 12.0, 0.2)
    hold(-0.45, 12.0, 0.2)
    hold(0.0, 8.0, 0.25)

    period = 2.4
    while period > 0.25:
        hold(0.7, period / 2.0)
        hold(-0.7, period / 2.0)
        period *= 0.75

    hold(0.0, 3.0)
    return segments


class BackAndForth(Node):
    def __init__(self):
        super().__init__("back_and_forth")
        self.declare_parameter("rate", 50.0)
        self.declare_parameter("seed", 1)
        self.declare_parameter("loop", False)
        self.declare_parameter("mode", "identification")

        self.rate = self.get_parameter("rate").value
        self.seed = self.get_parameter("seed").value
        self.loop = self.get_parameter("loop").value
        self.mode = self.get_parameter("mode").value

        if self.mode == "demo":
            self.segments = build_demo_program()
        else:
            self.segments = build_program(self.seed)
        self.duration = sum(s[0] for s in self.segments)
        self.rng = random.Random(self.seed + 7919)

        self.pub = self.create_publisher(Twist, "/vrep/twistCommand", 1)
        self.create_subscription(TwistStamped, "/vrep/localTwist", self.state_cb, 1)
        self.last_state = None
        self.armed = False
        self.t0 = self.get_clock().now().nanoseconds / 1e9
        self.timer = self.create_timer(1.0 / self.rate, self.timer_cb)
        self.get_logger().info("%s program, seed %d, duration %.1f s at %.1f Hz"
                               % (self.mode, self.seed, self.duration, self.rate))

    def value_at(self, t):
        for duration, start, end, noise in self.segments:
            if t < duration:
                v = start + (end - start) * (t / duration)
                if noise > 0.0:
                    v += self.rng.gauss(0.0, noise)
                return max(-1.0, min(1.0, v))
            t -= duration
        return 0.0

    def state_cb(self, msg):
        self.last_state = self.get_clock().now().nanoseconds / 1e9

    def timer_cb(self):
        now = self.get_clock().now().nanoseconds / 1e9
        twist = Twist()

        if self.last_state is None or now - self.last_state > 0.5:
            if self.armed:
                self.armed = False
                self.get_logger().info("simulation stopped, holding at zero")
            self.t0 = now
            self.pub.publish(twist)
            return

        if not self.armed:
            self.armed = True
            self.t0 = now
            self.get_logger().info("simulation running, starting program")

        t = now - self.t0
        if t > self.duration:
            if self.loop:
                self.t0 = now
                t = 0.0
            else:
                self.pub.publish(twist)
                self.get_logger().info("program complete")
                raise SystemExit
        twist.linear.x = self.value_at(t)
        self.pub.publish(twist)


def main(args=None):
    rclpy.init(args=args)

    driver = BackAndForth()

    try:
        rclpy.spin(driver)
    except SystemExit:
        pass

    driver.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

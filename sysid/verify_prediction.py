#!/usr/bin/env python3
import sys

import numpy as np
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped

TS = 0.02


class Verifier(Node):
    def __init__(self, duration):
        super().__init__('prediction_verifier')
        self.duration = duration
        self.meas = []
        self.pred = []
        self.cmd = []
        self.create_subscription(TwistStamped, '/vrep/localTwist',
                                 lambda m: self.meas.append(self.row(m)), 50)
        self.create_subscription(TwistStamped, '/vrep/commandTwist',
                                 lambda m: self.cmd.append(self.row(m)), 50)
        self.create_subscription(TwistStamped, '/predict/twist_prediction',
                                 lambda m: self.pred.append(self.row(m)), 50)
        self.t0 = self.get_clock().now().nanoseconds / 1e9
        self.create_timer(1.0, self.tick)

    @staticmethod
    def row(msg):
        return (msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9, msg.twist.linear.x)

    def tick(self):
        if self.get_clock().now().nanoseconds / 1e9 - self.t0 < self.duration:
            return
        if len(self.pred) < 10 or len(self.meas) < 10:
            print('not enough data: %d predictions, %d measurements'
                  % (len(self.pred), len(self.meas)))
            raise SystemExit(1)
        meas = np.array(self.meas)
        pred = np.array(self.pred)
        cmd = np.array(self.cmd)

        start = max(meas[0, 0], pred[0, 0]) + 1.0
        stop = min(meas[-1, 0], pred[-1, 0]) - 1.0
        t = np.arange(start, stop, TS)
        y = np.interp(t, meas[:, 0], meas[:, 1])
        u = np.interp(t, cmd[:, 0], cmd[:, 1]) if len(cmd) > 2 else np.zeros_like(t)
        p = np.interp(t, pred[:, 0] + TS, pred[:, 1])

        def fit(ref, est):
            return 100.0 * (1.0 - np.linalg.norm(ref - est) / np.linalg.norm(ref - ref.mean()))

        print('samples compared : %d over %.1f s' % (len(t), t[-1] - t[0]))
        print('prediction rate  : %.1f Hz' % (len(pred) / (pred[-1, 0] - pred[0, 0])))
        print('fit prediction   : %6.2f %%   rmse %.4f'
              % (fit(y, p), float(np.sqrt(np.mean((y - p) ** 2)))))
        print('fit command      : %6.2f %%   rmse %.4f'
              % (fit(y, u), float(np.sqrt(np.mean((y - u) ** 2)))))
        raise SystemExit(0)


def main():
    duration = float(sys.argv[1]) if len(sys.argv) > 1 else 40.0
    rclpy.init()
    try:
        rclpy.spin(Verifier(duration))
    except SystemExit as exc:
        sys.exit(exc.code)


if __name__ == '__main__':
    main()

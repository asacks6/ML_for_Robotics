import os
import sys, math, time, random
import numpy as np
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import tf2_ros

# Recorrido aleatorio por el lecho del lago para grabar el dataset del suelo
# usage: tour.py labels_file max_per_class [seed]
labels_file, max_per_class = sys.argv[1], int(sys.argv[2])
rng = random.Random(int(sys.argv[3]) if len(sys.argv) > 3 else 0)
G = np.load(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'geom.npz'))
D, X0, RES = G['D'], float(G['X0']), float(G['RES'])
OBST = [(-3.47, 2.05), (13.8, -3.63), (14.9, 3.25), (4.15, 12.27), (-7.75, 3.72), (0.0, 0.0), (-5.43, 11.25), (0.0, 9.02)]


def dist(x, y):
    i, j = int(round((y - X0) / RES)), int(round((x - X0) / RES))
    if 0 <= i < D.shape[0] and 0 <= j < D.shape[1]:
        return D[i, j]
    return 0.0


def clear(p, q, m=0.7):
    n = int(math.hypot(q[0] - p[0], q[1] - p[1]) / 0.1) + 1
    return all(dist(p[0] + (q[0] - p[0]) * k / n, p[1] + (q[1] - p[1]) * k / n) >= m for k in range(n + 1))


class Tour(Node):
    def __init__(self):
        super().__init__('tour')
        self.buf = tf2_ros.Buffer()
        self.tl = tf2_ros.TransformListener(self.buf, self)
        self.pub = self.create_publisher(Twist, '/vrep/twistCommand', 1)
        self.target = None
        self.t0 = time.time()
        self.last_print = 0
        self.create_timer(0.1, self.step)

    def counts(self):
        try:
            labs = [l.split()[1] for l in open(labels_file)]
        except Exception:
            return 0, 0
        return labs.count('0'), labs.count('1')

    def pick(self, x, y):
        for _ in range(2000):
            if rng.random() < 0.35:
                ox, oy = rng.choice(OBST)
                a, r = rng.uniform(0, 2 * math.pi), rng.uniform(1.3, 2.5)
                tx, ty = ox + r * math.cos(a), oy + r * math.sin(a)
            else:
                a, r = rng.uniform(0, 2 * math.pi), rng.uniform(3, 10)
                tx, ty = x + r * math.cos(a), y + r * math.sin(a)
            if dist(tx, ty) >= 1.0 and clear((x, y), (tx, ty)):
                return tx, ty
        return None

    def step(self):
        try:
            t = self.buf.lookup_transform('world', 'bubbleRob', rclpy.time.Time())
        except Exception:
            return
        x, y = t.transform.translation.x, t.transform.translation.y
        q = t.transform.rotation
        yaw = math.atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z))
        if time.time() - self.last_print > 20:
            self.last_print = time.time()
            print('t=%.0f pos (%.1f,%.1f) counts untrav/trav %s' % (time.time() - self.t0, x, y, self.counts()), flush=True)
            if min(self.counts()) >= max_per_class:
                self.pub.publish(Twist())
                raise SystemExit
        if self.target is None or math.hypot(self.target[0] - x, self.target[1] - y) < 0.5:
            self.target = self.pick(x, y)
            if self.target is None:
                self.get_logger().error('no target')
                return
        err = math.atan2(self.target[1] - y, self.target[0] - x) - yaw
        err = math.atan2(math.sin(err), math.cos(err))
        m = Twist()
        m.angular.z = max(-0.6, min(0.6, 1.5 * err))
        m.linear.x = 0.5 * max(0.0, math.cos(err)) if abs(err) < 0.8 else 0.0
        self.pub.publish(m)


rclpy.init()
n = Tour()
try:
    rclpy.spin(n)
except SystemExit:
    pass
n.pub.publish(Twist())

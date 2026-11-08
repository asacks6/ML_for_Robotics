import sys, math, json, time
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import tf2_ros

# usage: drive.py '[[x,y],...]' [v] [topic]
wps = json.loads(sys.argv[1])
v_max = float(sys.argv[2]) if len(sys.argv) > 2 else 0.5
topic = sys.argv[3] if len(sys.argv) > 3 else '/vrep/twistCommand'


class Drive(Node):
    def __init__(self):
        super().__init__('drive_wp')
        self.buf = tf2_ros.Buffer()
        self.tl = tf2_ros.TransformListener(self.buf, self)
        self.pub = self.create_publisher(Twist, topic, 1)
        self.i = 0
        self.t0 = time.time()
        self.create_timer(0.1, self.step)

    def step(self):
        try:
            t = self.buf.lookup_transform('world', 'bubbleRob', rclpy.time.Time())
        except Exception:
            return
        x, y = t.transform.translation.x, t.transform.translation.y
        q = t.transform.rotation
        yaw = math.atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z))
        tx, ty = wps[self.i]
        d = math.hypot(tx - x, ty - y)
        if d < 0.5:
            print(f'reached wp {self.i} ({tx},{ty}) at t={time.time()-self.t0:.0f}s', flush=True)
            self.i += 1
            if self.i >= len(wps):
                self.pub.publish(Twist())
                raise SystemExit
            return
        err = math.atan2(ty - y, tx - x) - yaw
        err = math.atan2(math.sin(err), math.cos(err))
        m = Twist()
        m.angular.z = max(-0.6, min(0.6, 1.5 * err))
        m.linear.x = v_max * max(0.0, math.cos(err)) if abs(err) < 1.0 else 0.0
        self.pub.publish(m)


rclpy.init()
n = Drive()
try:
    rclpy.spin(n)
except SystemExit:
    pass

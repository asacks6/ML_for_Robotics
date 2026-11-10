#!/usr/bin/env python3
# Mide el factor de tiempo real del simulador y la frecuencia de las imagenes
import time
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from sensor_msgs.msg import Image

rclpy.init()
n = Node('rate_check')
st = []
cnt = {'k': 0, 'v': 0}
n.create_subscription(Float32, '/vrep/simTime', lambda m: st.append((time.time(), m.data)), 10)
n.create_subscription(Image, '/vrep/kision/image', lambda m: cnt.__setitem__('k', cnt['k'] + 1), 10)
n.create_subscription(Image, '/vrep/vision/image', lambda m: cnt.__setitem__('v', cnt['v'] + 1), 10)
t0 = time.time()
while time.time() - t0 < 6.0:
    rclpy.spin_once(n, timeout_sec=0.05)
if len(st) > 2:
    wall = st[-1][0] - st[0][0]
    sim = st[-1][1] - st[0][1]
    print('sim time %.1f s, real-time factor %.2f, sim steps %.1f Hz, kinect %.1f Hz, camera %.1f Hz' % (
        st[-1][1], sim / wall, (len(st) - 1) / wall, cnt['k'] / 6.0, cnt['v'] / 6.0))
else:
    print('no /vrep/simTime received: is the simulation running?')
n.destroy_node()
rclpy.shutdown()

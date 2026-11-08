import sys, math, time, signal, os
import numpy as np
import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist
from std_msgs.msg import Float32, Bool
import tf2_ros

# usage: record_demo.py mode(floor|shore) out.mp4|view duration_s [title] [speed] [dstar]
# Con 'view' en lugar de un fichero se muestra en una ventana y no se graba nada
mode, out, duration = sys.argv[1], sys.argv[2], float(sys.argv[3])
title = sys.argv[4] if len(sys.argv) > 4 else ''
SPEED = float(sys.argv[5]) if len(sys.argv) > 5 else 1.0
DSTAR = float(sys.argv[6]) if len(sys.argv) > 6 else 1.5
SP = os.path.dirname(os.path.abspath(__file__)) + '/'
G = np.load(SP + 'geom.npz')
X0, RES = float(G['X0']), float(G['RES'])
Do = np.load(SP + 'shore.npz')['Do']
P = 384
FPS = 10


def to_img(m):
    a = np.frombuffer(m.data, np.uint8).reshape(m.height, m.width, -1)
    if m.encoding == 'rgb8':
        a = cv2.cvtColor(a, cv2.COLOR_RGB2BGR)
    return cv2.resize(a, (P, P), interpolation=cv2.INTER_NEAREST)


def label(img, text, y=22, scale=0.55):
    cv2.putText(img, text, (8, y), cv2.FONT_HERSHEY_SIMPLEX, scale, (0, 0, 0), 3, cv2.LINE_AA)
    cv2.putText(img, text, (8, y), cv2.FONT_HERSHEY_SIMPLEX, scale, (255, 255, 255), 1, cv2.LINE_AA)


# Vista cenital del lago: suelo gris, orilla y obstaculos verdes, recortada a la zona util
# Mapa sin las personas (Bill camina por la escena)
H = G['H']
gg = X0 + RES * np.arange(H.shape[0])
GY, GX = np.meshgrid(gg, gg, indexing='ij')
free = H < 0
for (ox, oy, r) in [(-3.47, 2.05, 0.4), (0.0, 0.0, 0.2), (-5.43, 11.25, 0.45), (0.0, 9.02, 0.7), (4.95, 2.95, 0.45),
                    (15.38, -12.67, 0.45), (16.25, -3.22, 0.45), (18.02, -8.82, 0.45), (-5.45, 12.83, 0.9), (4.78, -0.10, 0.9),
                    (3.08, 7.33, 0.9), (18.0, -10.4, 0.9), (17.5, 10.7, 0.9), (1.62, 18.65, 0.9), (-14.62, -10.95, 0.9),
                    (11.28, 11.75, 0.9), (-0.15, 4.45, 0.9), (-0.12, -17.2, 0.9)]:
    free &= np.hypot(GX - ox, GY - oy) > r
base = np.zeros(free.shape + (3,), np.uint8)
base[free] = (190, 190, 190)
base[~free] = (60, 120, 60)
C0, C1 = int((-20 - X0) / RES), int((22 - X0) / RES)
base = cv2.resize(cv2.flip(base[C0:C1, C0:C1], 0), (P, P), interpolation=cv2.INTER_AREA)
SCALE = P / (C1 - C0)


def w2p(x, y):
    return int(((x - X0) / RES - C0) * SCALE), int((C1 - (y - X0) / RES) * SCALE)


class Rec(Node):
    def __init__(self):
        super().__init__('demo_recorder')
        self.buf = tf2_ros.Buffer()
        self.tl = tf2_ros.TransformListener(self.buf, self)
        self.raw = None
        self.lab = None
        self.cmd = None
        self.expert = None
        self.d = None
        self.ctrl = []
        self.traj = []
        self.dist = []
        self.create_subscription(Image, '/vrep/kision/image', lambda m: setattr(self, 'raw', to_img(m)), 1)
        if mode == 'floor':
            self.create_subscription(Image, '/floor_plane_classify/image_label', lambda m: setattr(self, 'lab', to_img(m)), 1)
        else:
            self.create_subscription(Twist, '/vrep/twistCommand', lambda m: setattr(self, 'cmd', m), 1)
            self.create_subscription(Bool, '/dagger/expert_ctrl', lambda m: setattr(self, 'expert', m.data), 1)
            self.create_subscription(Float32, '/dagger/distance', lambda m: setattr(self, 'd', m.data), 1)
        self.vw = None if out == 'view' else cv2.VideoWriter(out, cv2.VideoWriter_fourcc(*'avc1'), FPS * SPEED,
                                                             (3 * P if mode == 'floor' else 2 * P, P + 40))
        self.t0 = None
        self.sim_t = None
        self.last_frame = -1e9
        self.create_subscription(Float32, '/vrep/simTime', lambda m: setattr(self, 'sim_t', m.data), 1)
        self.create_timer(0.02, self.step)

    def step(self):
        # Un fotograma cada 0.1 s de tiempo simulado: el video va en tiempo de simulacion
        if self.raw is None or self.sim_t is None or (mode == 'floor' and self.lab is None):
            return
        if self.t0 is None:
            self.t0 = self.sim_t
        el = self.sim_t - self.t0
        if el - self.last_frame < 1.0 / FPS:
            return
        self.last_frame = el
        if el > duration:
            raise SystemExit
        try:
            t = self.buf.lookup_transform('world', 'bubbleRob', rclpy.time.Time())
            x, y = t.transform.translation.x, t.transform.translation.y
            q = t.transform.rotation
            yaw = math.atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z))
            self.traj.append((x, y))
            self.ctrl.append(bool(self.expert))
            i, j = int(round((y - X0) / RES)), int(round((x - X0) / RES))
            self.dist.append((el, float(self.d) if self.d is not None else float(Do[i, j])))
        except Exception:
            return
        m = base.copy()
        # Trayectoria azul cuando conduce la red, roja cuando el experto toma el control
        for k in range(1, len(self.traj)):
            cv2.line(m, w2p(*self.traj[k - 1]), w2p(*self.traj[k]), (0, 0, 230) if self.ctrl[k] else (200, 60, 0), 2, cv2.LINE_AA)
        px, py = w2p(x, y)
        for da in (-0.5, 0.5):
            cv2.line(m, (px, py), (int(px + 25 * math.cos(yaw + da)), int(py - 25 * math.sin(yaw + da))), (0, 200, 255), 1, cv2.LINE_AA)
        cv2.circle(m, (px, py), 5, (0, 0, 255), -1)
        label(m, 'Top view (ground truth pose)')
        cam = self.raw.copy()
        label(cam, 'Kinect RGB')
        if mode == 'floor':
            lab = self.lab.copy()
            label(lab, 'CNN: green = traversable, red = obstacle')
            row = np.hstack([cam, lab, m])
        else:
            w = self.cmd.angular.z if self.cmd else 0.0
            cx = P // 2
            cv2.rectangle(cam, (cx - 100, P - 30), (cx + 100, P - 14), (40, 40, 40), -1)
            cv2.rectangle(cam, (cx, P - 30), (int(cx - w / 0.4 * 100), P - 14), (0, 220, 255), -1)
            label(cam, 'turn command %+.2f rad/s' % w, y=P - 40, scale=0.5)
            if self.expert is not None:
                txt, col = ('EXPERT TAKEOVER', (0, 0, 220)) if self.expert else ('NETWORK DRIVING', (0, 170, 0))
                cv2.rectangle(cam, (P - 200, 34), (P - 6, 62), col, -1)
                cv2.putText(cam, txt, (P - 192, 55), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (255, 255, 255), 1, cv2.LINE_AA)
            d = self.dist[-1][1]
            label(m, 'distance to shore %.2f m (target %.1f)' % (d, DSTAR), y=P - 12, scale=0.5)
            row = np.hstack([cam, m])
        bar = np.zeros((40, row.shape[1], 3), np.uint8)
        label(bar, '%s   sim t = %5.1f s%s' % (title, el, '   (x%g speed)' % SPEED if SPEED != 1 else ''), y=27, scale=0.65)
        if self.vw is None:
            cv2.imshow('project 2', np.vstack([bar, row]))
            if cv2.waitKey(1) == 27:
                raise SystemExit
        else:
            self.vw.write(np.vstack([bar, row]))


rclpy.init()
n = Rec()
signal.signal(signal.SIGINT, lambda *a: (_ for _ in ()).throw(SystemExit()))
try:
    rclpy.spin(n)
except SystemExit:
    pass
if n.vw is not None:
    n.vw.release()
    np.save(out.replace('.mp4', '_dist.npy'), np.array(n.dist))
    np.save(out.replace('.mp4', '_traj.npy'), np.array(n.traj))
print('wrote' if n.vw is not None else 'shown', out, len(n.dist), 'frames')

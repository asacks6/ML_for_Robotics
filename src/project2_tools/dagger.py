import os
import argparse, math
import numpy as np
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from std_msgs.msg import Float32, Bool
import tf2_ros

# Supervisor: la red conduce (/net/twist), el experto etiqueta (/expert/twist) y
# toma el control si el robot se aleja demasiado. Sirve para DAgger y para evaluar.
ap = argparse.ArgumentParser()
ap.add_argument('--duration', type=float, default=1500, help='tiempo simulado maximo (s)')
ap.add_argument('--laps', type=float, default=0, help='parar tras N vueltas (0 = sin limite)')
ap.add_argument('--labels', default='', help='labels.txt del observe, para parar por cuenta')
ap.add_argument('--max', type=int, default=0, help='imagenes por clase para parar')
ap.add_argument('--dstar', type=float, default=1.5)
ap.add_argument('--field', default='shore.npz')
ap.add_argument('--side', type=int, default=1, help='1 orilla a la derecha, -1 a la izquierda')
ap.add_argument('--expert_only', action='store_true', help='el experto conduce siempre')
ap.add_argument('--kicks', action='store_true', help='golpes de direccion aleatorios del experto')
ap.add_argument('--seed', type=int, default=0)
ap.add_argument('--log', default='')
args = ap.parse_args()

SP = os.path.dirname(os.path.abspath(__file__)) + '/'
G = np.load(SP + 'geom.npz')
X0, RES = float(G['X0']), float(G['RES'])
SH = np.load(SP + args.field)
Do, gx, gy = SH['Do'], SH['gx'], SH['gy']
V, W_MAX = 0.3, 0.5
CX, CY = 3.6, 3.6
rng = np.random.default_rng(args.seed)


def at(a, x, y):
    i = min(max(int(round((y - X0) / RES)), 0), a.shape[0] - 1)
    j = min(max(int(round((x - X0) / RES)), 0), a.shape[1] - 1)
    return a[i, j]


class Supervisor(Node):
    def __init__(self):
        super().__init__('dagger')
        self.buf = tf2_ros.Buffer()
        self.tl = tf2_ros.TransformListener(self.buf, self)
        self.pub_exec = self.create_publisher(Twist, '/vrep/twistCommand', 1)
        self.pub_lab = self.create_publisher(Twist, '/expert/twist', 1)
        self.pub_ctrl = self.create_publisher(Bool, '/dagger/expert_ctrl', 1)
        self.pub_d = self.create_publisher(Float32, '/dagger/distance', 1)
        self.net = None
        self.create_subscription(Twist, '/net/twist', lambda m: setattr(self, 'net', m), 1)
        self.sim_t = None
        self.create_subscription(Float32, '/vrep/simTime', lambda m: setattr(self, 'sim_t', m.data), 1)
        self.t0 = None
        self.expert_ctrl = True
        self.engaged = False
        self.n_net = 0
        self.n_tot = 0
        self.takeovers = 0
        self.a_prev = None
        self.swept = 0.0
        self.rows = []
        self.hist = []
        self.t_engaged = 0.0
        self.next_kick = rng.uniform(4, 8)
        self.kick_end = 0.0
        self.kick = 0.0
        self.last_print = -1e9
        self.create_timer(0.05, self.step)

    def counts(self):
        try:
            labs = [l.split()[1] for l in open(args.labels)]
            return [labs.count(str(k)) for k in range(3)]
        except Exception:
            return [0, 0, 0]

    def step(self):
        if self.sim_t is None:
            return
        if self.t0 is None:
            self.t0 = self.sim_t
        el = self.sim_t - self.t0
        if el > args.duration or (args.laps > 0 and abs(self.swept) >= 2 * math.pi * args.laps):
            raise SystemExit
        try:
            t = self.buf.lookup_transform('world', 'bubbleRob', rclpy.time.Time())
        except Exception:
            return
        x, y = t.transform.translation.x, t.transform.translation.y
        q = t.transform.rotation
        yaw = math.atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z))
        d = at(Do, x, y)
        # Robot volcado o atascado: se termina la prueba y se anota el incidente
        tilt = math.degrees(math.acos(max(-1.0, min(1.0, 1 - 2 * (q.x * q.x + q.y * q.y)))))
        if tilt > 45:
            print('incident: robot flipped at (%.1f,%.1f) sim t=%.0f' % (x, y, el), flush=True)
            raise SystemExit
        self.hist.append((el, x, y))
        while self.hist and el - self.hist[0][0] > 60:
            self.hist.pop(0)
        if self.engaged and el - self.t_engaged > 60 and math.hypot(x - self.hist[0][1], y - self.hist[0][2]) < 0.2:
            print('incident: robot stuck at (%.1f,%.1f) sim t=%.0f' % (x, y, el), flush=True)
            raise SystemExit
        ax, ay = x + 0.4 * math.cos(yaw), y + 0.4 * math.sin(yaw)
        g = np.array([at(gx, ax, ay), at(gy, ax, ay)])
        g /= max(1e-6, np.linalg.norm(g))
        # Tangente a la orilla: g girado -90 (orilla a la derecha) o +90 (a la izquierda)
        tang = math.atan2(-args.side * g[0], args.side * g[1])
        psi = tang + args.side * max(-0.8, min(0.8, math.atan(1.0 * (args.dstar - d))))
        err = math.atan2(math.sin(psi - yaw), math.cos(psi - yaw))
        lab = Twist()
        lab.linear.x = V
        lab.angular.z = max(-W_MAX, min(W_MAX, 1.2 * err))
        if not self.engaged and abs(d - args.dstar) < 0.3 and abs(err) < 0.3:
            self.engaged = True
            self.t_engaged = el
            print('engaged at (%.1f,%.1f)' % (x, y), flush=True)
        if self.engaged:
            self.pub_lab.publish(lab)
        if self.expert_ctrl:
            if self.engaged and not args.expert_only and abs(d - args.dstar) < 0.3 and abs(err) < 0.3:
                self.expert_ctrl = False
        elif d > args.dstar + 1.5 or d < 0.7 or abs(err) > 1.3:
            self.expert_ctrl = True
            self.takeovers += 1
        if self.expert_ctrl or self.net is None:
            ex = Twist()
            ex.linear.x = V
            ex.angular.z = lab.angular.z
            if args.kicks and self.engaged:
                if el > self.next_kick:
                    self.kick = rng.choice([-1, 1]) * rng.uniform(0.3, 0.5)
                    self.kick_end = el + rng.uniform(0.8, 2.0)
                    self.next_kick = self.kick_end + rng.uniform(3, 7)
                if el < self.kick_end:
                    ex.angular.z = max(-0.6, min(0.6, ex.angular.z + self.kick))
            self.pub_exec.publish(ex)
        else:
            self.pub_exec.publish(self.net)
        self.pub_ctrl.publish(Bool(data=self.expert_ctrl))
        self.pub_d.publish(Float32(data=float(d)))
        if self.engaged:
            a = math.atan2(y - CY, x - CX)
            if self.a_prev is not None:
                self.swept += math.atan2(math.sin(a - self.a_prev), math.cos(a - self.a_prev))
            self.a_prev = a
            if not self.expert_ctrl:
                self.n_net += 1
            self.n_tot += 1
            self.rows.append((el, x, y, d, float(self.expert_ctrl), self.swept / (2 * math.pi)))
        if el - self.last_print > 30:
            self.last_print = el
            c = self.counts() if args.labels else None
            print('sim t=%.0f (%.1f,%.1f) d=%.2f laps %.2f net control %.0f %% takeovers %d counts %s'
                  % (el, x, y, d, self.swept / (2 * math.pi), 100.0 * self.n_net / max(1, self.n_tot),
                     self.takeovers, c), flush=True)
            if c and args.max and min(c) >= args.max:
                raise SystemExit


rclpy.init()
n = Supervisor()
try:
    rclpy.spin(n)
except (SystemExit, KeyboardInterrupt):
    pass
n.pub_exec.publish(Twist())
if args.log:
    np.save(args.log, np.array(n.rows))
print('final: laps %.2f, net control %.1f %%, takeovers %d' % (n.swept / (2 * math.pi), 100.0 * n.n_net / max(1, n.n_tot),
                                                               n.takeovers), flush=True)

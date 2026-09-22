#!/usr/bin/env python3
import sys
import time

import numpy as np

sys.path.insert(0, '/cs-share/pradalier/CoppeliaSim/programming/zmqRemoteApi/clients/python/src')
from coppeliasim_zmqremoteapi_client import RemoteAPIClient

OFFSET = np.array([0.0, -9.0, 4.5])
TAU = 2.0
PERIOD = 0.1


def look_at(eye, target):
    z = target - eye
    z = z / np.linalg.norm(z)
    x = np.cross([0.0, 0.0, 1.0], z)
    x = x / np.linalg.norm(x)
    y = np.cross(z, x)
    return [x[0], y[0], z[0], eye[0],
            x[1], y[1], z[1], eye[1],
            x[2], y[2], z[2], eye[2]]


def connect():
    sim = RemoteAPIClient().require('sim')

    for name in ('boolparam_console_visible', 'boolparam_statustext_open',
                 'boolparam_browser_visible', 'boolparam_hierarchy_visible'):
        if hasattr(sim, name):
            try:
                sim.setBoolParam(getattr(sim, name), False)
            except Exception:
                pass

    return sim, sim.getObject('/Quadcopter'), sim.getObject('/DefaultCamera')


def main():
    sim = None
    centre = None
    alpha = PERIOD / (TAU + PERIOD)

    while True:
        try:
            if sim is None:
                sim, drone, cam = connect()
                m = sim.getObjectMatrix(drone, -1)
                centre = np.array([m[3], m[7], m[11]])
            m = sim.getObjectMatrix(drone, -1)
            pos = np.array([m[3], m[7], m[11]])
            centre = centre + alpha * (pos - centre)
            sim.setObjectMatrix(cam, look_at(centre + OFFSET, centre), -1)
        except KeyboardInterrupt:
            return
        except Exception:
            sim = None
            time.sleep(1.0)
        time.sleep(PERIOD)


if __name__ == '__main__':
    main()

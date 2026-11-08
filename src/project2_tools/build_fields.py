import sys, os
import numpy as np
from scipy import ndimage

# Construye los campos de distancia a la orilla a partir de geom.npz (ver geom.py):
#   D_static.npy     distancia al obstaculo estatico mas cercano (orilla u objeto)
#   shore.npz        distancia a la orilla exterior (+ obstaculos a menos de 3 m de ella)
#   shore_island.npz distancia a la isla (+ obstaculos a menos de 3 m de ella)
# usage: build_fields.py [out_dir]
here = os.path.dirname(os.path.abspath(__file__))
out = sys.argv[1] if len(sys.argv) > 1 else here
G = np.load(os.path.join(here, 'geom.npz'))
H, X0, RES = G['H'], float(G['X0']), float(G['RES'])
# Obstaculos fijos (las personas caminan y no se incluyen)
STATIC = [(-3.47, 2.05, 0.4), (0.0, 0.0, 0.2), (-5.43, 11.25, 0.45), (0.0, 9.02, 0.7), (4.95, 2.95, 0.45),
          (15.38, -12.67, 0.45), (16.25, -3.22, 0.45), (18.02, -8.82, 0.45), (-5.45, 12.83, 0.9), (4.78, -0.10, 0.9),
          (3.08, 7.33, 0.9), (18.0, -10.4, 0.9), (17.5, 10.7, 0.9), (1.62, 18.65, 0.9), (-14.62, -10.95, 0.9),
          (11.28, 11.75, 0.9), (-0.15, 4.45, 0.9), (-0.12, -17.2, 0.9)]
g = X0 + RES * np.arange(H.shape[0])
GY, GX = np.meshgrid(g, g, indexing='ij')
free = H < 0
for (ox, oy, r) in STATIC:
    free &= np.hypot(GX - ox, GY - oy) > r
D = ndimage.distance_transform_edt(free) * RES
np.save(os.path.join(out, 'D_static.npy'), D)

lab, n = ndimage.label(~free, structure=np.ones((3, 3)))


def field(seed_cell, name):
    comp = lab == lab[seed_cell]
    d = ndimage.distance_transform_edt(~comp) * RES
    for k in range(1, n + 1):
        c = lab == k
        if not (c & comp).any() and d[c].min() < 3.0:
            comp |= c
    d = ndimage.distance_transform_edt(~comp) * RES
    d[comp] = 0
    gy, gx = np.gradient(ndimage.gaussian_filter(d, 3), RES)
    np.savez(os.path.join(out, name), Do=d, gx=gx, gy=gy)


field((0, 0), 'shore.npz')
field((int((3.6 - X0) / RES), int((3.6 - X0) / RES)), 'shore_island.npz')
print('fields written to', out)

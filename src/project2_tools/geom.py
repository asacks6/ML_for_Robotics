import numpy as np
from scipy.interpolate import RegularGridInterpolator
from scipy import ndimage

RES = 0.1
X0 = -25.0
N = 501
t = np.loadtxt('terrain.txt')
Zc = t[:, 2].reshape(50, 50)
xs = np.linspace(-25, 25, 50)
interp = RegularGridInterpolator((xs, xs), Zc)
g = X0 + RES * np.arange(N)
GY, GX = np.meshgrid(g, g, indexing='ij')
H = interp((GY, GX))
OBST = {'cube': [(-3.47, 2.05, 0.4)],
        'bill': [(13.8, -3.63, 0.35), (14.9, 3.25, 0.35), (4.15, 12.27, 0.35), (-7.75, 3.72, 0.35)],
        'pole': [(0.0, 0.0, 0.2)], 'chair': [(-5.43, 11.25, 0.45)], 'rack': [(0.0, 9.02, 0.7)],
        'toilet': [(4.95, 2.95, 0.45)],
        'plant': [(15.38, -12.67, 0.45), (16.25, -3.22, 0.45), (18.02, -8.82, 0.45)],
        'tree': [(-5.45, 12.83, 0.9), (4.78, -0.10, 0.9), (3.08, 7.33, 0.9), (18.0, -10.4, 0.9), (17.5, 10.7, 0.9),
                 (1.62, 18.65, 0.9), (-14.62, -10.95, 0.9), (11.28, 11.75, 0.9), (-0.15, 4.45, 0.9), (-0.12, -17.2, 0.9)]}
lake = H < 0.0
free = lake.copy()
for k, L in OBST.items():
    for (ox, oy, r) in L:
        free &= np.hypot(GX - ox, GY - oy) > r
# conservar solo la componente conexa del robot
lab, n = ndimage.label(free)
free &= lab == lab[int((-2.5 - X0) / RES), int((-2.38 - X0) / RES)]
D = ndimage.distance_transform_edt(free) * RES
np.savez('geom.npz', H=H, free=free, D=D, X0=X0, RES=RES)
print('lake area m2', free.sum() * RES * RES, 'max D', D.max())

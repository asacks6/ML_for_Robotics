import sys, os
import numpy as np
import cv2

# Quita las imagenes donde el cielo ocupa <20 % o >70 %: persona delante de la camara,
# robot volcado o atascado mirando la orilla
root = sys.argv[1]
L = [l.rstrip('\n') for l in open(os.path.join(root, 'labels.txt')) if l.strip()]
if not os.path.exists(os.path.join(root, 'labels_all.txt')):
    open(os.path.join(root, 'labels_all.txt'), 'w').write('\n'.join(L) + '\n')
fr = np.array([np.mean(cv2.imread(os.path.join(root, l.split()[0])).max(2) < 8) for l in L])
keep = [l for l, f in zip(L, fr) if 0.2 <= f <= 0.7]
open(os.path.join(root, 'labels.txt'), 'w').write('\n'.join(keep) + '\n')
print(root, len(L), '->', len(keep))

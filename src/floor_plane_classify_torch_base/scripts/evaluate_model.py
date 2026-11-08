#!/usr/bin/env python3
# Matriz de confusion de un modelo entrenado sobre un conjunto etiquetado.
# Usa PNGReader para que el preprocesado sea el mismo que en el entrenamiento.
import argparse
import os

import numpy as np
import cv2
import torch

from pytorch_models_base.model import CNNModel
from pytorch_models_base.reader import PNGReader

parser = argparse.ArgumentParser()
parser.add_argument('--model', required=True, help='fichero .pt')
parser.add_argument('--root', required=True, help='carpeta con labels.txt, p.ej. ~/data/floor_plane/val')
parser.add_argument('--classes', type=int, default=2)
parser.add_argument('--errors', default='', help='png donde guardar un mosaico de los errores')
args = parser.parse_args()

root = os.path.expanduser(args.root)
ds = PNGReader(os.path.join(root, 'labels.txt'), root)
model = CNNModel(3, args.classes, 0.0)
model.load_state_dict(torch.load(os.path.expanduser(args.model), weights_only=True, map_location='cpu'))
model.eval()

x = torch.from_numpy(np.stack(ds.x).transpose(0, 3, 1, 2).copy())
with torch.no_grad():
    pred = np.concatenate([model(b).numpy() for b in torch.split(x, 256)]).argmax(1)
y = ds.y

cm = np.zeros((args.classes, args.classes), int)
np.add.at(cm, (y, pred), 1)
print('confusion (filas = verdad, columnas = prediccion)')
print(cm)
print('accuracy %.4f sobre %d muestras' % (np.trace(cm) / cm.sum(), cm.sum()))
for c in range(args.classes):
    prec = cm[c, c] / max(1, cm[:, c].sum())
    rec = cm[c, c] / max(1, cm[c].sum())
    print('clase %d: precision %.4f recall %.4f' % (c, prec, rec))

if args.errors:
    # Borde con el color de la prediccion (equivocada)
    colors = [(0, 0, 255), (0, 255, 0), (255, 0, 0)]
    wrong = np.flatnonzero(pred != y)[:200]
    tiles = [cv2.copyMakeBorder((ds.x[i] * 255).astype(np.uint8), 2, 2, 2, 2, cv2.BORDER_CONSTANT,
                                value=colors[pred[i] % 3]) for i in wrong]
    if tiles:
        tiles += [np.zeros_like(tiles[0])] * (-len(tiles) % 20)
        grid = np.vstack([np.hstack(tiles[r:r + 20]) for r in range(0, len(tiles), 20)])
        cv2.imwrite(args.errors, cv2.resize(grid, (0, 0), fx=2, fy=2, interpolation=cv2.INTER_NEAREST))
    print('%d errores, mosaico en %s' % (len(wrong), args.errors))

#!/usr/bin/env python3
# Junta una o varias sesiones grabadas (carpetas con labels.txt) y las separa en
# ROOT/train y ROOT/val. Se separa por bloques de muestras consecutivas: dos
# imagenes seguidas son casi iguales y no deben quedar una en train y otra en val.
import argparse
import os
import random
import shutil
from collections import Counter

parser = argparse.ArgumentParser()
parser.add_argument('sessions', nargs='+', help='carpetas raw_* con labels.txt')
parser.add_argument('--out', required=True, help='carpeta que recibira train/ y val/')
parser.add_argument('--val', type=float, default=0.2, help='fraccion de validacion')
parser.add_argument('--block', type=int, default=64, help='muestras consecutivas por bloque')
parser.add_argument('--seed', type=int, default=0)
args = parser.parse_args()

rng = random.Random(args.seed)
labels = {'train': [], 'val': []}
for k, sess in enumerate(args.sessions):
    lines = [l.split() for l in open(os.path.join(sess, 'labels.txt')) if l.strip()]
    starts = list(range(0, len(lines), args.block))
    val_starts = set(rng.sample(starts, round(args.val * len(starts))))
    for b in starts:
        split = 'val' if b in val_starts else 'train'
        for path, label in lines[b:b + args.block]:
            dst = os.path.join('s%d' % k, path)
            os.makedirs(os.path.join(args.out, split, os.path.dirname(dst)), exist_ok=True)
            shutil.copyfile(os.path.join(sess, path), os.path.join(args.out, split, dst))
            labels[split].append((dst, label))

for split, items in labels.items():
    with open(os.path.join(args.out, split, 'labels.txt'), 'w') as f:
        for dst, label in items:
            f.write('%s %s\n' % (dst, label))
    print(split, len(items), dict(sorted(Counter(l for _, l in items).items())))

import sys, json
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# Barras de autonomia y tomas de control por vuelta, agrupadas por pista de prueba
# usage: comparison_bars.py metrics.json out.png
M = [m for m in json.load(open(sys.argv[1])) if not m['expert']]
tracks = ['outer', 'island']
fig, axs = plt.subplots(1, 3, figsize=(12.8, 5.4), dpi=100)
for ax, (key, name, lim) in zip(axs, [('autonomy', 'Autonomy (% of time the network drives)', 100),
                                      ('takeovers', 'Expert takeovers per lap', None),
                                      ('mae', '|d - d*| while the network drives (m)', None)]):
    xs, labels, colors = [], [], []
    top = max(m[key] + m[key + '_sd'] for m in M)
    x = 0
    for tr in tracks:
        x_start = x
        for m in [m for m in M if m['track'] == tr]:
            cross = 'cross' in m['label']
            ax.bar(x, m[key], yerr=m[key + '_sd'], capsize=4, color='#bbbbbb' if cross else ('#3b6ea5' if tr == 'outer' else '#5a9e5a'),
                   hatch='//' if cross else None, edgecolor='black', lw=0.6)
            ax.text(x, m[key] + m[key + '_sd'] + 0.02 * top, ('%.0f' if key == 'autonomy' else '%.2f' if key == 'mae' else '%.1f') % m[key],
                    ha='center', fontsize=9)
            labels.append(m['label'].split(':')[0])
            xs.append(x)
            x += 1
        if x > x_start:
            ax.text((x_start + x - 1) / 2, -0.13 * (lim or top * 1.1), '%s test' % ('outer rim' if tr == 'outer' else 'island'),
                    ha='center', fontsize=10, weight='bold')
        x += 0.6
    ax.set_xticks(xs)
    ax.set_xticklabels(labels)
    ax.set_title(name, fontsize=11)
    ax.set_ylim(0, lim or top * 1.12)
    ax.grid(axis='y', alpha=0.3)
fig.text(0.5, 0.01, 'blue: outer-rim test track, green: island test track, hatched grey: cross test (network trained on the other shore); '
         'error bars = std over 3 laps', ha='center', fontsize=10)
plt.tight_layout(rect=(0, 0.05, 1, 1))
fig.savefig(sys.argv[2])
print('wrote', sys.argv[2])

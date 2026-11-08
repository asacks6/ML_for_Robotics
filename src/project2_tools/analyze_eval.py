import sys, os, json
import numpy as np
import cv2
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# usage: analyze_eval.py out_dir runs.json
# runs.json: [{"tags": [...], "label": ..., "dstar": 1.5, "track": "outer"|"island", "expert": false}, ...]
# Cada vuelta se evalua por separado; la tabla da media y desviacion entre vueltas.
out_dir, runs = sys.argv[1], json.load(open(sys.argv[2]))
stem = os.path.join(out_dir, os.path.splitext(os.path.basename(sys.argv[2]))[0] + '_')
EV = os.path.expanduser('~/data/') + 'shore_follower/eval/'
SP = os.path.dirname(os.path.abspath(__file__)) + '/'
G = np.load(SP + 'geom.npz')
X0, RES = float(G['X0']), float(G['RES'])
D = np.load(SP + 'D_static.npy')


def lap_metrics(a, dstar, expert):
    t, x, y, d, ex, lap = a.T
    net = ex < 0.5
    sel = np.ones_like(net) if expert else net
    # Una toma de control = paso de red a experto; se normaliza por la fraccion de vuelta recorrida
    frac = float(np.abs(lap[-1]) - np.abs(lap[0]))
    to = int(np.sum((ex[1:] > 0.5) & (ex[:-1] < 0.5)))
    dn = d[sel]
    return dict(frac=frac, autonomy=100 * net.mean(), takeovers=to / max(frac, 1e-3), mae=np.abs(dn - dstar).mean(),
                mean_d=dn.mean(), std_d=dn.std(), within=100 * np.mean(np.abs(dn - dstar) < 0.5))


results = []
for r in runs:
    laps = []
    incidents = []
    for tag in r['tags']:
        for f in [EV + 'sup_' + tag + '.log', EV + tag + '_incident.txt']:
            if os.path.exists(f):
                incidents += [l.strip() for l in open(f) if 'incident' in l or 'flipped' in l]
        a = np.load(EV + tag + '_log.npy')
        p = np.abs(a[:, 5])
        n = int(np.ceil(p[-1] - 0.05))
        for k in range(n):
            seg = a[(p >= k) & (p < k + 1)]
            if len(seg) > 100:
                laps.append(lap_metrics(seg, r['dstar'], r.get('expert', False)))
    # Media ponderada por la fraccion de vuelta (las vueltas cortadas por un vuelco pesan menos)
    w = np.array([l['frac'] for l in laps])
    agg = {}
    for k in laps[0]:
        v = np.array([l[k] for l in laps])
        mu = float(np.sum(w * v) / np.sum(w))
        agg[k] = (mu, float(np.sqrt(np.sum(w * (v - mu) ** 2) / np.sum(w))))
    m = dict(label=r['label'], track=r['track'], dstar=r['dstar'], n_laps=float(np.sum(w)), expert=r.get('expert', False),
             incidents=incidents,
             **{k: v[0] for k, v in agg.items()}, **{k + '_sd': v[1] for k, v in agg.items()},
             per_lap=laps)
    results.append((r, m))
    print('%-40s %-6s %.2f laps  autonomy %5.1f +- %4.1f %%  takeovers/lap %.1f +- %.1f  |d-d*| %.2f +- %.2f  within %3.0f %%'
          % (m['label'], m['track'], m['n_laps'], m['autonomy'], m['autonomy_sd'], m['takeovers'], m['takeovers_sd'],
             m['mae'], m['mae_sd'], m['within']))
json.dump([m for _, m in results], open(stem + 'metrics.json', 'w'), indent=1)

plot_runs = [(r, m) for r, m in results if not r.get('expert', False)]
if plot_runs:
    # Distancia a la orilla en la primera evaluacion de cada red, tomas de control sombreadas
    fig, axs = plt.subplots(len(plot_runs), 1, figsize=(11, 1.9 * len(plot_runs)), sharex=True, squeeze=False)
    for ax, (r, m) in zip(axs[:, 0], plot_runs):
        a = np.load(EV + r['tags'][0] + '_log.npy')
        t, x, y, d, ex, lap = a.T
        p = np.abs(lap)
        ax.plot(p, d, lw=1.2, color='tab:blue')
        ax.fill_between(p, 0, 6, where=ex > 0.5, color='tab:red', alpha=0.2, lw=0)
        ax.axhline(r['dstar'], color='k', ls='--', lw=0.8)
        ax.set_ylim(0, 4.5)
        ax.set_ylabel('d (m)')
        ax.set_title(r['label'], fontsize=10, loc='left')
    axs[-1, 0].set_xlabel('lap progress, first evaluation lap (red = expert takeover, dashed = target distance)')
    plt.tight_layout()
    plt.savefig(stem + 'distance_profiles.png', dpi=110)

    base = np.zeros(D.shape + (3,), np.uint8)
    base[D > 0] = (200, 200, 200)
    base[D <= 0] = (60, 120, 60)
    C0, C1 = int((-20 - X0) / RES), int((22 - X0) / RES)
    tiles = []
    for r, m in plot_runs:
        img = cv2.flip(base[C0:C1, C0:C1].copy(), 0)
        for tag in r['tags']:
            a = np.load(EV + tag + '_log.npy')
            t, x, y, d, ex, lap = a.T
            px = ((x - X0) / RES - C0).astype(int)
            py = (C1 - (y - X0) / RES).astype(int)
            for k in range(1, len(px)):
                cv2.line(img, (px[k - 1], py[k - 1]), (px[k], py[k]), (0, 0, 230) if ex[k] > 0.5 else (200, 60, 0), 1,
                         cv2.LINE_AA)
        img = cv2.resize(img, (400, 400), interpolation=cv2.INTER_AREA)
        cv2.putText(img, r['label'][:40], (6, 18), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (0, 0, 0), 1, cv2.LINE_AA)
        cv2.putText(img, '%.1f laps: autonomy %.0f %%, %.1f takeovers/lap' % (m['n_laps'], m['autonomy'], m['takeovers']),
                    (6, 392), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (0, 0, 0), 1, cv2.LINE_AA)
        tiles.append(img)
    while len(tiles) % 3:
        tiles.append(np.full_like(tiles[0], 255))
    grid = np.vstack([np.hstack(tiles[k:k + 3]) for k in range(0, len(tiles), 3)])
    cv2.imwrite(stem + 'trajectories.png', grid)

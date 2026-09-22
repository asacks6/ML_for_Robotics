#!/usr/bin/env python3
import json
import os

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
DATA = os.path.join(HERE, 'data')
FIGURES = os.path.join(HERE, 'figures')
TS = 0.02


def load_topic(path):
    raw = np.genfromtxt(path, delimiter=',', usecols=(0, 1, 3), invalid_raise=False)
    raw = raw[np.isfinite(raw).all(axis=1)]
    t = raw[:, 0] + raw[:, 1] * 1e-9
    order = np.argsort(t)
    return np.column_stack((t[order], raw[order, 2]))


def resample(cmd, vel, ts=TS):
    t0 = min(cmd[0, 0], vel[0, 0])
    start = max(cmd[0, 0], vel[0, 0]) - t0
    stop = min(cmd[-1, 0], vel[-1, 0]) - t0
    t = np.arange(start, stop, ts)
    u = np.interp(t, cmd[:, 0] - t0, cmd[:, 1])
    y = np.interp(t, vel[:, 0] - t0, vel[:, 1])
    return t, u, y


def regressors(u, y, na, nb, nk):
    n = max(na, nb + nk - 1)
    rows = len(y) - n
    phi = np.zeros((rows, na + nb))
    for i in range(na):
        phi[:, i] = -y[n - 1 - i:n - 1 - i + rows]
    for j in range(nb):
        d = nk + j
        phi[:, na + j] = u[n - d:n - d + rows]
    return phi, y[n:], n


def fit_arx(u, y, na, nb, nk):
    phi, target, _ = regressors(u, y, na, nb, nk)
    theta, _, _, _ = np.linalg.lstsq(phi, target, rcond=None)
    return theta[:na], theta[na:]


def predict_one_step(u, y, a, b, nk):
    phi, target, n = regressors(u, y, len(a), len(b), nk)
    return n, target, phi @ np.concatenate((a, b))


def simulate(u, y, a, b, nk):
    na, nb = len(a), len(b)
    n = max(na, nb + nk - 1)
    out = np.zeros(len(u))
    out[:n] = y[:n]
    for k in range(n, len(u)):
        acc = 0.0
        for i in range(na):
            acc -= a[i] * out[k - 1 - i]
        for j in range(nb):
            acc += b[j] * u[k - nk - j]
        out[k] = acc
    return n, y[n:], out[n:]


def fit_percent(y, yhat):
    denom = np.linalg.norm(y - y.mean())
    if denom == 0:
        return float('nan')
    return 100.0 * (1.0 - np.linalg.norm(y - yhat) / denom)


def rmse(y, yhat):
    return float(np.sqrt(np.mean((y - yhat) ** 2)))


def stable(a):
    if len(a) == 0:
        return True
    roots = np.roots(np.concatenate(([1.0], a)))
    return bool(np.all(np.abs(roots) < 1.0))


def main():
    train_cmd = load_topic(os.path.join(DATA, 'train_cmd.csv'))
    train_vel = load_topic(os.path.join(DATA, 'train_vel.csv'))
    test_cmd = load_topic(os.path.join(DATA, 'test_cmd.csv'))
    test_vel = load_topic(os.path.join(DATA, 'test_vel.csv'))

    tr_t, tr_u, tr_y = resample(train_cmd, train_vel)
    te_t, te_u, te_y = resample(test_cmd, test_vel)

    print('training set : %d samples, %.1f s' % (len(tr_t), tr_t[-1] - tr_t[0]))
    print('test set     : %d samples, %.1f s' % (len(te_t), te_t[-1] - te_t[0]))
    print('command range: [%.2f, %.2f]  velocity range: [%.2f, %.2f]'
          % (tr_u.min(), tr_u.max(), tr_y.min(), tr_y.max()))
    print()

    candidates = []
    for nb in (1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 25):
        candidates.append(('FIR', 0, nb, 1))
    for na in (1, 2, 3, 4, 5, 6):
        for nb in (1, 2, 3, 4, 5, 6):
            for nk in (1, 2):
                candidates.append(('ARX', na, nb, nk))

    results = []
    for kind, na, nb, nk in candidates:
        a, b = fit_arx(tr_u, tr_y, na, nb, nk)
        _, y1, p1 = predict_one_step(te_u, te_y, a, b, nk)
        _, ys, ps = simulate(te_u, te_y, a, b, nk)
        _, y1tr, p1tr = predict_one_step(tr_u, tr_y, a, b, nk)
        results.append({
            'kind': kind, 'na': na, 'nb': nb, 'nk': nk,
            'a': a.tolist(), 'b': b.tolist(),
            'params': na + nb,
            'fit_train_1step': fit_percent(y1tr, p1tr),
            'fit_test_1step': fit_percent(y1, p1),
            'fit_test_sim': fit_percent(ys, ps),
            'rmse_test_1step': rmse(y1, p1),
            'rmse_test_sim': rmse(ys, ps),
            'dc_gain': float(np.sum(b) / (1.0 + np.sum(a))),
            'stable': stable(a),
        })

    results.sort(key=lambda r: -r['fit_test_sim'])

    header = '%-5s %3s %3s %3s %7s %8s %8s %8s %8s %6s' % (
        'type', 'na', 'nb', 'nk', 'params', 'fitTr1', 'fitTe1', 'fitTeSim', 'rmseSim', 'gain')
    print(header)
    print('-' * len(header))
    for r in results[:25]:
        print('%-5s %3d %3d %3d %7d %8.2f %8.2f %8.2f %8.4f %6.3f %s' % (
            r['kind'], r['na'], r['nb'], r['nk'], r['params'],
            r['fit_train_1step'], r['fit_test_1step'], r['fit_test_sim'],
            r['rmse_test_sim'], r['dc_gain'], '' if r['stable'] else 'UNSTABLE'))
    print()

    best_fir = max((r for r in results if r['kind'] == 'FIR'), key=lambda r: r['fit_test_sim'])
    usable = [r for r in results if r['kind'] == 'ARX' and r['stable']]
    best_arx = max(usable, key=lambda r: r['fit_test_sim'])
    top = max(usable, key=lambda r: r['fit_test_sim'] - 0.02 * r['params'])

    print('best FIR  : nb=%d  fit_sim=%.2f%%  fit_1step=%.2f%%'
          % (best_fir['nb'], best_fir['fit_test_sim'], best_fir['fit_test_1step']))
    print('best ARX  : na=%d nb=%d nk=%d  fit_sim=%.2f%%  fit_1step=%.2f%%'
          % (best_arx['na'], best_arx['nb'], best_arx['nk'],
             best_arx['fit_test_sim'], best_arx['fit_test_1step']))
    print('selected  : na=%d nb=%d nk=%d  fit_sim=%.2f%%  fit_1step=%.2f%%'
          % (top['na'], top['nb'], top['nk'], top['fit_test_sim'], top['fit_test_1step']))
    print()
    print('A(q) coefficients a1..a%d : %s' % (top['na'], ','.join('%.6f' % v for v in top['a'])))
    print('B(q) coefficients b1..b%d : %s' % (top['nb'], ','.join('%.6f' % v for v in top['b'])))
    print('dc gain %.4f, poles %s' % (top['dc_gain'],
                                      np.round(np.roots(np.concatenate(([1.0], top['a']))), 4)))
    print()
    print('launch file parameters (inverse_coef_list: True, rate %.1f):' % (1.0 / TS))
    print("  {'~/state_coef_csv': \"%s\"}," % ','.join('%.6f' % v for v in top['a']))
    print("  {'~/command_coef_csv': \"%s\"}," % ','.join('%.6f' % v for v in top['b']))

    with open(os.path.join(HERE, 'models.json'), 'w') as f:
        json.dump({'ts': TS, 'selected': top, 'best_arx': best_arx,
                   'best_fir': best_fir, 'all': results}, f, indent=2)

    make_plots(tr_t, tr_u, tr_y, te_t, te_u, te_y, results, top, best_fir, best_arx)


def make_plots(tr_t, tr_u, tr_y, te_t, te_u, te_y, results, top, best_fir, best_arx):
    fig, ax = plt.subplots(2, 1, figsize=(13, 6), sharex=True)
    ax[0].plot(tr_t, tr_u, lw=0.8)
    ax[0].set_ylabel('command linear.x')
    ax[0].set_title('training bag')
    ax[0].grid(alpha=0.3)
    ax[1].plot(tr_t, tr_y, lw=0.8, color='tab:orange')
    ax[1].set_ylabel('measured linear.x')
    ax[1].set_xlabel('time [s]')
    ax[1].grid(alpha=0.3)
    fig.tight_layout()
    fig.savefig(os.path.join(FIGURES, 'train_data.png'), dpi=110)
    plt.close(fig)

    fig, ax = plt.subplots(2, 1, figsize=(13, 6), sharex=True)
    ax[0].plot(te_t, te_u, lw=0.8)
    ax[0].set_ylabel('command linear.x')
    ax[0].set_title('test bag')
    ax[0].grid(alpha=0.3)
    ax[1].plot(te_t, te_y, lw=0.8, color='tab:orange')
    ax[1].set_ylabel('measured linear.x')
    ax[1].set_xlabel('time [s]')
    ax[1].grid(alpha=0.3)
    fig.tight_layout()
    fig.savefig(os.path.join(FIGURES, 'test_data.png'), dpi=110)
    plt.close(fig)

    a = np.array(top['a'])
    b = np.array(top['b'])
    n1, y1, p1 = predict_one_step(te_u, te_y, a, b, top['nk'])
    ns, ys, ps = simulate(te_u, te_y, a, b, top['nk'])

    fig, ax = plt.subplots(2, 1, figsize=(13, 7), sharex=True)
    ax[0].plot(te_t[n1:], y1, label='measured', lw=1.0)
    ax[0].plot(te_t[n1:], p1, label='one step ahead (%.1f%%)' % top['fit_test_1step'],
               lw=0.9, ls='--')
    ax[0].set_title('ARX %d %d %d on test bag' % (top['na'], top['nb'], top['nk']))
    ax[0].legend(loc='upper right')
    ax[0].grid(alpha=0.3)
    ax[0].set_ylabel('linear.x [m/s]')
    ax[1].plot(te_t[ns:], ys, label='measured', lw=1.0)
    ax[1].plot(te_t[ns:], ps, label='simulated (%.1f%%)' % top['fit_test_sim'],
               lw=0.9, ls='--', color='tab:green')
    ax[1].legend(loc='upper right')
    ax[1].grid(alpha=0.3)
    ax[1].set_ylabel('linear.x [m/s]')
    ax[1].set_xlabel('time [s]')
    fig.tight_layout()
    fig.savefig(os.path.join(FIGURES, 'test_prediction.png'), dpi=110)
    plt.close(fig)

    lo = int(60.0 / TS)
    hi = lo + int(25.0 / TS)
    hi = min(hi, len(ps) + ns)
    fig, ax = plt.subplots(figsize=(13, 4.5))
    ax.plot(te_t[lo:hi], te_y[lo:hi], label='measured', lw=1.4)
    ax.plot(te_t[lo:hi], ps[lo - ns:hi - ns], label='simulated', lw=1.2, ls='--')
    ax.plot(te_t[lo:hi], te_u[lo:hi], label='command', lw=0.9, alpha=0.5, color='grey')
    ax.legend(loc='upper right')
    ax.grid(alpha=0.3)
    ax.set_xlabel('time [s]')
    ax.set_ylabel('linear.x [m/s]')
    ax.set_title('detail of the simulated response')
    fig.tight_layout()
    fig.savefig(os.path.join(FIGURES, 'test_prediction_detail.png'), dpi=110)
    plt.close(fig)

    fir = [r for r in results if r['kind'] == 'FIR']
    fir.sort(key=lambda r: r['nb'])
    arx = [r for r in results if r['kind'] == 'ARX' and r['nk'] == 1 and r['na'] == r['nb']]
    arx.sort(key=lambda r: r['na'])
    fig, ax = plt.subplots(figsize=(9, 5))
    ax.plot([r['nb'] for r in fir], [r['fit_test_sim'] for r in fir],
            'o-', label='FIR, nb terms')
    ax.plot([r['na'] + r['nb'] for r in arx], [r['fit_test_sim'] for r in arx],
            's-', label='ARX na=nb, nk=1')
    ax.set_xlabel('number of parameters')
    ax.set_ylabel('fit on test bag [%]')
    ax.set_title('model order selection')
    ax.grid(alpha=0.3)
    ax.legend()
    fig.tight_layout()
    fig.savefig(os.path.join(FIGURES, 'order_selection.png'), dpi=110)
    plt.close(fig)

    steps = int(3.0 / TS)
    u_step = np.ones(steps)
    u_step[:int(0.2 / TS)] = 0.0
    fig, ax = plt.subplots(figsize=(9, 5))
    for label, r in (('selected ARX %d%d%d' % (top['na'], top['nb'], top['nk']), top),
                     ('best FIR nb=%d' % best_fir['nb'], best_fir),
                     ('best ARX %d%d%d' % (best_arx['na'], best_arx['nb'], best_arx['nk']),
                      best_arx)):
        aa = np.array(r['a'])
        bb = np.array(r['b'])
        _, _, resp = simulate(u_step, np.zeros(steps), aa, bb, r['nk'])
        n = steps - len(resp)
        ax.plot(np.arange(n, steps) * TS, resp, label=label, lw=1.2)
    ax.plot(np.arange(steps) * TS, u_step, color='grey', alpha=0.5, label='command')
    ax.set_xlabel('time [s]')
    ax.set_ylabel('linear.x [m/s]')
    ax.set_title('step response of the identified models')
    ax.grid(alpha=0.3)
    ax.legend()
    fig.tight_layout()
    fig.savefig(os.path.join(FIGURES, 'step_response.png'), dpi=110)
    plt.close(fig)


if __name__ == '__main__':
    main()

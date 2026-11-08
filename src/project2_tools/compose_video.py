import sys, json
import numpy as np
import cv2
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# Monta el video final a partir de una lista de tarjetas, imagenes y clips.
# usage: compose_video.py spec.json out.mp4
spec, out = json.load(open(sys.argv[1])), sys.argv[2]
W, H, FPS = 1280, 720, 30
vw = cv2.VideoWriter(out, cv2.VideoWriter_fourcc(*'avc1'), FPS, (W, H))
BG = (24, 24, 28)


def fig_to_img(fig):
    fig.canvas.draw()
    a = np.asarray(fig.canvas.buffer_rgba())[..., :3]
    plt.close(fig)
    return cv2.resize(cv2.cvtColor(a, cv2.COLOR_RGB2BGR), (W, H), interpolation=cv2.INTER_AREA)


def card(title, lines, small=False):
    fig = plt.figure(figsize=(12.8, 7.2), dpi=100)
    fig.patch.set_facecolor('#1c1c1c')
    fig.text(0.06, 0.86, title, color='white', fontsize=26, weight='bold', va='top')
    y = 0.72
    for ln in lines:
        fig.text(0.07, y, ln, color='#dddddd', fontsize=15 if small else 17, va='top', family='DejaVu Sans')
        y -= 0.06 if small else 0.075
    return fig_to_img(fig)


def image_slide(path, caption):
    img = cv2.imread(path)
    h, w = img.shape[:2]
    s = min((W - 40) / w, (H - 90) / h)
    img = cv2.resize(img, (int(w * s), int(h * s)), interpolation=cv2.INTER_AREA)
    canvas = np.full((H, W, 3), BG, np.uint8)
    y0, x0 = 70 + (H - 90 - img.shape[0]) // 2, (W - img.shape[1]) // 2
    canvas[y0:y0 + img.shape[0], x0:x0 + img.shape[1]] = img
    put_caption(canvas, caption)
    return canvas


def put_caption(canvas, caption):
    cv2.putText(canvas, caption, (24, 44), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (255, 255, 255), 2, cv2.LINE_AA)


def emit(frame, seconds):
    for _ in range(int(seconds * FPS)):
        vw.write(frame)


for item in spec:
    if 'card' in item:
        emit(card(item['card'], item.get('lines', []), item.get('small', False)), item.get('seconds', 6))
    elif 'image' in item:
        emit(image_slide(item['image'], item.get('caption', '')), item.get('seconds', 8))
    elif 'clip' in item:
        # step = cuantos fotogramas de origen se saltan (aceleracion extra)
        c = cv2.VideoCapture(item['clip'])
        step, k, n = item.get('step', 1), 0, 0
        max_frames = int(item.get('max_s', 1e9) * FPS)
        src_fps = c.get(cv2.CAP_PROP_FPS)
        # Tiempo simulado real de cada fotograma, guardado por record_demo.py; se quita la barra grabada
        side = np.load(item['clip'].replace('.mp4', '_dist.npy'))
        times = side[:, 0]
        if item.get('log'):
            # El clip empieza cuando la red toma el control por primera vez (antes el experto
            # lleva el robot desde la pose inicial hasta la orilla); se busca por posicion
            lg = np.load(item['log'])
            first = lg[np.argmax(lg[:, 4] < 0.5)]
            traj = np.load(item['clip'].replace('.mp4', '_traj.npy'))
            item['start'] = max(0, int(np.argmin(np.hypot(traj[:, 0] - first[1], traj[:, 1] - first[2]))) - 15)
        speed = round(step * src_fps * float(np.mean(np.diff(times))))
        while n < max_frames:
            ok, f = c.read()
            if not ok:
                break
            k += 1
            if k - 1 < item.get('start', 0):
                continue
            if k - 1 > item.get('end', 1e9):
                break
            if (k - 1 - item.get('start', 0)) % step:
                continue
            f = f[item.get('crop_top', 40):]
            h, w = f.shape[:2]
            s = min((W - 20) / w, (H - 80) / h)
            f = cv2.resize(f, (int(w * s), int(h * s)), interpolation=cv2.INTER_AREA)
            canvas = np.full((H, W, 3), BG, np.uint8)
            y0, x0 = 66 + (H - 76 - f.shape[0]) // 2, (W - f.shape[1]) // 2
            canvas[y0:y0 + f.shape[0], x0:x0 + f.shape[1]] = f
            put_caption(canvas, item.get('caption', ''))
            cv2.putText(canvas, 'sim t = %4.0f s   played at ~x%d' % (times[min(k - 1, len(times) - 1)], speed), (W - 380, 44),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.7, (200, 200, 200), 1, cv2.LINE_AA)
            vw.write(canvas)
            n += 1
vw.release()
print('wrote', out)

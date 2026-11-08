import sys, os, random, numpy as np, cv2
root, out = sys.argv[1], sys.argv[2]
lines = [l.split() for l in open(os.path.join(root, 'labels.txt'))]
random.seed(1)
rows = []
for lab in ['1', '0']:
    sel = [l[0] for l in lines if l[1] == lab]
    sel = random.sample(sel, min(80, len(sel)))
    ims = [cv2.imread(os.path.join(root, p)) for p in sel]
    ims += [np.zeros((32, 32, 3), np.uint8)] * (80 - len(ims))
    grid = np.vstack([np.hstack(ims[r * 20:(r + 1) * 20]) for r in range(4)])
    rows.append(cv2.copyMakeBorder(grid, 4, 4, 4, 4, cv2.BORDER_CONSTANT, value=(0, 255, 0) if lab == '1' else (0, 0, 255)))
cv2.imwrite(out, cv2.resize(np.vstack(rows), (0, 0), fx=1.5, fy=1.5, interpolation=cv2.INTER_NEAREST))

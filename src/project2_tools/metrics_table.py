import sys, json
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# Tabla de resultados para el video a partir del metrics.json de analyze_eval.py
# usage: metrics_table.py metrics.json out.png
M = json.load(open(sys.argv[1]))
cols = ['Network (training data)', 'Test track', 'Laps', 'Autonomy', 'Takeovers / lap', '|d - d*| (m)', 'Within 0.5 m', 'Incidents']
cells = []
for m in M:
    if m['expert']:
        aut, to = 'expert drives', '-'
    else:
        aut = '%.0f ± %.0f %%' % (m['autonomy'], m['autonomy_sd'])
        to = '%.1f ± %.1f' % (m['takeovers'], m['takeovers_sd'])
    inc = m.get('incidents', [])
    nf = sum('flipped' in i for i in inc)
    ns = len(inc) - nf
    note = ', '.join(x for x in ['%d roll-over%s' % (nf, 's' if nf > 1 else '') if nf else '',
                                 '%d stuck' % ns if ns else ''] if x) or '-'
    cells.append([m['label'], m['track'], '%.1f' % m['n_laps'], aut, to, '%.2f ± %.2f' % (m['mae'], m['mae_sd']),
                  '%.0f %%' % m['within'], note])
fig = plt.figure(figsize=(12.8, 0.5 * (len(cells) + 1)), dpi=100)
ax = fig.add_axes([0.005, 0.01, 0.99, 0.98])
ax.axis('off')
tb = ax.table(cellText=cells, colLabels=cols, bbox=[0, 0, 1, 1], cellLoc='center',
              colWidths=[0.29, 0.08, 0.05, 0.12, 0.12, 0.12, 0.09, 0.11])
tb.auto_set_font_size(False)
tb.set_fontsize(12)
for (i, j), c in tb.get_celld().items():
    if i == 0:
        c.set_facecolor('#33415c')
        c.set_text_props(color='white', weight='bold')
    elif cells[i - 1][3] == 'expert drives':
        c.set_facecolor('#eeeeee')
fig.savefig(sys.argv[2], bbox_inches='tight', pad_inches=0.15)
print('wrote', sys.argv[2])

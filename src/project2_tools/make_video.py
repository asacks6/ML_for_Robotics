import json, subprocess, os

# Genera las diapositivas, la especificacion del video final y lo monta.
# Las cifras de las tarjetas salen de runs_final_metrics.json (analyze_eval.py).
HOME = os.path.expanduser('~')
T = os.path.dirname(os.path.abspath(__file__))
V = HOME + '/data/videos/'
A = HOME + '/data/shore_follower/eval/analysis/'
PY = '/usr/bin/python3'
os.makedirs(V + 'slides', exist_ok=True)
metrics = A + 'runs_final_metrics.json'
subprocess.run([PY, T + '/metrics_table.py', metrics, V + 'slides/shore_table.png'], check=True)
subprocess.run([PY, T + '/comparison_bars.py', metrics, V + 'slides/shore_bars.png'], check=True)
M = {(m['label'].split(':')[0], m['track']): m for m in json.load(open(metrics))}


def g(net, track, key, fmt):
    return fmt % M[(net, track)][key]


A_o, B_o, C_o = ('A', 'outer'), ('B', 'outer'), ('C', 'outer')
C0_i, C_i, B_i = ('C0', 'island'), ('C', 'island'), ('B', 'island')
conclusions = [
    'DAgger on the outer rim: autonomy %s -> %s %%, takeovers per lap %s -> %s, |d - d*| %s -> %s m.' % (
        g(*A_o, 'autonomy', '%.0f'), g(*B_o, 'autonomy', '%.0f'), g(*A_o, 'takeovers', '%.1f'), g(*B_o, 'takeovers', '%.1f'),
        g(*A_o, 'mae', '%.2f'), g(*B_o, 'mae', '%.2f')),
    '  Expert data only: the robot zigzags in and out of the band; after DAgger it holds 1.5 to 2 m.',
    'On the island the extra DAgger round did not help: C0 %s %% / %s takeovers per lap, C %s %% / %s.' % (
        g(*C0_i, 'autonomy', '%.0f'), g(*C0_i, 'takeovers', '%.1f'), g(*C_i, 'autonomy', '%.0f'), g(*C_i, 'takeovers', '%.1f')),
    '  Likely reason: C0 already drove 84 % of its DAgger round, so few new hard states were added.',
    'Cross tests: each network is worse on the shore it was not trained on.',
    '  B on the island %s %% (%s takeovers per lap), C on the outer rim %s %% (%s per lap).' % (
        g(*B_i, 'autonomy', '%.0f'), g(*B_i, 'takeovers', '%.1f'), g(*C_o, 'autonomy', '%.0f'), g(*C_o, 'takeovers', '%.1f')),
    'Takeovers cluster where the shore shape changes sharply: the tree in the north-east bay',
    '  of the outer rim and the cube on the west side of the island.',
    'Walking people are not in the labels: both roll-overs came just after people reached the robot.',
    'Limits: one training run per condition, three evaluation laps per network, ground-truth expert.',
]

spec = [
    {'card': 'Project 2: learned traversability and shore following', 'seconds': 7, 'lines': [
        'CS7630, scene lakeExampleRich in CoppeliaSim 4.10, Summit XL with a Kinect, ROS 2',
        'Network: pytorch_models_base CNN, 2 conv + 4 fully connected layers, 32x32 input',
        'Part 1: floor traversability classifier',
        'Part 2: shore follower, four networks trained under different conditions',
        'Clips are sped up; the factor and the simulation time are in the top right corner']},
    {'card': 'Part 1: floor traversability from appearance', 'seconds': 12, 'small': True, 'lines': [
        'Labels come from the Kinect: each 32x32 thumbnail is compared with the floor plane in the robot frame.',
        '  obstacle: more than 20 % of its points are more than 5 cm away from the floor',
        '  traversable: more than 90 % of it has depth and less than 1 % is off the floor',
        '  otherwise unusable (not saved); frames are skipped when the robot tilts by more than 1 degree',
        'Dataset: scripted random tour of the lake bed that approaches the obstacles,',
        '  two sessions of 3000 thumbnails per class (balanced with max_image_per_type)',
        'Train / validation split by blocks of 64 consecutive samples of session 1;',
        '  session 2 is a held-out test set recorded with a different tour']},
    {'image': V + 'slides/floor_results.png', 'caption': 'Floor classifier: confusion matrices and errors', 'seconds': 12},
    {'clip': V + 'floor_classifier_demo.mp4', 'step': 2, 'caption': 'Floor classifier on a tour of the static obstacles'},
    {'card': 'Part 2: shore following', 'seconds': 13, 'small': True, 'lines': [
        'Task: keep the shore on the right at d* = 1.5 m, constant speed 0.3 m/s.',
        'Labels: right / straight / left from the demonstrated angular speed, threshold 0.2 rad/s.',
        'Network command: angular = 0.4 x (p_left - p_right), the expected turn instead of the argmax.',
        'Demonstrations: a scripted expert that uses the ground-truth pose and a distance field to the shore.',
        '  Random steering kicks while recording, so the data also shows how to recover.',
        'DAgger: the trained network drives, the expert only labels the images it sees, then retrain.',
        'Images with a person in front of the camera (sky below 20 % or above 70 %) are dropped.']},
    {'card': 'Four networks: two shores x two dataset recipes', 'seconds': 14, 'small': True, 'lines': [
        'A   outer rim, expert demonstrations only (9476 images)',
        'B   outer rim, data of A + one DAgger round driven by A (13066 images)',
        'C0  island shore, expert demonstrations only (4498 images)',
        'C   island shore, data of C0 + one DAgger round driven by C0 (8089 images)',
        'Evaluation: supervised laps from the same start pose, simulation restarted for each run.',
        '  The expert takes over when d > d* + 1.5 m, d < 0.7 m or the heading error exceeds 75 degrees,',
        '  and gives control back once the robot is on track again.',
        'Metrics: autonomy (% of time the network drives), takeovers per lap, |d - d*| while the network drives.',
        'B and C are also tested on the shore they were not trained on (cross test).']},
    {'clip': V + 'shore_A_expert.mp4', 'log': HOME + '/data/shore_follower/eval/A_expert_log.npy', 'step': 3, 'caption': 'A: outer rim, expert data only'},
    {'clip': V + 'shore_B_dagger.mp4', 'log': HOME + '/data/shore_follower/eval/B_dagger_log.npy', 'step': 3, 'caption': 'B: outer rim, expert + DAgger'},
    {'clip': V + 'shore_C0_island.mp4', 'log': HOME + '/data/shore_follower/eval/C0_island_log.npy', 'step': 2, 'caption': 'C0: island, expert data only'},
    {'clip': V + 'shore_C_island.mp4', 'log': HOME + '/data/shore_follower/eval/C_island_log.npy', 'step': 2, 'caption': 'C: island, expert + DAgger'},
    {'clip': V + 'shore_B_island.mp4', 'log': HOME + '/data/shore_follower/eval/B_island_log.npy', 'step': 2, 'caption': 'Cross test: B (outer rim) on the island'},
    {'clip': V + 'shore_C_outer.mp4', 'log': HOME + '/data/shore_follower/eval/C_outer_log.npy', 'step': 3, 'end': 3270, 'caption': 'Cross test: C (island) on the outer rim'},
    {'clip': V + 'shore_C_outer_r2.mp4', 'step': 1, 'start': 640, 'caption': 'C on the outer rim, 2nd run: people hit it'},
    {'image': V + 'slides/shore_table.png', 'caption': 'Shore following: results per lap (mean +/- std)', 'seconds': 15},
    {'image': V + 'slides/shore_bars.png', 'caption': 'Shore following: comparison', 'seconds': 14},
    {'image': A + 'runs_outer_distance_profiles.png', 'caption': 'Outer rim test: distance to the shore, first lap',
     'seconds': 12},
    {'image': A + 'runs_island_distance_profiles.png', 'caption': 'Island test: distance to the shore, first lap',
     'seconds': 12},
    {'image': A + 'runs_final_trajectories.png', 'caption': 'All evaluation laps (red = expert takeover)', 'seconds': 13},
    {'card': 'Conclusions', 'seconds': 20, 'small': True, 'lines': conclusions},
]
json.dump(spec, open(V + 'slides/spec.json', 'w'), indent=1)
subprocess.run([PY, T + '/compose_video.py', V + 'slides/spec.json', V + 'project2_performance_analysis.mp4'], check=True)

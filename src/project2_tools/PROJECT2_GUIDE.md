# CS7630 Project 2: guide

Scene: `/cs-share/pradalier/ros2_ws/src/scenes/lakeExampleRich.ttt` (CoppeliaSim 4.10, ROS 2 Kilted).

## 1. The project in one page

The robot (a Summit XL with a Kinect; its tf frame is still called `bubbleRob`) drives in a
dried-up lake: a flat concrete lake bed shaped like a ring around an island, surrounded by a
grassy shore that rises out of the floor. Trees, plants, a cube, a pole, a chair, a rack and
walking people are scattered around.

Both objectives use the same small CNN from `pytorch_models_base` (2 convolution layers and 4
fully connected layers, 32x32 BGR input), trained on images recorded in the simulation.

**Objective 1, floor traversability.** The Kinect depth gives a free label for every 32x32 patch
of the camera image: if the 3D points of the patch stick out of the floor plane, it is an
obstacle. We record thousands of labelled patches while driving, train the CNN to predict the
label from the colours alone, then run it on the live camera image and paint every patch green
(traversable) or red (obstacle). Result: 98.85 % accuracy on the validation split and 99.85 % on
a second recording session never used in training.

**Objective 2, shore following.** The CNN looks at the whole camera image (shrunk to 32x32) and
chooses turn right, go straight or turn left, to keep the shore on the robot's right at 1.5 m.
The demonstrations come from a scripted expert that knows the robot pose and the shore geometry,
with random steering kicks so the data also shows how to recover. We then improve the network
with DAgger: the network drives, the expert only labels what the network sees, and we retrain.
We trained four networks (outer shore or island, with or without DAgger) and compared them on
supervised laps where the expert only takes over when the robot gets lost.

| Network | Training data | Tested on | Autonomy | Takeovers per lap |
|---|---|---|---|---|
| A | outer shore, expert only | outer | 64 % | 14.3 |
| B | outer shore, expert + DAgger | outer | 86 % | 4.0 |
| C0 | island, expert only | island | 86 % | 2.3 |
| C | island, expert + DAgger | island | 81 % | 3.7 |
| B | (cross test) | island | 74 % | 5.7 |
| C | (cross test) | outer | 61 % | 15.8 |

DAgger made a big difference on the outer shore and none on the island; each network is worse
on the shore it was not trained on.

## 2. Watching the results

Videos are in `~/data/videos/`:

| File | Content |
|---|---|
| `project2_performance_analysis.mp4` | **the deliverable** (5:53): method, floor results, one lap of each shore network, cross tests, tables, plots, conclusions |
| `floor_classifier_demo.mp4` | floor classifier on a tour of the obstacles (x2) |
| `shore_A_expert.mp4`, `shore_B_dagger.mp4` | first evaluation lap of A and B on the outer shore (x3) |
| `shore_C0_island.mp4`, `shore_C_island.mp4` | first evaluation lap of C0 and C on the island |
| `shore_B_island.mp4`, `shore_C_outer*.mp4` | cross tests (C rolled over in `shore_C_outer.mp4` and `_r2`) |
| `*_r2.mp4`, `shore_C_outer_r3.mp4` | the extra laps used for the statistics |

In the shore clips the banner says NETWORK DRIVING or EXPERT TAKEOVER, the bar shows the turn
command, and the top view draws the path in blue (network) or red (expert).
The figures and the results table are in `~/data/shore_follower/eval/analysis/` and
`~/data/videos/slides/`.

## 3. Running it yourself

### 3.1 Once per session

1. The zenoh router must be running (`zenod` in a terminal if it is not) and
   `ROS_DOMAIN_ID` set (your `.bashrc` sets 69).
2. Start CoppeliaSim with the GUI (`csim`), open
   `/cs-share/pradalier/ros2_ws/src/scenes/lakeExampleRich.ttt` and press Play.
3. Every terminal that runs ROS nodes:
   ```
   source /cs-share/pradalier/venv/torch-cpu-ros2/bin/activate
   source ~/ros_workspace/install/setup.bash
   ```
   (the two `watch_*.sh` scripts below do this themselves).

The workspace is already built. If you rebuild, activate the venv first (cv_bridge2 needs it).

### 3.2 Floor classifier (what the video shows)

Press Stop then Play in CoppeliaSim so the robot is back at its start pose, then:
```
~/ros_workspace/src/project2_tools/watch_floor.sh
```
It starts the classifier node with the trained model (`model_ce_99.pt`), opens a window with the
camera, the network output and a top view, and drives a 2-minute route that stops in front of
the pole, the cube, an island tree, the chair and the rack. Watch the robot in CoppeliaSim at the
same time. Esc in the window or Ctrl+C in the terminal stops everything.

To drive yourself instead: `watch_floor.sh manual`, then in another terminal either the joystick
(`ros2 launch vrep_ros_teleop teleop.launch.py`) or the keyboard
(`ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r cmd_vel:=/vrep/twistCommand`).

The assignment's own way, without my scripts:
```
ros2 launch floor_plane_classify_torch_base start.launch.py model:=$HOME/data/floor_plane/output_20261013_162545/models/model_ce_99.pt
ros2 run rqt_image_view rqt_image_view /floor_plane_classify/image_label
```

### 3.3 Shore follower (what the video shows)

Press Stop then Play (start pose), then for example:
```
~/ros_workspace/src/project2_tools/watch_shore.sh B          # outer shore, expert + DAgger
~/ros_workspace/src/project2_tools/watch_shore.sh A          # outer shore, expert data only
~/ros_workspace/src/project2_tools/watch_shore.sh C          # island, expert + DAgger
~/ros_workspace/src/project2_tools/watch_shore.sh C0         # island, expert data only
~/ros_workspace/src/project2_tools/watch_shore.sh B island   # cross test
~/ros_workspace/src/project2_tools/watch_shore.sh C outer    # cross test
```
Optional third argument: number of laps (default 1). One outer lap takes about 7 minutes of
simulated time, one island lap about 3.5.

What happens: the expert first drives the robot from the start pose to the shore (red path),
then the network drives (blue). If the robot gets more than 3 m from the shore, closer than
0.7 m, or turns more than 75 degrees away from the shore direction, the expert takes over until
the robot is back on track. The terminal prints progress every 30 s of simulated time and, at the
end, the autonomy (% of the time the network drove) and the number of takeovers. The first run
builds the scene maps it needs (a few seconds).

Start each run from the start pose (Stop then Play): the expert has no obstacle avoidance and can
hit the rack if it has to cross the lake from somewhere else.

The assignment's own way, where the network drives alone:
```
ros2 launch shore_follower_drive_torch_base start.launch.py model:=$HOME/data/shore_follower/output_20261013_184009/models/model_ce_71.pt
```
Drive the robot close to the shore with the shore on its right (joystick), then give control to
the network with joystick button 1, or:
```
ros2 service call /cmd_mux/select topic_tools_interfaces/srv/MuxSelect "{topic: '/mux/autoCommand'}"
```

### 3.4 Troubleshooting

- The robot keeps moving after a script is killed: the simulator repeats the last command.
  `ros2 topic pub --once /vrep/twistCommand geometry_msgs/msg/Twist "{}"` stops it.
- A walking person can block the robot or, after a collision, roll it over. Press Stop and Play.
- `No simulation on ROS_DOMAIN_ID=...`: the sim is not playing, or it runs on another domain.
- CoppeliaSim crashes at start-up: another user left a lock in `/tmp/qipc_sharedmemory_coppeliaSim*`;
  start it with `TMPDIR=/tmp/$USER-coppelia` (create the folder first).
- Training or video encoding at the same time slows the simulation down (it runs at real time
  otherwise). Results are in simulated time, so they stay valid, just slower to watch.
- Logs of the watch scripts are in `~/ros_workspace/src/project2_tools/logs/`.

## 4. How it works

### 4.1 Scene facts used everywhere

- The `bubbleRob` frame origin is 0.31 m above the floor, so flat floor is at z = -0.31 m in
  the robot frame.
- Camera image 128x128, focal length 117.9 px, Kinect depth saturates at 5 m. The point cloud
  comes from `vrep4_helpers/kinect_pc_min.launch.py` (depth_image_proc), now included in the
  record launch file.
- The lake bed is the simulator floor at z = 0; the shore is a heightfield that rises above it.
  `dump_terrain.sh`, `geom.py` and `build_fields.py` turn the heightfield into a 0.1 m grid and
  distance fields to the outer shore, to the island and to any static obstacle.
- Positive `angular.z` turns left.

### 4.2 Objective 1: floor classifier

**Labels (`floor_plane_record_base/src/floor_plane_extract.cpp`, `check_thumb`).** For each
32x32 thumbnail, count the pixels that have a 3D point and the ones whose height differs from
the floor (z = -0.31 m) by more than `height_threshold` (5 cm):
- more than 20 % of the thumbnail off the floor: **untraversable**;
- more than 90 % with depth and less than 1 % off the floor: **traversable**;
- anything else (too little depth, or a mixed patch): **unusable**, not saved.

If the robot is tilted by more than 1 degree (it climbed the shore), the floor is no longer at
-0.31 m in its frame and every thumbnail would be called an obstacle, so the whole frame is
skipped. The tilt is read from TF inside `check_thumb`. The point projection in the starter code
was already correct (the "sign error?" comment is a red herring).

**Recording.** `ros2 launch floor_plane_record_base record.launch.py` (optional
`out_dir:=...`, default `~/data/floor_plane/raw_<date>`; the node rewrites `labels.txt` at start,
so each session needs its own folder). Parameters: `max_image_per_type` 3000,
`min_displacement` 0.15 m, `min_rotation` 0.25 rad (0.1 in session 1 let a robot turning on the
spot record 2000 near-identical obstacle thumbnails). The data was recorded with `tour.py`, a
random tour of the lake bed where a third of the targets are next to an obstacle, in two sessions
with different random seeds: `raw_sim1` and `raw_sim2`, 3000 thumbnails per class each.

**Split.** `floor_plane_record_base/scripts/split_dataset.py` copies the sessions into `train/`
and `val/` by blocks of 64 consecutive samples (20 % to validation). Consecutive frames are almost
identical, so a random split per image would leak them into validation. Session 1 was split into
train / val, session 2 was kept as an independent test set.

**Training.** `floor_plane_classify_torch_base/scripts/train_floor_plane.sh` (run it from the
folder where you want the `runs/` TensorBoard folder; it needs the venv and the workspace
sourced): learning rate 1e-4, weight decay 1e-4, batch 64, 20 epochs, dropout 0.2, 2 classes.
About 1 minute per epoch on the CPU. Best checkpoint:
`~/data/floor_plane/output_20261013_162545/models/model_ce_99.pt`.

**Runtime node (`floor_plane_classify_node.py`).** Splits the 128x128 image into 16 thumbnails,
divides pixels by 255 (as in training), runs them as one batch, takes the argmax and returns red
(obstacle) or green (traversable); the node overlays it at 50 %. The model is loaded with
`map_location='cpu'` so a GPU-trained file also works.

**Evaluation (`scripts/evaluate_model.py`).** Validation 98.85 % (1216 thumbnails): the 14
errors are all floor with grass at the waterline, which is less than 5 cm high so the depth rule
calls it traversable while the network says obstacle. Held-out session 99.85 % (6000): the 9
errors are edges of the lavender cube, a rock and a dark corner called traversable. Confusion
matrices and error mosaics: `~/data/floor_plane/eval/`.

### 4.3 The network and the planted bugs in `pytorch_models_base`

Found by running `train.py` and reading each error, as asked:

| # | Symptom | Cause | Fix |
|---|---|---|---|
| 1 | `weight of size [32, 2, 3, 3], expected input[64, 3, 32, 32] to have 2 channels` | `channel` and `classes` swapped in `model.py` | first conv uses `channel`, last linear uses `classes` |
| 2 | `weight of size [64, 64, 3, 3], expected input ... to have 64 channels, but got 32` | second conv input size | `Conv2d(32, 64, 3)` |
| 3 | `mat1 and mat2 shapes cannot be multiplied (57344x14 and 12544x4600)` | flatten commented out | `torch.flatten(model_output, start_dim=1)` |
| 4 | `mat1 and mat2 shapes cannot be multiplied (64x4600 and 6400x3200)` | linear sizes do not chain | `Linear(4600, 3200)` |
| 5 | checkpoint `model_ce_0.pt` for an epoch with 60 % validation accuracy | name used the last batch accuracy | name uses `batch_acc_val` |
| 6 | `ModuleNotFoundError: No module named 'venv_hack'` with `ros2 run` | flat imports only work inside the folder | `from pytorch_models_base.xxx import ...` |
| 7 | "Using CPU for Torch" although CUDA is available | `--nocuda` was `type=bool` with default `"False"`, and `bool("False")` is True | `action='store_true'` |

Not bugs, but needed: with learning rate 1e-3 the network collapses to a single class (the
softmax saturates), hence 1e-4 or 5e-5; `plt.show()` at the end of `train.py` waits for the plot
window to be closed (`MPLBACKEND=Agg` avoids it). The lab PC's Quadro P400 is too old for the
installed cuDNN, so everything was trained on the CPU. The nodes build the model as
`CNNModel(3, classes, dropout)`, like `train.py`.

### 4.4 Objective 2: shore follower

**Task and labels.** Keep the shore on the right at d* = 1.5 m at a constant 0.3 m/s.
`shore_follower_observe` saves each camera image with label 0 if the angular command is below
-0.2 rad/s (turn right), 2 if above 0.2 (turn left), 1 otherwise. (The drive node's enum calls 0
LEFT; the code only relies on the sign.)

**Network command (`shore_follower_drive.py`, `image_to_rot`).** The whole image is shrunk to
32x32 and divided by 255. Instead of the argmax, the command is the expected turn:
`angular = 0.4 x (p_left - p_right)`, which is smoother when the network hesitates.

**Expert (`project2_tools/dagger.py`).** Uses the ground-truth pose and the distance field to the
chosen shore (the outer shore with the obstacles less than 3 m from it, or the island with the
cube). Target heading = the shore tangent, plus `atan(1.5 - d)` (at most 0.8 rad) to come back
to 1.5 m, measured 0.4 m ahead of the robot; angular command = 1.2 x heading error, limited to
0.5 rad/s.

**Steering kicks.** While recording, every 3 to 7 s an extra ±0.3 to 0.5 rad/s is added to the
executed command for 0.8 to 2 s. The recorded label is always the clean expert command
(`shore_follower_observe` listens to `/expert/twist`), so the data contains recoveries.

**DAgger.** The trained network drives (`/net/twist`), the expert keeps publishing its labels,
and takes over if d > d* + 1.5 m, d < 0.7 m or the heading error is above 75 degrees, giving
control back when |d - d*| < 0.3 m and the heading error is below 0.3 rad. The new images are
added to the dataset and the network is retrained.

**Cleaning.** `filter_outliers.py` drops images whose black sky covers less than 20 % or more
than 70 % of the image: a person right in front of the camera, a rolled robot, or a robot stuck
against the shore.

**The four networks.**

| | Data | Images | Training |
|---|---|---|---|
| A | outer shore, expert with kicks (`raw_sim1`, `raw_sim2`) | 9476 | lr 1e-4, collapsed at epoch 9, best epoch kept |
| B | A + one DAgger round driven by A (`raw_dagger1`) | 13066 | lr 5e-5, 12 epochs |
| C0 | island, expert with kicks (`shore_island/raw_exp1`) | 4498 | lr 5e-5, 12 epochs |
| C | C0 + one DAgger round driven by C0 (`shore_island/raw_dagger1`) | 8089 | lr 5e-5, 12 epochs |

Validation accuracy is only 67 to 71 % for all of them: labels near the 0.2 rad/s threshold are
ambiguous, and validation accuracy does not predict driving quality: network A has 70 % and,
driving alone without the expert, it left the shore within a minute. The closed-loop evaluation
is what matters.

**Evaluation protocol (`eval_net.sh`).** Restart the simulation, start the drive node with the
model, let the expert bring the robot to the shore, then the network drives under the same
takeover rules as DAgger (no recording). Three laps per network (one 1-lap run and one 2-lap
run). Metrics per lap: autonomy (% of time the network drives), takeovers per lap, and the
distance error |d - d*| while the network drives.

**Results** (mean ± std over 3 laps; expert alone for reference: |d - d*| = 0.13 m outer,
0.06 m island):

| Network | Track | Autonomy | Takeovers / lap | |d - d*| | Incidents |
|---|---|---|---|---|---|
| A | outer | 64 ± 3 % | 14.3 ± 1.9 | 0.37 m | |
| B | outer | 86 ± 1 % | 4.0 ± 0.0 | 0.30 m | |
| C (cross) | outer | 61 ± 4 % | 15.8 ± 0.9 | 0.28 m | 2 roll-overs |
| C0 | island | 86 ± 6 % | 2.3 ± 0.9 | 0.23 m | |
| C | island | 81 ± 10 % | 3.7 ± 1.9 | 0.35 m | |
| B (cross) | island | 74 ± 2 % | 5.7 ± 0.5 | 0.36 m | |

What it shows:
- DAgger on the outer shore: takeovers per lap 14.3 to 4.0. Trained on expert data only, the
  robot zigzags in and out of the band; after DAgger it holds 1.5 to 2 m for long stretches.
- On the island the DAgger round did not help. C0 already drove 84 % of its DAgger round, so
  that round probably added few new difficult situations.
- Each network is worse on the shore it was not trained on.
- Takeovers cluster where the shore shape changes sharply: the tree in the north-east bay of
  the outer shore and the cube on the west side of the island.
- Walking people are not part of the labels. Both roll-overs (C on the outer shore) happened
  right after people reached the robot.
- Limits: one training run per condition, three laps per network, an expert that uses the
  ground-truth pose.

## 5. Reproducing everything

Commands are in `project2_tools/README.txt`. The order:

1. Floor data: `record.launch.py` plus `tour.py` (or the joystick), twice;
   `split_dataset.py`; `train_floor_plane.sh`; `evaluate_model.py` on `val` and on the second
   session.
2. Shore data: `rec_session.sh` in expert mode (`none` instead of a model),
   `filter_outliers.py`, `split_dataset.py`, `train_shore_follower.sh <data folder>`;
   then `rec_session.sh` again with the trained model (DAgger), filter, re-split both sessions,
   retrain.
3. Evaluation: `eval_net.sh` for each network and track (`run_all_evals.sh`,
   `run_more_laps.sh` are the exact runs used), then `analyze_eval.py` with
   `runs_final.json`, `runs_outer.json`, `runs_island.json`.
4. Video: `make_video.py` (uses `compose_video.py`, `metrics_table.py`, `comparison_bars.py`).

The scripts in `project2_tools` run the simulator headless on `ROS_DOMAIN_ID=42` so they do not
disturb a GUI session on 69; only `watch_floor.sh` and `watch_shore.sh` use your current domain.

## 6. Where everything is

**Code changed in the workspace (`~/ros_workspace/src`):**

| Package | Files |
|---|---|
| `floor_plane_record_base` | `src/floor_plane_extract.cpp` (check_thumb), `launch/record.launch.py`, `scripts/split_dataset.py` |
| `floor_plane_classify_torch_base` | node (`load_model`, `check_thumb`), `scripts/train_floor_plane.sh`, `scripts/evaluate_model.py` |
| `pytorch_models_base` | `model.py`, `parser.py`, `train.py` (the 7 fixes) |
| `shore_follower_observe` | `launch/record.launch.py` (output folder argument) |
| `shore_follower_drive_torch_base` | node (`load_model`, `image_to_rot`), `launch/start.launch.py`, `scripts/train_shore_follower.sh` |
| `project2_tools` | simulation, expert, DAgger, evaluation and video scripts (not a ROS package) |

The empty `floor_plane_classify_base` and `shore_follower_drive_base` folders are leftovers; the
real starter packages are the `_torch_base` ones. Nothing is committed to git.

**Data (`~/data`):**

| Path | Content |
|---|---|
| `floor_plane/raw_sim1`, `raw_sim2`, `train`, `val`, `eval` | floor sessions, split, evaluation |
| `floor_plane/output_20261013_162545/models/model_ce_99.pt` | floor classifier |
| `shore_follower/raw_sim1`, `raw_sim2`, `raw_dagger1` | outer shore data |
| `shore_follower/old_v2/output_20261013_180724/models/model_ce_70.pt` | network A |
| `shore_follower/output_20261013_184009/models/model_ce_71.pt` | network B |
| `shore_island/raw_exp1`, `raw_dagger1` | island data |
| `shore_island/old_c0/output_20261105_104715/models/model_ce_67.pt` | network C0 |
| `shore_island/output_20261105_111525/models/model_ce_69.pt` | network C |
| `shore_follower/eval/` | evaluation logs (`*_log.npy`), `analysis/` figures and metrics |
| `videos/` | all videos, `slides/` |
| `sim_tools/` | the copy of the tools the experiments ran from (absolute paths) |
| `project2_code.zip` | the code to hand in |

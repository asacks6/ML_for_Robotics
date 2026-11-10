# Final project: treasure search with the VSV

Scene: `treasure_search.ttt`. The truck drives around the dry lake with the shore on its right, the arm keeps the detector above the shore, and the objects found are published as markers.

| Objective | Node | Method |
|---|---|---|
| 1. Locate the objects | `treasure_detector` | Each pass over an object gives one estimate: the mean of the tool positions, weighted by the detector value |
| 2a. Arm tip follows the shore | `arm_follower` | CNN on the 32x32 kinect image, trained on your demonstrations (3 classes: towards the truck, hold, away) |
| 2b. Tool height | `arm_follower` | Proportional control on the kinect depth |
| 3. Truck follows the shore | `truck_follower` | `angular.z = k1 y + k2 theta`, with `y` and `theta` measured by the line laser |

## Folder

```
~/ros_workspace/src/final_project/
  vrep_vsv_driver/      course package, unchanged
  vsv_shore_observe/    recorder, adapted from shore_follower_observe
  vsv_treasure/         the three nodes, launch files, training scripts, RViz config
  data/                 recordings and trained models (link to this PC's local disk)
```

The three packages are built in `~/ros_workspace` like the others. Terminals that were already open before the build need `source ~/ros_workspace/install/setup.bash` once. After editing C++ run `colcon build --symlink-install --packages-select vsv_shore_observe`. Python and launch files need no rebuild.

No virtual environment is needed in the terminals: the launch file and the training script load PyTorch themselves.

`data/` is on the local disk of gtlpc102 (`/var/tmp/asacks/final_project_data`), because the shared home sometimes fills up. To run on another PC, copy `data/arm/model.pt` (300 MB) there and pass it with `model:=`.

## Controller (SHANWAN gamepad)

| Control | Action |
|---|---|
| Left stick | Drive the truck |
| Right stick, left/right | Arm tip towards the truck / away from it |
| Right stick, up/down | Arm tip up / down |
| Cross, left/right | Arm tip forward and backward (not needed) |
| A | Deploy the arm (done automatically at start) |
| B | Park the arm |
| X | Move the arm with the stick. Needed once after every deploy |
| LB / RB | Truck: you drive / it drives itself |
| LT / RT | Arm: you move it / it moves itself |
| Y | Pause and resume the recording |

The course launch file `vsv_geom_mux.launch.py` doesn't fit this gamepad (it uses buttons the pad doesn't have, and a trigger as an arm axis), so `teleop.launch.py` is a copy of it with the axes and buttons as arguments.

To check the numbers, run `ros2 topic echo /joy` with the teleop running and press each button. Expected positions in `buttons`: A 0, B 1, X 3, Y 4, LB 6, RB 7, LT 8, RT 9. If one differs, pass it to the launch file, for example `arm_auto_button:=5`. The list of arguments is at the top of `vsv_treasure/launch/teleop.launch.py`.

## 1. Start

Terminal 1, simulator:

1. `csim`
2. Open `/cs-share/pradalier/ros2_ws/src/scenes/treasure_search.ttt` and press Play.

Terminal 2, drivers and joystick:

```
ros2 launch vsv_treasure teleop.launch.py
```

The arm deploys by itself. Press **X** once it has stopped moving.

Check the speed of the simulation once:

```
ros2 run vsv_treasure sim_rate.py
```

The real-time factor must be close to 1. If it is clearly above 1, enable real-time mode in CoppeliaSim (the clock button in the toolbar, with the simulation stopped) and press Play again. The arm is moved in real time, so a simulation running faster than that makes the truck too fast for the arm.

## 2. Record the demonstration for the arm

You only move the arm tip sideways. The truck and the tool height are automatic.

Terminal 3:

```
ros2 launch vsv_treasure teach.launch.py
```

RViz opens with a top view (grid, truck and true treasure positions), the kinect image and the cabin camera.

1. Drive to the shore with the left stick, going around the brown mound next to the start. Turn left before reaching the grass, so the truck ends up parallel to the shore with the grass 2 or 3 m to its right, the side of the arm. The truck then goes around the lake anticlockwise.
2. Press **RT**: the tool goes down to its working height. The right stick still moves it sideways.
3. Move the tool until the kinect image is half tiles, half grass.
4. Press **RB**: the truck starts following the shore at 0.4 m/s.

Terminal 4, once the truck is moving:

```
ros2 launch vsv_shore_observe record.launch.py
```

It prints `Image counter at N (towards hold away)` and saves into `data/arm/raw_<date>/`.

How to demonstrate:

- Watch only the kinect image. Tiles on the left, grass on the right. The goal is the border in the middle.
- Mostly tiles: push the right stick to the right, until the border is back in the middle.
- Mostly grass: push it to the left.
- Border near the middle: release the stick.
- Push the stick fully. A push below 12 % of the stick counts as "hold".
- Press **Y** to pause when something goes wrong (the truck leaves the shore, you lose the border for a long time). Fix it, then press **Y** again.
- If the truck does something you don't like, **LB** gives it back to you, and **RB** returns it to automatic.

One full lap is enough (about 15 minutes). Each class stops at 1500 images. Stop the recorder with Ctrl+C.

You can record several sessions. Each one gets its own `raw_<date>` folder and the training uses all of them.

## 3. Train

```
ros2 run vsv_treasure train_arm.sh
```

It splits all the sessions into `train/` and `val/` (by blocks of 50 consecutive images), trains the course network (`CNNModel` from `pytorch_models_base`, 3 classes) for 15 epochs on the CPU, and links the best model as `data/arm/model.pt`. It takes about 10 minutes. The curves are saved as `data/arm/loss.png` and `data/arm/acc.png`.

Stop the simulation while it trains, the two compete for the CPU.

## 4. Run everything

With the simulator and `teleop.launch.py` running (and **X** pressed):

```
ros2 launch vsv_treasure auto.launch.py
```

1. Drive next to the shore as before.
2. Press **RT**: the arm goes down and looks for the border by itself.
3. Press **RB**: the truck follows the shore.

The detected objects appear in RViz as red cylinders with their number and position. The simulator publishes the true positions as the TF frames `Treasure1` to `Treasure5`, also shown in RViz, so the error can be read directly. The terminal prints one line per detection.

To show objective 2a alone, press only **RT** and drive the truck yourself.

Arguments: `linear_vel:=0.4` (truck speed), `target_distance:=2.5` (distance to the shore), `model:=<file.pt>`, `rviz:=false`.

## Parameters

All in `vsv_treasure/launch/auto.launch.py`.

| Parameter | Value | Meaning |
|---|---|---|
| `lateral_vel` | 0.5 m/s | Arm speed when the network is sure |
| `target_height` | 0.35 m | Kinect to ground distance. The kinect sees nothing closer than 0.2 m |
| `height_gain`, `vertical_vel` | 1.0, 0.3 m/s | Height control gain and speed limit |
| `max_reach` | 3.9 m | The arm doesn't extend further than this from the truck axis |
| `linear_vel` | 0.4 m/s | Truck speed |
| `target_distance` | 2.5 m | Truck axis to shore. The arm reaches from 0.8 to about 4 m |
| `k_distance`, `k_angle` | 0.15, 0.3 | `k1` and `k2` of the steering law |
| `approach_limit` | 0.04 rad/s | Maximum turn rate towards the shore |
| `shore_percentile` | 50 | Which of the remembered shore points beside the arm gives the distance. Lower keeps the truck further from grass that sticks out |
| `threshold` | 0.3 | Detector value that starts a pass over an object |
| `merge_distance` | 3 m | Two estimates closer than this are the same object |

## How it works

### Objective 1: `treasure_detector`

- Inputs: `/vrep/metalDetector` and the tool position in the world, from TF (`world` to `VSV/Tool`).
- A pass starts when the detector goes above `threshold` and ends after 1 s below it.
- All the measurements of the pass give one estimate: the mean of the tool positions, each weighted by `value - threshold`.
- If the estimate is closer than `merge_distance` to an object already found, the two are averaged (second lap). Otherwise it is a new object.
- Output: `/treasure_detector/markers`, a red cylinder and a label per object.

The label also shows the peak value of the pass. A peak near 1 means the tool went over the object, and the estimate is good to a few tens of cm. A lower peak means the tool only went near it: the estimate is then the closest point of the tool's path, and the object is further out. In the scene script the detector is `exp(-d^2 / 8)` plus up to 0.1 of noise, so a peak of 0.6 is about 2 m away.

### Objective 2a: `arm_follower`, lateral motion

Recording (`vsv_shore_observe`): each kinect image is saved with the lateral velocity that was being sent to the arm (`/arm_ik/twist`, `linear.x`). Label 0 is towards the truck, 1 is hold, 2 is away.

Driving: the image is reduced to 32x32 and goes through the network, which gives three probabilities. The command is `lateral_vel * (p_away - p_towards)`, so the arm slows down when the network hesitates.

### Objective 2b: `arm_follower`, height

The kinect looks straight down, so its depth image is the height above the ground. The node takes the closest 5 % of the image, which makes the tool rise before something sticks out, and sends `height_gain * (target_height - closest)` as vertical velocity. If most of the image is invalid the ground is closer than the kinect can see, and the tool goes up.

Both commands go out in one twist on `/arm_mux/autoCommand`. The arm can't go up when it is fully stretched, so beyond `max_reach` it stops moving away from the truck.

In teaching mode (`teach.launch.py`) there is no network: the lateral command is the one from your stick, and the height control is the same. That way the images you record are taken at the working height.

### Objective 3: `truck_follower`

The line laser on the cabin scans the ground from side to side, 6.6 m in front of the rear axle.

1. Every pixel of the scan is placed in the truck frame, using its depth and TF.
2. Grass has little blue, tiles are grey. The shore is the first grass pixel to the right of the truck axis. This is the far point.
3. The far points are remembered in world coordinates. When the truck gets there, the median of the points within 2 m of the arm gives the distance to the shore beside it. This is the near point.
4. `y` is the near distance minus `target_distance`. `theta` is the angle of the line from the near point to the far point.
5. `angular.z = -k_distance * y - k_angle * theta`, at constant speed.

Turning towards the shore is limited to `approach_limit`. In a narrow inlet the shore jumps away, and the truck shouldn't follow it in. Turning away from the shore has no limit other than the truck's 5 m turning radius.

The simplest idea in the assignment, steering from how far the arm is stretched, was tried first. It followed straight shore but drove onto the grass at the first corner, because the arm is beside the truck and can't see the shore ahead. The laser looks ahead, so the truck starts turning in time.

## What was added to the course code

| File | Change |
|---|---|
| `vsv_shore_observe/src/vsv_shore_observe.cpp` | Copy of `shore_follower_observe.cpp`. New parameter `~/command_field`: which part of the twist makes the label (`angular.z` before, `linear.x` for the arm) |
| `vsv_shore_observe/launch/record.launch.py` | Kinect image, arm twist, dated output folder, pause button |
| `vsv_treasure/launch/teleop.launch.py` | Copy of `vsv_geom_mux.launch.py` with the joystick mapping as arguments |
| `vsv_treasure/vsv_treasure/arm_follower.py` | Based on `shore_follower_drive.py`: same network and image preparation, output on the arm, plus the height control |
| `vsv_treasure/vsv_treasure/truck_follower.py` | New |
| `vsv_treasure/vsv_treasure/treasure_detector.py` | New |
| `vsv_treasure/scripts/train_arm.sh`, `split_dataset.py` | Same as in Project 2, for 3 classes |

`vrep_vsv_driver` and the scene are unchanged.

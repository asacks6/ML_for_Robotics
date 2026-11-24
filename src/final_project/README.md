# Final project: treasure search with the VSV

Scene: `treasure_search.ttt`. The truck drives around the dry lake with the shore on its right, the arm keeps the detector above the shore, and the objects found are published as markers.

| Objective | Node | Method |
|---|---|---|
| 1. Locate the objects | `treasure_detector` | Each pass over an object gives one estimate: the mean of the tool positions, weighted by the detector value |
| 2a. Arm tip follows the shore | `arm_follower` | CNN on the 32x32 kinect image, trained on your demonstrations (3 classes: towards the truck, hold, away) |
| 2b. Tool height | `arm_follower` | Proportional control on the kinect depth |
| 3. Truck follows the shore | `truck_follower` | `angular.z = v (k1 y + k2 theta)`, with `y` and `theta` measured by the line laser |

## Folder

```
~/ros_workspace/src/final_project/
  vrep_vsv_driver/      course package, unchanged
  vsv_shore_observe/    recorder, adapted from shore_follower_observe
  vsv_treasure/         the three nodes, launch files, training scripts, RViz config
  data/                 recordings and trained models (link to ~/final_project_data)
```

The three packages are built in `~/ros_workspace` like the others. Terminals that were already open before the build need `source ~/ros_workspace/install/setup.bash` once. After editing C++ run `colcon build --symlink-install --packages-select vsv_shore_observe`. Python and launch files need no rebuild.

No virtual environment is needed in the terminals: the launch file and the training script load PyTorch themselves.

`data/` links to `~/final_project_data`. It is in your home, so every lab PC sees it, but outside the git repository: each model is 300 MB, more than GitHub accepts.

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
2. Open `/cs-share/pradalier/ros2_ws/src/scenes/treasure_search.ttt`.
3. Before pressing Play, click **Simulation > Toggle real-time mode**. The status bar says `Toggled to real-time simulation mode.`
4. Press Play.

Step 3 is required. The scene is saved with real-time mode off, and on the lab PCs it then runs about 3 times faster than real time. The arm controller (`vsv_arm_ik`) works on the real clock, so the arm becomes 3 times too slow compared with the truck, and you would have to react 3 times faster than normal. The setting is kept through Stop and Play, but not when the scene is opened again.

Terminal 2, drivers and joystick:

```
ros2 launch vsv_treasure teleop.launch.py
```

The arm deploys by itself. Press **X** once it has stopped moving.

To check the speed:

```
ros2 run vsv_treasure sim_rate.py
```

The real-time factor must be close to 1.0. `arm_follower` also prints a warning every 5 s while it isn't.

## 2. Record the demonstration for the arm

The network only sees the kinect image: about 40 cm of ground at the tool, in 128x128 pixels reduced to 32x32. For each image it learns which way you pushed the right stick. To follow the meanders, it has to learn two things:

- Small corrections while the border drifts in the image, as the truck gets closer to or further from the shore.
- What to do when the border is far to one side, or gone from the image. That happens in sharp meanders. A careful driver rarely shows it, so you create those situations on purpose (recoveries, below).

You only move the arm tip sideways. The truck and the tool height are automatic.

Terminal 3:

```
ros2 launch vsv_treasure teach.launch.py
```

RViz opens with a top view (grid, truck and true treasure positions), the kinect image and the cabin camera.

1. Drive to the shore with the left stick, going around the brown mound next to the start. Turn left before reaching the grass, so the truck ends up parallel to the shore with the grass 2 or 3 m to its right, the side of the arm. The truck then goes around the lake anticlockwise.
2. Press **RT**: the tool goes down to its working height. The right stick still moves it sideways.
3. Move the tool until the kinect image is half tiles, half grass.
4. Press **RB**: the truck starts following the shore at 0.25 m/s.

Terminal 4, once the truck is moving and the border is centred:

```
ros2 launch vsv_shore_observe record.launch.py
```

Its first line must say `Recording into /home/GTL/asacks/ros_workspace/src/final_project/data/arm/raw_<date>`. Then it prints `Image counter at N (towards hold away)` for every image saved.

How to demonstrate:

- Watch only the kinect image. Tiles are on the left (the truck's side), grass on the right. Keep the border on the vertical centre line.
- New ground enters at the bottom of the image. If the border at the bottom edge is off-centre, the shore is turning: start moving now, before it reaches the middle. This is how the network learns to anticipate a meander.
- Mostly tiles: push the right stick to the right. Mostly grass: push it to the left. Border centred: let go.
- Push the stick fully. A push below 12 % of the stick counts as "hold".
- **Recovery**, every 20 to 30 s. The truck keeps driving meanwhile, which is fine: it steers with the line laser and doesn't depend on the arm.
  1. Pause first, then move the tool off the border by 0.5 to 1 m. Alternate the sides: sometimes until the image is all tiles, sometimes all grass. Keep it short, 2 to 3 s.
  2. Start pushing back towards the border, and resume while you are already pushing.
  3. Let go when the border is centred.

  Only the return is recorded. An image saved while the stick is released is labelled "hold", so don't resume with the tool off the border and the stick idle.
- The truck drives itself, so your left thumb is free. `record.launch.py pause_button:=10` puts pause on the Select (Back) button, and the right thumb can stay on the stick. Pressing it must print `Learning interruped` in the recorder terminal, then `Learning started` the next time. If it doesn't, keep **Y**.
- Press **Y** to pause before anything you don't want learned: the arm stopped at its reach limit in a deep inlet, the truck crossing grass, the border lost for a long time.
- If the truck does something you don't like, **LB** gives it back to you, and **RB** returns it to automatic.

One full lap is enough (about 19 minutes at 0.25 m/s). Each class stops at 1500 images. If at the end of the lap one counter is far behind, do a few more recoveries that need that direction. Stop the recorder with Ctrl+C.

You can record several sessions. Each one gets its own `raw_<date>` folder and the training uses all of them.

## 3. Train

```
ros2 run vsv_treasure train_arm.sh
```

It splits all the sessions into `train/` and `val/` (by blocks of 50 consecutive images), trains the course network (`CNNModel` from `pytorch_models_base`, 3 classes) for 15 epochs on the CPU, and links the best model as `data/arm/model.pt`. It takes about 10 minutes. The curves are saved as `data/arm/loss.png` and `data/arm/acc.png`.

A validation accuracy around 0.7 is normal. Near the centre the choice between "hold" and a small push is arbitrary, so the classes overlap there. The node doesn't use the most likely class: it moves at `lateral_vel * (p_away - p_towards)`, so an unsure network moves the arm slowly.

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

If the arm loses the border at some places, record a second session (section 2) with more recoveries there, then run `train_arm.sh` again. It trains on all the sessions.

Arguments: `linear_vel:=0.25` (truck speed, use the one you recorded at), `target_distance:=2.7` (distance to the shore), `model:=<file.pt>`, `rviz:=false`.

## Parameters

All in `vsv_treasure/launch/auto.launch.py`.

| Parameter | Value | Meaning |
|---|---|---|
| `lateral_vel` | 0.5 m/s | Arm speed when the network is sure |
| `target_height` | 0.35 m | Kinect to ground distance. The kinect sees nothing closer than 0.2 m |
| `height_gain`, `vertical_vel` | 1.0, 0.3 m/s | Height control gain and speed limit |
| `max_reach` | 3.9 m | The arm doesn't extend further than this from the truck axis |
| `linear_vel` | 0.25 m/s | Truck speed. At 0.4 m/s the kinect view crosses the image in about 1 s, too fast to demonstrate the meanders |
| `target_distance` | 2.7 m | Truck axis to shore. The arm reaches from 0.8 to 3.9 m |
| `k_distance`, `k_angle` | 0.375, 0.75 | `k1` and `k2` of the steering law, per metre travelled. At 0.4 m/s this is 0.15 and 0.3 rad/s |
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
5. `angular.z = v * (-k_distance * y - k_angle * theta)`, at the constant speed `v`. Multiplying by `v` makes the truck turn the same amount per metre at any speed, so changing the speed doesn't change its path.

The median ignores inlets and peninsulas shorter than its 4 m window, so the truck doesn't swerve into every notch. The only limit on turning is the truck's 5 m minimum radius (`vsv_driver`).

### Limits of the truck

Measured in the simulator against the true shoreline, one lap at 0.25 m/s (two laps for each setting, within 0.3 % of each other):

| Setting | Rear axle on grass | Front-right wheel on grass (deepest) | Shore within the arm's reach |
|---|---|---|---|
| Shore at 2.5 m, turn towards it at 10 m radius at most | 4 % of the lap | 9.6 % (2.3 m) | 83 % |
| Shore at 2.5 m, no extra limit | 2.5 % | 9 % (1.7 m) | 85 % |
| Shore at 2.7 m, no extra limit (used) | 1.1 % | 7.2 % (1.4 m) | 83 % |

The truck runs onto the grass at the narrow peninsulas, mostly around treasures 1, 4 and 5. It's already turning as hard as it can there: the line laser only sees 6.6 m ahead, and the truck can't turn tighter than a 5 m radius. On about 11 % of the lap the shore is further than the arm can reach (deep inlets, the narrowest at treasure 3), and on about 6 % it is too close. No setting removes both: moving the truck away from the shore trades grass driving for unreachable inlets. A tighter 3.5 m turning radius for the truck didn't help either. So the arm can't follow the edge everywhere, whatever the network does.

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

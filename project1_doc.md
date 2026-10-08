# Project 1: traversability map, cylinder detection and Bayesian map

## 0. The project in one page

The robot (a Summit XL in CoppeliaSim, called `bubbleRob` in TF) drives around
a 10 x 10 m room with a Kinect depth camera. The project asks for three things:

| Objective | Question it answers | What was built |
|---|---|---|
| 1 | Where can the robot drive? | A 2D map where each 10 cm cell is *traversable*, *not traversable* or *unknown* |
| 2 | Where are the cylinders? | A detector that finds cylinders in the point cloud and keeps a map of all of them |
| 3 | How sure are we of the map? | The same map as objective 1, but each cell holds a probability updated with Bayes rule |

To fill the whole map, the robot also needed a way to look around. A new task
was added to the task manager that makes the robot turn 360 degrees on the spot,
and a mission that follows the road graph and turns at every node.

**Yes, objective 3 uses Bayesian inference.** Every cell holds the probability
that it is traversable, and every new observation updates it with Bayes rule.
The update is written in log-odds form, which is the "log-ratio" representation
the assignment mentions. Section 4 explains it from scratch with a worked
example.

Results in simulation: the whole arena is mapped, and 99.7 % of the cells away
from object boundaries are correctly labelled. All 6 cylinders of the scene are
found, with a position error of at most 4 mm and no false detection.

## 1. The pieces and how the data flows

```
CoppeliaSim (rosControlKinect3d.ttt)
   |  /vrep/kision/depth, /vrep/kision/camera_info, /tf
   v
vrep4_helpers/kinect_pc.launch.py        depth image -> 3D points
   |  /points   (16384 points per frame, in frame Vision_sensor)
   +-------------------------------+
   v                               v
floor_plane_mapping              cylinder_detector
   ~/labels          (obj 1)        ~/cylinders        (obj 2, MarkerArray)
   ~/probability     (obj 3)        ~/vertical_points  (debug cloud)
   ~/traversability  (obj 3)
   |                               |
   +---------------+---------------+
                   v
             RViz2 (project.rviz)

explore_scan.py -> floor_nav task server (GoTo, Scan) -> /mux/autoCommand
                -> topic_tools mux -> /vrep/twistCommand -> robot wheels
```

What was added to the workspace:

| Item | Purpose |
|---|---|
| [src/floor_plane_mapping/](src/floor_plane_mapping/) | New package, objectives 1 and 3 |
| [src/cylinder_detector/](src/cylinder_detector/) | New package, objective 2 |
| [src/floor_nav/tasks/TaskScan.cpp](src/floor_nav/tasks/TaskScan.cpp) | New task: rotate 360 degrees on the spot |
| [src/floor_nav/missions/explore_scan.py](src/floor_nav/missions/explore_scan.py) | New mission: graph tour with a scan at every node |
| [project.launch.py](src/floor_plane_mapping/launch/project.launch.py) | Starts everything except the simulator and the mission |
| [project.rviz](src/floor_plane_mapping/rviz/project.rviz) | RViz layout used in the video |
| `evaluation.txt` in each new package | Short technical summary with the formulas and the numbers |

The only change to existing code is two lines in `floor_nav/CMakeLists.txt`, one
to build the new task and one to install the new mission.

## 2. Background you need first

### 2.1 The point cloud

The Kinect in this scene is a 128 x 128 depth camera with a 57 degree field of
view, seeing from 0.2 to 5 m. `kinect_pc.launch.py` turns each depth image into
128 x 128 = 16384 3D points. The points are expressed in the frame of the camera
(`Vision_sensor`). The camera sits about 0.43 m above the ground, tilted down
by about 10 degrees.

### 2.2 TF: from the camera to the world

A point "1 m in front of the camera" means nothing for a map, because the camera
moves. The map has to be fixed in the room, so every point is converted into the
`world` frame first. The scene publishes the chain of frames

```
world -> odom -> bubbleRob -> Vision_sensor
```

and the assignment says this localisation is perfect. Asking TF for the
transform `world <- Vision_sensor` at the timestamp of the cloud and applying it
to every point gives the points in room coordinates. This is the same code as
in your RANSAC node, only with `world` instead of `bubbleRob` as the target.

The translation part of that transform is also useful by itself: it is the
position of the camera in the room, which is needed to know how far each point
is from the sensor.

### 2.3 Occupancy grid

A map here is an image. Cell `(i, j)` of a `cv::Mat` stands for the square of
the floor between `x = -5.5 + 0.1 i` and `x + 0.1`, and the same for `y` with
`j`. ROS has a message for exactly this, `nav_msgs/OccupancyGrid`. Each cell is
a number: `0` means free (here: traversable), `100` means occupied (here: not
traversable), and `-1` means unknown. RViz draws it as a grey level image lying
on the floor.

### 2.4 The scene, and why it matters

Before choosing any threshold, the scene file was opened with a small script run
inside CoppeliaSim, to read the true shape of the floor and the true position of
every object. That gave the ground truth used in section 7, and it showed what
"traversable" must mean in this scene:

- The floor is a heightfield with two flat plateaus, one at z = -0.5 (south) and
  one at z = +0.5 (north).
- They are joined in the middle by a ramp of about 13 degrees (through graph
  node 0). The robot can drive on it.
- On both sides of the ramp the transition is a cliff of 30 to 60 degrees. The
  robot cannot drive on it.
- Objects: 6 cylindrical pillars (0.8 m tall, radius 0.10 to 0.175 m), 3 square
  boxes (0.2 x 0.2 x 1 m), 2 sofas, 3 plants in pots, and the walls.

So the mapper must accept 13 degrees and reject 30 degrees and above. The
threshold of 20 degrees comes from there. And the cylinder detector must find
the 6 pillars but not the boxes, sofas or plants.

## 3. Objective 1: the traversability map

**Idea in one sentence:** for each 10 cm square of floor, take the points that
fell in it, fit a plane through them, and call the square traversable if that
plane is flat and close to horizontal.

All of this happens in `pointCloudCallback` of
[floor_plane_mapping.cpp](src/floor_plane_mapping/src/floor_plane_mapping.cpp),
once per point cloud.

### 3.1 Peas in buckets

The assignment suggests "a function linking map coordinates to lists of
points", that is, throwing each point into the bucket of the cell below it.
That is what the code does:

```cpp
int i = floor((p.x() - info_.origin.position.x) / resolution_);
int j = floor((p.y() - info_.origin.position.y) / resolution_);
Bucket & b = buckets[j*labels_.cols + i];
```

The grid is **110 x 110 cells of 10 cm**, fixed in the `world` frame, covering
x and y from -5.5 m to +5.5 m: the 10 x 10 m arena plus 0.5 m of margin outside
the walls. These come from the launch parameters `resolution` (0.1), `width` and
`height` (11.0 m) and `origin_x`, `origin_y` (-5.5). The same grid is used for
the labels of objective 1 and the probabilities of objective 3, so bucket
`(i, j)` always updates map cell `(i, j)`.

Buckets are only created for the cells that receive points in the current
frame (they live in a hash map keyed by `j*110 + i`), and they are thrown away
after each frame. With the camera seeing at most 3 m ahead, a frame typically
updates about 200 of the 12100 cells; the map itself keeps everything.

Points closer than 0.3 m or farther than 3 m from the camera are thrown away
first, because far points are too sparse to be useful (see 3.3).

One difference with the suggestion: a bucket does not store the list of points.
It only stores three running sums:

```
n           number of points
S  = sum p        (a 3-vector)
SS = sum p p^T    (a 3x3 matrix)
```

The plane fit below only needs the mean and the covariance of the points, and
both come straight from these sums:

```
mean        m = S / n
covariance  C = SS / n - m m^T
```

So the result is exactly the same as with lists, without storing 16384 points
in lists at every frame. The points are taken relative to the centre of their
cell before being added, so that `SS` does not lose precision.

### 3.2 Fitting a plane with PCA

The covariance matrix `C` describes the shape of the cloud of points inside the
cell. Its eigenvectors are the main axes of that shape, and its eigenvalues are
the spread (variance) along each axis.

- Points on a flat floor form a thin pancake: two large eigenvalues (the points
  spread over the 10 cm of the cell in two directions) and one tiny one. The
  eigenvector of the tiny eigenvalue is the direction in which the points do
  **not** spread, which is the normal of the plane.
- Points on the side of a pillar form a vertical sheet. The normal is
  horizontal.

From the smallest eigenvalue `l0` and its eigenvector `normal`:

```
slope      = acos(|normal_z|)      angle between the plane and the horizontal
roughness  = sqrt(l0)              thickness of the points around the plane (m)
```

Why not reuse the `z = a x + b y + c` fit from the regression and RANSAC
homeworks? That model cannot represent a vertical surface: for a wall, `a` and
`b` go to infinity and the least squares system becomes singular. Many obstacle
cells contain exactly that (sides of pillars, boxes, walls). PCA works for any
orientation, and a vertical surface simply gives a slope of 90 degrees.

### 3.3 Cells that cannot be judged

Far from the robot, the floor is seen at a grazing angle and two consecutive
rows of the depth image hit the floor far apart. With the camera 0.43 m above
the ground, the gap is about `0.018 d^2` metres at distance `d`: 7 cm at 2 m,
16 cm at 3 m. A 10 cm cell far away is then crossed by a single row of points,
which is a line, and a line does not define a plane.

In that case the middle eigenvalue is also tiny, and the code skips the cell
for this frame (`min_spread`) instead of computing a meaningless slope. Cells
with fewer than 6 points are skipped too.

### 3.4 The three tests

A cell is labelled traversable when all three hold:

| Test | Threshold | Why |
|---|---|---|
| slope | < 20 degrees | ramp is 13 degrees, cliffs are 30 to 60 degrees |
| roughness | < 2 cm | a cell mixing floor and the base of an object is not a clean plane |
| step | < 5 cm | the centroid of each neighbouring cell must lie within 5 cm of this cell's plane |

The step test exists for flat surfaces that are not on the floor, like the seat
of a sofa: locally it is flat and horizontal, but its border has a jump with the
floor next to it. Without the test it would pass the first two checks.

### 3.5 Writing the label

For objective 1 the rule is the simplest possible: the last observation wins.

```cpp
labels_(j,i) = o.traversable ? TRAVERSABLE : OBSTACLE;
```

`labels_` is a `cv::Mat_<uint8_t>`, the OpenCV image the assignment asks for. It
directly holds the OccupancyGrid values (0, 100, and 255 which reads as -1 once
converted to the signed type of the message). Cells never observed keep the
initial value, unknown.

### 3.6 Publishing

`mat_to_og` is the function from `wifi_map_base`, copied and slightly adapted (in
`wifi_map_base` it is a member of the wifi node and cannot be called from
another package). A timer publishes the maps once per second, with a "latched"
QoS so that RViz receives the last map even if it starts later. When the node
stops, the maps are also written as PNG images with `cv::imwrite`; the images
in [src/floor_plane_mapping/results/](src/floor_plane_mapping/results/) come
from the final run.

## 4. Objective 3: the Bayesian filter

### 4.1 Why the objective 1 map is not enough

"Last observation wins" trusts every observation completely. But observations
can be wrong:

- a cell seen from 3 m away only has a few points, and its plane is unreliable;
- a cell on the edge of an object sometimes gets the floor points, sometimes the
  object points, and its label flips from frame to frame.

What we want instead is a belief that grows with the number of agreeing
observations, where a reliable observation counts more than a doubtful one, and
where one bad observation does not erase many good ones. That is exactly what a
Bayesian filter gives.

### 4.2 The model

For one cell:

```
State (unknown, what we want):  x in {T, N}    T = traversable, N = not traversable
Measurement (one per frame):    z in {t, n}    output of the tests of section 3.4
Prior (before any measurement): P(T) = P(N) = 0.5
```

Two assumptions:

1. The world does not change (a cell that is traversable stays traversable).
2. Given the true state of the cell, the measurements are independent of each
   other.

### 4.3 The sensor model

The sensor model says how much we trust one measurement. It is symmetric: the
probability of a correct answer is `p`, whatever the true state.

```
P(z = t | T) = P(z = n | N) = p(r)       correct answer
P(z = t | N) = P(z = n | T) = 1 - p(r)   wrong answer
```

`p` depends on the distance `r` between the camera and the cell. This is how the
"long range updates are imprecise" remark of the assignment is modelled:

```
p(r) = p_near + (p_far - p_near) * min(r / r_max, 1)
p_near = 0.9,  p_far = 0.6,  r_max = 3 m
```

| Distance | p | Meaning |
|---|---|---|
| 0 m | 0.90 | right 9 times out of 10 |
| 1.5 m | 0.75 | right 3 times out of 4 |
| 3 m | 0.60 | barely better than a coin toss |

These three values were chosen by reasoning, not measured. They could be
calibrated by comparing single observations with the ground truth of section 7.

### 4.4 Applying Bayes rule

After the k-th measurement, Bayes rule says:

```
P(x | z_1..z_k) = eta * P(z_k | x) * P(x | z_1..z_k-1)
```

The new belief is the old belief multiplied by how well the new measurement fits
each hypothesis, and `eta` is whatever number makes `P(T) + P(N) = 1`.

To get rid of `eta`, write the same rule for `T` and for `N` and divide one by
the other, so `eta` cancels:

```
P(T | z_1..z_k)     P(z_k | T)     P(T | z_1..z_k-1)
---------------  =  ----------  *  -----------------
P(N | z_1..z_k)     P(z_k | N)     P(N | z_1..z_k-1)
```

Then take the logarithm, which turns the product into a sum. Call
`l = log(P(T) / P(N))` the **log-odds** of the cell:

```
l_k = l_k-1 + log( P(z_k | T) / P(z_k | N) )
l_0 = log(0.5 / 0.5) = 0
```

With the sensor model of 4.3, the term added is

```
if z = t :   + log( p / (1 - p) )
if z = n :   - log( p / (1 - p) )
```

and the probability is recovered at any time with

```
P(T) = 1 - 1 / (1 + exp(l))
```

`l = 0` means 50/50, a large positive `l` means surely traversable, a large
negative `l` means surely not.

### 4.5 In the code

The whole filter is these lines of `pointCloudCallback`, run for every cell
observed in the current frame (`o.range` is the mean distance of the cell's
points to the camera):

```cpp
double p = p_near_ + (p_far_ - p_near_) * std::min(1.0, o.range / max_range_);
double dl = log(p / (1 - p));
double l = log_odds_(j,i) + (o.traversable ? dl : -dl);
log_odds_(j,i) = std::max(-l_max_, std::min(l_max_, l));
```

`log_odds_` is a `cv::Mat_<float>` with one log-odds value per cell, starting at
0. `probaTraversable` converts it back to `P(T)`.

### 4.6 Worked example

A cell is seen 3 times as traversable from 1 m, then once as not traversable
from 3 m (a bad far observation). At 1 m, `p = 0.8` so each step adds
`log(0.8/0.2) = 1.39`. At 3 m, `p = 0.6` so the step is `log(0.6/0.4) = 0.41`.

| Step | Measurement | l | P(T) |
|---|---|---|---|
| start | none | 0 | 0.50 |
| 1 | t at 1 m | +1.39 | 0.80 |
| 2 | t at 1 m | +2.77 | 0.94 |
| 3 | t at 1 m | +4.16 | 0.98 |
| 4 | n at 3 m | +3.75 | 0.98 |

The confidence grows with each agreeing observation (0.80, 0.94, 0.98), and the
one far contradicting observation barely moves it. The objective 1 map, with
"last observation wins", would now say *not traversable*, which is wrong.

### 4.7 Link with the "+1 / -1" counter

The assignment warns that adding +1 or -1 to a cell gives a similar behaviour.
It is in fact the same filter: a counter is the log-odds `l` with a constant
step of 1, which corresponds to a constant `p = e / (1 + e) = 0.73`. The Bayesian
version gives the counter a meaning (it is a probability once passed through
`1 - 1/(1+exp(l))`) and lets the step depend on how reliable the measurement
is, which a plain counter cannot do.

### 4.8 Why the value is clamped

`l` is kept between -4.6 and +4.6, which is P between 0.01 and 0.99.

The reason is assumption 2 of section 4.2. The camera sends about 55 frames per
second here, and two consecutive frames see the same cell from almost the same
place, so they are not independent at all: they are close to the same
measurement repeated. Without a bound, `l` would grow to hundreds after a few
seconds, the filter would be absurdly sure of itself, and a cell could never
change its mind again. With the bound, a cell at the limit needs 3 contrary
observations at close range (or 5 at 1.5 m, 14 at 3 m) to change label.

### 4.9 What is published

- `~/probability`: `100 * P(N)` per cell, and -1 if never observed. With the RViz
  "map" colours, traversable cells are white, obstacles black, and uncertain
  cells grey.
- `~/traversability`: the probability turned back into the three labels of
  objective 1. Traversable if `P(T) > 0.7`, not traversable if `P(T) < 0.3`,
  unknown otherwise.

### 4.10 What the results show

In this simulation, the objective 1 map and the Bayesian map reach the same
score (99.7 %). That is because simulated depth has no noise: almost every
observation is right, so "last observation wins" already works. The two maps
only disagree on cells whose label flips between frames, at object edges and
far away. On a real Kinect, with noisy depth, the difference would be much
larger.

At 55 frames per second most cells hit the bound (0.01 or 0.99) within a second,
which is why the probability map looks almost black and white at the end of the
run. The grey cells left are those that really receive contradicting
observations.

## 5. Objective 2: cylinder detection

**Idea in one sentence:** the pillars stand vertically, so seen from above their
surface is a circle; keep only the points that belong to vertical surfaces, and
look for circles among them.

All of this is in
[cylinder_detector.cpp](src/cylinder_detector/src/cylinder_detector.cpp).

### 5.1 Keep only vertical structure

The floor is not flat (plateaus, ramp, cliffs), so it cannot be removed with a
single plane as in the RANSAC homework. Instead a small grid of 5 cm cells is
built around the robot, and each cell remembers the lowest and highest point
that fell in it.

- A vertical surface piles up points of many heights in the same cell: the side
  of a pillar spans tens of centimetres.
- The ground does not: over 5 cm, the 13 degree ramp rises 1 cm and even the
  60 degree cliff only 9 cm.

So a cell is "vertical" when `z_max - z_min > 0.2 m`. In those cells, the few
floor points lying under the object (less than 3 cm above `z_min`) are dropped.

### 5.2 Group the points into objects

The vertical cells form an image (255 = vertical, 0 = not).
`cv::connectedComponents` gives a label to each group of touching cells, so each
object seen becomes one cluster of points.

### 5.3 Find a circle: RANSAC, then least squares

This is the same two-stage scheme as your RANSAC floor plane, applied to circles
in the horizontal plane:

1. **RANSAC.** A plane needs 3 points, and so does a circle. Draw 3 random
   points of the cluster, compute the circle passing through them, and count the
   points within 1 cm of it. Keep the best circle over 200 draws. Circles with a
   radius outside 7 to 30 cm are ignored.
2. **Least squares.** Refit the circle on its inliers. Written as
   `x^2 + y^2 + D x + E y + F = 0`, the circle equation is linear in `D, E, F`,
   so it is solved exactly like the regression homework (normal equations with
   `ldlt`). Then `center = (-D/2, -E/2)` and `r = sqrt(D^2/4 + E^2/4 - F)`.

As in the RANSAC homework, RANSAC decides which points belong to the circle, and
least squares decides where the circle is.

### 5.4 Accept or reject the circle

RANSAC always returns *some* circle, even on a box. These tests decide whether
it is really a cylinder:

| Test | Rejects |
|---|---|
| at least 30 points on the circle | small noisy clusters |
| among the points near the circle (within r + 5 cm of the centre), at least 90 % are on it | boxes, pieces of wall, plants |
| the points on the circle cover at least 90 degrees of arc | short flat faces |
| the centre is farther from the camera than the points | concave shapes (inside of a corner) |
| the points on the circle span at least 0.4 m in height | sofa armrests |

The second test only looks *near* the circle, so a pillar touching a wall still
passes (one pillar of the scene does).

### 5.5 Keep a map of all the cylinders

Each detection is compared with the cylinders already known. If one is closer
than its radius plus 15 cm, it is the same cylinder seen again, and the
estimates are merged. Otherwise a new cylinder is created.

Merging is a weighted average of the centres and radii, with weight
`w = 1 / d^2` where `d` is the distance to the camera. The reason: the error on
the position of a point grows with the size of a pixel on the object, which
grows like `d`, so the variance grows like `d^2`, and weighting by the inverse
of the variance is the standard way to average measurements of different
quality. A close view of a cylinder therefore counts much more than a far one.

A cylinder is only published after it has been detected in 3 frames, so a
single wrong fit never reaches the map. All cylinders found since the start
are republished at every frame in the MarkerArray, each one as an orange
cylinder with a label showing its radius `r` and its number of detections `n`.

### 5.6 How the thresholds were tuned

A bag of the depth images and TF of a full mission was recorded, then replayed
through the detector with different settings:

| Ratio on circle | Min height | Pillars found | False detections |
|---|---|---|---|
| 0.7 | 0.3 m | 6 / 6 | 9 (3 plant pots, 2 boxes, 4 on sofa armrests) |
| 0.9 | 0.3 m | 6 / 6 | 1 (sofa armrest, 0.31 m tall) |
| 0.9 | 0.4 m | 6 / 6 | 0 |

Why boxes passed with 0.7: a small simulation of a 0.2 m square seen from 0.8 to
2.5 m showed that the best circle through a box corner keeps 60 to 70 % of the
nearby points, while a real cylinder keeps 100 % (the simulated depth has no
noise). 0.9 separates the two cleanly.

### 5.7 Assumptions

- Cylinders are vertical. This is true for every cylinder of the scene; a
  cylinder lying on its side would not be found.
- The plant pots are small real cylinders (radius 7.5 cm, 16.5 cm tall) under
  leaves. They are deliberately not reported: the leaves around them keep the
  ratio below 0.9. Lowering the ratio would bring them back, but the boxes
  would come back too.

## 6. Exploration: the Scan task

Following the road graph alone leaves holes in the map, because the camera only
sees 57 degrees in front of the robot. As the assignment suggests, a scanning
behaviour was added to the task framework:
[TaskScan.cpp](src/floor_nav/tasks/TaskScan.cpp) makes the robot rotate on the
spot and adds up how much it has turned since the start of the task, stopping
after a full turn. The amount turned is added up instead of comparing the
heading with its initial value, because the heading jumps from +180 to -180
degrees during the turn.

[explore_scan.py](src/floor_nav/missions/explore_scan.py) is `test_graph.py`
(same hand-made Hamiltonian path through the 12 nodes) with a `Scan` at the
start and after each `GoTo`. It also selects `/mux/autoCommand` on the mux by
itself (task `SetMuxGeneric`), so the manual service call is not needed.

## 7. Results and how they were measured

The ground truth comes from the scene file (section 2.4): the slope of the
heightfield in every cell, plus the footprint of every object. A band of one
cell around every boundary is left out, because the label of a cell that
straddles a boundary depends on how the points split inside it.

**Map** (final run, full mission, about 2.5 minutes):

| Measure | Value |
|---|---|
| observed cells | 10325 of 12100 (the whole arena; the grid has 0.5 m of margin outside the walls) |
| correct labels, away from boundaries | 99.7 % of 8743 cells |
| wrongly traversable | 0 |
| wrongly not traversable | 25, all just outside object footprints |

**Cylinders:**

| Pillar | True position | True r | Estimated position | Est. r | Error |
|---|---|---|---|---|---|
| P | (-2.575, 3.175) | 0.175 | (-2.575, 3.173) | 0.172 | 2 mm |
| P0 | (-3.025, -3.000) | 0.125 | (-3.024, -3.000) | 0.123 | 1 mm |
| P1 | (4.075, 0.325) | 0.100 | (4.078, 0.327) | 0.098 | 4 mm |
| P2 | (0.400, 4.775) | 0.125 | (0.398, 4.775) | 0.121 | 2 mm |
| P3 | (-2.675, 0.150) | 0.110 | (-2.677, 0.151) | 0.107 | 2 mm |
| P4 | (0.775, 1.950) | 0.125 | (0.773, 1.950) | 0.119 | 2 mm |

The radius is 2 to 6 mm too small, probably because the pillar meshes are made
of flat facets while the true radius above is measured at the corners.

How it was tested: three full runs with the simulator headless, the tuning
replays of section 5.6, and one full run with the CoppeliaSim GUI, all giving
the same results.

## 8. Did it follow the instructions?

| Instruction | Status | Notes |
|---|---|---|
| Copy and build the provided packages, use the 4 launch files | Done | Built with colcon; `project.launch.py` starts the same 4 launch files plus the new nodes and RViz |
| RViz with TF and the graph MarkerArray | Done | `project.rviz` |
| Select automatic mode on the mux | Done | Done by the mission itself |
| Obj 1: 2D matrix with labels {traversable, not traversable, unknown} | Done | `labels_`, a `cv::Mat_<uint8_t>` |
| Obj 1: traversable = flat with low angle to gravity | Done | slope < 20 degrees, roughness < 2 cm, plus the step test |
| Obj 1: publish as OccupancyGrid with `mat_to_og` | Done | Function copied from `wifi_map_base` |
| Obj 1: `cv::imshow` or `cv_bridge` | Not used | Presented as possible options; the OccupancyGrid in RViz replaces them, and the maps are saved as PNG |
| Use TF to project the clouds | Done | Cloud transformed into `world` at its timestamp |
| "Lists of points per cell" (peas in buckets) | Done, with a variant | Buckets keep sums instead of lists, which gives the same mean and covariance |
| "Copy your floor plane extraction software" | Adapted | Same node structure as your RANSAC node, but the plane per cell is fitted with PCA because the `z = ax+by+c` model fails on vertical surfaces |
| Obj 2: detect cylinders, MarkerArray | Done | `~/cylinders` |
| Obj 2: start from the RANSAC node | Done in spirit | Same RANSAC then least squares scheme, on circles instead of planes |
| Obj 2: keep ALL cylinders, consistent map, merge repeated observations | Done | Association plus weighted average, stable ids |
| Obj 3: traversability as a binary variable, Bayesian filter | Done | Binary Bayes filter, section 4 |
| Obj 3: confidence increasing with the number of observations | Done | Each agreeing observation adds to `l` |
| Obj 3: write the formulas before coding | Done | Section 4 here, and `floor_plane_mapping/evaluation.txt` |
| Obj 3: lower confidence for long range observations | Done | `p(r)` goes from 0.9 at 0 m to 0.6 at 3 m |
| Obj 3: log-ratios | Done | The filter is stored and updated as log-odds |
| New packages `floor_plane_mapping`, `cylinder_detector` | Done | |
| Scanning behaviour to fill holes | Done | `TaskScan` and `explore_scan.py` |

Things that go beyond or differ from the text, so you are not surprised:

- The cylinders are assumed vertical, and the plant pots are deliberately
  excluded (section 5.7).
- The sensor model values (0.9, 0.6) were chosen, not measured (section 4.3).
- `floor_nav` was extended (new task, new mission, two lines of CMake).
- Everything was tested in simulation only, where the simulator runs about 2.5
  to 3 times faster than real time.

## 9. Where to look in the code

| What | Where |
|---|---|
| Transform the cloud, buckets, PCA, tests, label and Bayes update | `pointCloudCallback` in [floor_plane_mapping.cpp](src/floor_plane_mapping/src/floor_plane_mapping.cpp) |
| Log-odds to probability | `probaTraversable` |
| Probability and three-label maps | `computeBayesMaps` |
| Publication once per second | `timerCallback`, `mat_to_og` |
| PNG export | destructor `~FloorPlaneMapping` |
| Vertical cells, clusters | `pointCloudCallback` in [cylinder_detector.cpp](src/cylinder_detector/src/cylinder_detector.cpp) |
| RANSAC, refit and acceptance tests | `fitCylinder` |
| Merging into the cylinder map | `integrate`, struct `Cylinder` |
| Markers | `publishMarkers` |
| Parameters | the two launch files in each package's `launch/` folder |

## 10. Questions you may be asked

**Why PCA and not RANSAC inside each cell?** A cell holds a few dozen points of
a single surface, so there are no outliers to reject; what is needed is the
orientation of that surface, including vertical ones, which is exactly what PCA
gives in one step.

**Why 10 cm cells?** Small enough to resolve the 20 cm obstacles, large enough
to receive enough points to fit a plane up to 2 or 3 m away.

**Is it really Bayesian if the code only adds numbers?** Yes. Adding log-odds is
Bayes rule written in logarithms (section 4.4). It is the standard binary Bayes
filter used for occupancy grids (Thrun, Burgard and Fox, *Probabilistic
Robotics*).

**Why does the probability map look black and white?** The camera gives about
55 frames per second, so each cell receives hundreds of observations and
reaches the bound of 0.01 or 0.99 quickly (section 4.10).

**Why clamp the probability?** Consecutive frames are not independent, which
breaks an assumption of the filter. Without a bound the map would become
overconfident and could never correct itself (section 4.8).

**What if the localisation were not perfect?** Every point would be placed in
the wrong cell by the pose error, so obstacles would be smeared and the
cylinder estimates would drift. The Bayesian map would partly absorb it,
because a wrongly placed observation is outvoted by the correct ones.

**What would change with a real Kinect?** Real depth is noisy, and the noise
grows with distance. The roughness and circle tolerances would have to grow
with it, and the range dependent confidence would matter much more than it
does in simulation.

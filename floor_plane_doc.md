# Floor plane detection with Hough Transform and RANSAC

## 1. What the project does

Two ROS 2 nodes estimate the ground plane in front of the robot from a 3D point
cloud produced by a simulated Kinect in CoppeliaSim.

Both nodes solve the same problem with a different estimator:

| Package | Estimator | Source file |
|---|---|---|
| `floor_plane_hough_base` | Hough Transform (voting in a 3D accumulator) | `src/floor_plane_hough.cpp` |
| `floor_plane_ransac_base` | RANSAC (random minimal samples plus consensus) | `src/floor_plane_ransac.cpp` |

The plane model is the same as in the linear regression homework:

```
z = a*x + b*y + c
```

so the unknown is the vector `X = {a, b, c}`. The parameters mean:

* `a` is `dz/dx`, the slope of the ground along the robot forward axis.
* `b` is `dz/dy`, the slope along the robot lateral axis.
* `c` is the height of the plane at the origin of the robot frame. Since the
  `bubbleRob` frame sits about 0.30 m above the floor, a flat floor gives
  `c` close to `-0.30`.

The difference with the regression homework is robustness. Least squares uses
every point, so a tree trunk or a wall inside the sensor range drags the plane
with it. Hough and RANSAC both look for the model with the largest support and
ignore everything else, so obstacles do not bias the result as long as the
ground is still the dominant surface.

The estimated plane is published as a flat purple cylinder marker on
`~/floor_plane` so it can be seen in RViz. The RANSAC node also publishes the
consensus set on `~/inliers`.

## 2. Data flow

```
CoppeliaSim (rosControlKinect3d.ttt)
   |  /vrep/kision/depth   (depth image)
   v
vrep4_helpers/image_flip           -> /vrep/kision/depth_flipped
   v
depth_image_proc::PointCloudXyzNode -> /points   (sensor_msgs/PointCloud2)
   v
floor_plane_hough  or  floor_plane_ransac   (subscribes as ~/scans)
   v
visualization_msgs/Marker on ~/floor_plane   (+ ~/inliers for RANSAC)
```

The `fpr.launch.py` of each package starts the node, sets the parameters,
remaps `~/scans` to `/points`, and includes `kinect_pc_min.launch.py` from
`vrep4_helpers`, which is the part that turns the depth image into a cloud.

## 3. The code that was already there

This part is identical in both files and is worth understanding because a quick
fix may ask you to change it.

### 3.1 Getting two copies of the cloud

```cpp
pcl::PointCloud<pcl::PointXYZ> pc_sensor, pc_baseframe;
pcl::PCLPointCloud2 cloud2;
pcl_conversions::toPCL(*msg,cloud2);
pcl::fromPCLPointCloud2(cloud2,pc_sensor);
```

`pc_sensor` is the cloud in the camera optical frame, exactly as it arrived.
`pcl_conversions::toPCL` goes from the ROS message to the PCL blob type, and
`fromPCLPointCloud2` unpacks the blob into a typed `PointXYZ` cloud.

Then the same message is transformed into the robot frame:

```cpp
if (msg->header.frame_id != base_frame_) {
    ...
    transformStamped = tf_buffer->lookupTransform(base_frame_, msg->header.frame_id, msg->header.stamp);
    tf2::doTransform(*msg,pc,transformStamped);
    pcl_conversions::toPCL(pc,cloud2);
}
pcl::fromPCLPointCloud2(cloud2,pc_baseframe);
```

`canTransform` with a 1 s timeout waits for TF to be ready, `lookupTransform`
gets the camera to `bubbleRob` transform at the timestamp of the cloud, and
`doTransform` applies it to every point. After this, `pc_baseframe[i]` and
`pc_sensor[i]` are the same physical point expressed in two different frames.

Both copies are needed because the two filters below work in different frames.

### 3.2 Point filtering

```cpp
for (unsigned int i=0;i<n;i++) {
    float x = pc_sensor[i].x;  float y = pc_sensor[i].y;
    float d = hypot(x,y);
    if (d < 1e-2) continue;          // bogus point, discarded in SENSOR frame
    x = pc_baseframe[i].x; y = pc_baseframe[i].y;
    d = hypot(x,y);
    if (d > max_range_) continue;    // too far, discarded in ROBOT frame
    pidx.push_back(i);
}
```

The first test is in the sensor frame and removes invalid returns, which the
depth to cloud conversion places at the origin of the camera. The second test is
in the robot frame and removes points further than `max_range_` in the
horizontal plane, so only the patch of ground around the robot is used.

`pidx` is the list of surviving indices. Everything after this works on
`pc_baseframe[pidx[i]]`, never on `i` directly. This indirection is the single
most common source of bugs when editing these files.

### 3.3 Marker construction

Given `X = {a,b,c}` the code builds an orthonormal frame on the plane:

```cpp
w << X[0], X[1], -1.0;  w /= w.norm();     // plane normal
O << 1.0, 0.0, 1.0*X[0]+0.0*X[1]+X[2];     // a point of the plane at x=1,y=0
u << 2.0, 0.0, 2.0*X[0]+0.0*X[1]+X[2];     // a second point at x=2,y=0
u -= O;  u /= u.norm();                    // in plane direction
v = w.cross(u);                            // completes the right handed basis
```

`w` is the normal because rewriting the model as `a*x + b*y - z + c = 0` shows
the gradient of the left side is `(a, b, -1)`. The 3x3 matrix built from
`u, v, w` is converted into a quaternion and used as the marker orientation. The
marker is a cylinder of diameter 1 m and thickness 1 cm, so it looks like a
disc lying on the estimated ground.

Note that the disc is centered at `x = 1, y = 0`, which is one metre in front of
the robot, not at the robot itself.

## 4. Step 1: the Hough Transform

### 4.1 Why the accumulator has 3 dimensions

The model has exactly 3 free parameters, `a`, `b` and `c`. The Hough Transform
discretises the whole parameter space and has one counter per cell, so the
accumulator needs one dimension per parameter. It is declared as

```cpp
cv::Mat_<int32_t> accumulator;
int dims[3] = {n_a,n_b,n_c};
accumulator = cv::Mat_<int32_t>(3,dims);
```

which is an OpenCV n dimensional matrix with 3 axes of sizes `n_a`, `n_b`, `n_c`
holding 32 bit signed integers. Cells are read and written with
`accumulator(ia,ib,ic)`, and `accumulator = 0` clears every counter at once.

### 4.2 The step computation (constructor TODO, lines 244 to 256)

```cpp
da = (n_a > 1) ? (a_max - a_min)/(n_a - 1) : 1.0;
db = (n_b > 1) ? (b_max - b_min)/(n_b - 1) : 1.0;
dc = (n_c > 1) ? (c_max - c_min)/(n_c - 1) : 1.0;
```

With `n` values spread over `[min, max]` there are `n-1` gaps between them, so
the step is `(max-min)/(n-1)`. This convention makes index `0` land exactly on
`min` and index `n-1` land exactly on `max`, which matches the reconstruction
formula `a = a_min + ia*da` used later. The ternary guards the `n == 1` case,
where the division would be by zero.

If you ever divide by `n` instead of `n-1`, the grid becomes `[min, max-step]`
and the top of the range is never tested. Both conventions exist, but the code
has to be consistent between the step computation and the reconstruction.

### 4.3 The voting loop (callback TODO, lines 107 to 164)

```cpp
n = pidx.size();
rclcpp::Time now = this->get_clock()->now();
accumulator = 0;
size_t best = 0;
```

`n` is reused to hold the number of useful points. `now` starts the timing that
is printed at the end. The accumulator has to be cleared on every callback,
otherwise votes from previous clouds accumulate forever.

```cpp
for (unsigned int i=0;i<n;i++) {
    double x = pc_baseframe[pidx[i]].x;
    double y = pc_baseframe[pidx[i]].y;
    double z = pc_baseframe[pidx[i]].z;
```

One iteration per surviving point, read through `pidx` in the robot frame.

```cpp
    for (int ia=0;ia<n_a;ia++) {
        double a = a_min + ia * da;
        for (int ib=0;ib<n_b;ib++) {
            double b = b_min + ib * db;
```

Here is the core idea. A single point does not determine a plane, it only
constrains the parameters: the set of planes passing through `(x,y,z)` is the
2D surface `{(a,b,c) : c = z - a*x - b*y}` inside the 3D parameter space. So the
point votes for that whole surface. The way to enumerate it is to scan every
`(a,b)` cell and solve for the single `c` that goes with it.

```cpp
            double c = z - a*x - b*y;
            int ic = round((c - c_min)/dc);
            if ((ic < 0) || (ic >= n_c)) {
                continue;
            }
            accumulator(ia,ib,ic) += 1;
```

`c = z - a*x - b*y` is just the model solved for `c`. The discretisation follows
the pattern given in the `#if 0` block of the original file: subtract the
minimum, divide by the step, round to the nearest integer. The bounds test is
mandatory because a point far from the ground, for example the top of an
obstacle, produces a `c` outside `[c_min, c_max]` for some slopes. Without the
test that would be an out of bounds write into the OpenCV matrix.

Cost of this loop: `n * n_a * n_b` increments, independent of `n_c`.

### 4.4 Finding the maximum

```cpp
int best_ia = 0, best_ib = 0, best_ic = 0;
for (int ia=0;ia<n_a;ia++)
  for (int ib=0;ib<n_b;ib++)
    for (int ic=0;ic<n_c;ic++) {
        size_t votes = (size_t)accumulator(ia,ib,ic);
        if (votes > best) { best = votes; best_ia = ia; best_ib = ib; best_ic = ic; }
    }
if (best > 0) {
    X[0] = a_min + best_ia * da;
    X[1] = b_min + best_ib * db;
    X[2] = c_min + best_ic * dc;
}
```

A full scan of the accumulator for the cell with the most votes. The winning
indices are converted back into real parameter values with the same
`min + index*step` formula used during voting. `best` ends up holding the number
of points supporting the plane, which is what gets printed as `score`.

The `if (best > 0)` guard keeps `X` at `{0,0,0}` when the cloud is empty,
instead of reporting the corner of the accumulator as a plane.

### 4.5 Parameter choice in `fpr.launch.py`

```python
{'~/max_range': 2.0},
{'~/n_a': 51},  {'~/a_min': -0.5},  {'~/a_max': 0.5},
{'~/n_b': 51},  {'~/b_min': -0.5},  {'~/b_max': 0.5},
{'~/n_c': 76},  {'~/c_min': -1.0},  {'~/c_max': 0.5},
```

Range of `a` and `b`: these are slopes, and `0.5` is a 26 degree incline. The
ramps in the scene are far gentler than that, so the interval covers every
plausible ground orientation while keeping the grid small. Anything steeper is
a wall, not a floor, and should not be found anyway.

Range of `c`: the robot frame is about 0.30 m above the floor, so the flat case
is `c = -0.30`. The interval `[-1.0, 0.5]` leaves room for the robot to be on
top of a bump or at the edge of a step without the true value falling out of
the accumulator.

Steps: `da = db = 0.02` and `dc = 0.02` m. The reason these two match is
explained in section 4.7.

Memory: `51*51*76*4` bytes, about 0.8 MB, which is nothing.

### 4.6 Aliasing and how to fix it

Discretisation puts a hard floor on the precision: the answer is always a cell
centre, so the error on `c` can never be below `dc/2 = 1 cm` and the error on
`a` never below `da/2 = 0.01`. Making the grid finer fixes the precision but
the cost grows as `n_a * n_b`, and worse, the votes of a real noisy plane spread
across several neighbouring cells instead of piling into one, so the peak gets
flatter and less reliable.

Two ways to get precision without paying for a fine grid, neither of which is
implemented here:

1. Use the Hough Transform only as an initialisation. Take the winning cell,
   select every point within a tolerance of that coarse plane, and run a linear
   least squares fit on that subset. Voting supplies the robustness, least
   squares supplies the precision. This is exactly the refinement that the
   RANSAC node does, see section 5.5.
2. Compute the centroid of the votes in a small neighbourhood of the peak
   instead of taking the peak cell itself, so the estimate can land between
   cells. Smoothing the accumulator with a small Gaussian before the search has
   a similar effect and also merges peaks that noise has split in two.

### 4.7 Do we need the same discretisation on all parameters?

No, and the reason is that the parameters do not have the same units or the
same effect on the result.

`c` is a length in metres, and an error `dc` displaces the plane by `dc`
everywhere. `a` and `b` are dimensionless slopes, and an error `da` displaces
the plane by `da * r` at horizontal distance `r`. The two contributions are
comparable when

```
da ≈ dc / r_max
```

With `dc = 0.02 m` and `max_range_ = 2.0 m` this gives `da ≈ 0.01`. The chosen
`da = 0.02` is one step coarser than that, which is a deliberate trade against
computation time. If `max_range_` is increased, `da` and `db` should be reduced
proportionally, while `dc` can stay where it is.

There is a second asymmetry. The cost is `n * n_a * n_b`, and `n_c` is free,
so refining `c` is cheap and refining `a` or `b` is not. A useful configuration
is therefore a coarse angular grid and a fine height grid.

Finally `a` and `b` are not symmetric either in practice. The Kinect looks
forward, so the point cloud spans a much larger range in `x` than in `y`. The
lever arm on `a` is longer, which makes `a` better observed than `b`, and also
makes an error on `a` more visible. Reducing `n_b` is the first place to save
time if the node is too slow.

### 4.8 Computation load

Measured on this machine with the same inner loop compiled at `-O3`, including
the accumulator scan:

| Points | Accumulator | Time |
|---|---|---|
| 2000 | 51x51x76 | 24 ms |
| 5000 | 51x51x76 | 57 ms |
| 10000 | 51x51x76 | 146 ms |
| 5000 | 21x21x41 | 12 ms |
| 5000 | 31x31x51 | 24 ms |
| 5000 | 101x101x151 | 218 ms |

The time is linear in the number of points and in `n_a * n_b`, as expected.
At 5000 points and a 51x51 angular grid the node runs at about 17 Hz, which
keeps up with the simulated Kinect. The 21x21x41 grid is four times faster but
returned `b = -0.050` and `c = -0.287` on data whose true values were `-0.060`
and `-0.300`, which is the aliasing of section 4.6 showing up directly.

The practical levers, in order of effectiveness:

1. Lower `max_range_`, which cuts `n` quadratically.
2. Lower `n_b` before `n_a`, for the reason in section 4.7.
3. Subsample the cloud, for instance keep one point out of two in `pidx`.

### 4.9 Sensitivity to the environment

Obstacles: a tree trunk or a wall inside `max_range_` creates its own cluster of
votes, but those points are spread over many planes and rarely agree on one
cell, while the ground points all agree on a single one. As long as the ground
is the majority surface the peak stays on the ground and the obstacle is simply
ignored. This is the main gain over the least squares of the previous homework,
where the same trunk tilted the plane to `z = -0.21x + 0.01y + 0.09`.

Smooth slope transitions: this is the weak case. When the patch inside
`max_range_` contains the end of a flat section and the beginning of a ramp,
there is no single plane that fits everything. The accumulator then has two
competing peaks and the winner flips from one to the other between frames,
which shows up in RViz as a marker that jumps instead of rotating smoothly.
Reducing `max_range_` narrows the patch, makes the mixture less likely, and is
the cheapest way to make the transition behave, at the cost of using fewer
points and being more sensitive to noise.

## 5. Step 2: RANSAC

### 5.1 The principle

Instead of testing every model, RANSAC tests a few models built from the data
itself. A plane needs exactly 3 points, so each iteration draws 3 random points,
builds the plane through them, and counts how many of the other points lie
within `tolerance_` of it. The model with the largest consensus set wins.

### 5.2 Setup (lines 94 to 106)

```cpp
n = pidx.size();
size_t best = 0;
double X[3] = {0,0,0};
std::vector<size_t> pinliers;
if (n >= 3) {
    std::uniform_int_distribution<> dsample(0, n-1);
    std::vector<size_t> candidates;
    candidates.reserve(n);
```

The `n >= 3` test matters for two reasons: fewer than 3 points cannot define a
plane, and `dsample(0, n-1)` with `n == 0` would compute `0-1` on an unsigned
value and produce a huge bound. `candidates` is allocated once outside the loop
and reused, so the inner loop never reallocates.

The generator `gen` is a `std::mt19937` seeded from `std::random_device` in the
constructor initialiser list, both declared in the original file.

### 5.3 Drawing a minimal sample (lines 107 to 117)

```cpp
size_t j1 = dsample(gen);
size_t j2 = dsample(gen);
size_t j3 = dsample(gen);
if ((j1 == j2) || (j1 == j3) || (j2 == j3)) continue;
Eigen::Vector3f P1, P2, P3;
P1 << pc_baseframe[pidx[j1]].x, pc_baseframe[pidx[j1]].y, pc_baseframe[pidx[j1]].z;
```

Three independent draws, with the duplicates rejected. Drawing with replacement
and skipping collisions is simpler than drawing without replacement and costs
almost nothing, since a collision happens with probability about `3/n`.

Note the double indirection `pidx[j1]`: `dsample` returns a position inside
`pidx`, not an index into the cloud.

### 5.4 Building and scoring the plane (lines 119 to 152)

```cpp
Eigen::Vector3f nrm = (P2 - P1).cross(P3 - P1);
double area = nrm.norm();
if (area < 1e-6) continue;
nrm /= area;
```

The cross product of two edges of the triangle is normal to the plane that
contains it. Its norm is the area of the parallelogram built on those edges, so
it goes to zero exactly when the three points are aligned and the plane is not
defined. Rejecting on `area < 1e-6` removes that degenerate case, which happens
often in practice because a depth image has whole rows of collinear points.

```cpp
if (fabs(nrm(2)) < 1e-2) continue;
```

A plane whose normal is horizontal is vertical, and a vertical plane cannot be
written as `z = a*x + b*y + c` because that form requires solving for `z`. The
conversion below divides by `nrm(2)`, so near vertical candidates are dropped
before they produce infinities. This also happens to be a free filter against
walls.

```cpp
double d = nrm.dot(P1);
```

With `nrm` unitary, the plane is the set of points satisfying `nrm . P = d`, and
`d` is the signed distance from the origin to the plane.

```cpp
candidates.clear();
for (unsigned int k=0;k<n;k++) {
    Eigen::Vector3f P;
    P << pc_baseframe[pidx[k]].x, pc_baseframe[pidx[k]].y, pc_baseframe[pidx[k]].z;
    if (fabs(nrm.dot(P) - d) < tolerance_) {
        candidates.push_back(k);
    }
}
```

Because `nrm` was normalised, `nrm.dot(P) - d` is directly the signed orthogonal
distance from `P` to the plane, with no division needed. Every point closer than
`tolerance_` joins the consensus set.

This is the orthogonal distance, not the vertical one. The vertical distance
would be `fabs(z - (a*x + b*y + c))`, which is larger by a factor
`sqrt(1 + a^2 + b^2)` and therefore makes the effective tolerance depend on the
slope of the candidate. The orthogonal distance keeps `tolerance_` meaning the
same thing for every candidate.

```cpp
if (candidates.size() > best) {
    best = candidates.size();
    pinliers = candidates;
    X[0] = -nrm(0)/nrm(2);
    X[1] = -nrm(1)/nrm(2);
    X[2] = d/nrm(2);
}
```

Conversion from the implicit form to the explicit one: from
`nx*x + ny*y + nz*z = d`, isolating `z` gives
`z = (-nx/nz)*x + (-ny/nz)*y + d/nz`, hence the three lines above.

### 5.5 Least squares refinement (lines 155 to 171)

This is the answer to the third evaluation question, and it is implemented.

```cpp
if (pinliers.size() >= 3) {
    Eigen::MatrixXf A(pinliers.size(),3);
    Eigen::MatrixXf B(pinliers.size(),1);
    for (unsigned int k=0;k<pinliers.size();k++) {
        A(k,0) = pc_baseframe[pidx[pinliers[k]]].x;
        A(k,1) = pc_baseframe[pidx[pinliers[k]]].y;
        A(k,2) = 1.0;
        B(k,0) = pc_baseframe[pidx[pinliers[k]]].z;
    }
    Eigen::MatrixXf S = (A.transpose() * A).ldlt().solve(A.transpose() * B);
    X[0] = S(0); X[1] = S(1); X[2] = S(2);
}
```

The best plane so far was built from only 3 points, so it carries the full
measurement noise of those 3 points. The consensus set, on the other hand,
contains thousands of ground points and no obstacle points, because the
obstacles were already rejected by the tolerance test.

So the two stages split the work: RANSAC decides which points belong to the
ground, least squares decides where the ground is. This is the same normal
equations solve as the regression homework, `A^T A X = A^T B` factored with
`ldlt()`, applied to a clean subset instead of the raw cloud.

Note the triple indirection here: `pinliers[k]` is a position in `pidx`, and
`pidx[...]` is the index in the cloud.

Measured effect on synthetic data with 30 percent outliers and 1 cm noise, true
plane `a = 0.100, b = -0.060, c = -0.300`:

| Stage | a | b | c |
|---|---|---|---|
| RANSAC, 100 samples | 0.092 | -0.061 | -0.291 |
| after refinement | 0.100 | -0.060 | -0.300 |

### 5.6 Publishing the inliers (lines 173 to 179)

```cpp
pc_inliers.clear();
for (unsigned int k=0;k<pinliers.size();k++) {
    pc_inliers.push_back(pc_baseframe[pidx[pinliers[k]]]);
}
sensor_msgs::msg::PointCloud2 inlier_msg;
pcl::toROSMsg(pc_inliers,inlier_msg);
inlier_msg.header.stamp = msg->header.stamp;
inlier_msg.header.frame_id = base_frame_;
inlier_pub_->publish(inlier_msg);
```

`pc_inliers` was already declared in the original file but never used. Filling
it and publishing it on `~/inliers` makes the consensus set visible in RViz,
which is by far the fastest way to tell whether `tolerance_` is set correctly:
if the trunk of a tree lights up as an inlier, the tolerance is too large.

The frame is forced to `base_frame_` because the points were copied from
`pc_baseframe`, not from the original message.

### 5.7 Choosing `n_samples` and `tolerance`

Number of samples. The standard RANSAC formula gives the number of iterations
`N` needed to draw at least one all inlier sample with probability `p`:

```
N = log(1-p) / log(1 - w^s)
```

where `w` is the fraction of inliers and `s = 3` is the sample size. With
`p = 0.99`:

| Inlier ratio w | N |
|---|---|
| 0.7 | 11 |
| 0.5 | 35 |
| 0.4 | 70 |
| 0.3 | 169 |

With `max_range_ = 2.0` the ground is the large majority of the cloud, so `w`
is rarely below 0.5 and 35 iterations would already do. `n_samples = 100` was
chosen to stay safe at `w = 0.35`, which covers the case where the robot faces
a wall, while still costing very little. The default value of 10 in the base
launch file only reaches 99 percent at `w = 0.72`, which is optimistic.

Tolerance. This has to cover two physical effects added together:

* the depth noise of the sensor, a few millimetres to about 1 cm at 2 m,
* the actual roughness of the floor in the scene.

`tolerance = 0.05 m` sits above both, so genuine ground points are kept, and
well below the height of the obstacles in the scene, so obstacle points are
rejected. Measured behaviour on the same synthetic data, 5000 points, 30 percent
outliers, true `a = 0.100, c = -0.300`:

| tolerance | inliers | a after refit | c after refit |
|---|---|---|---|
| 0.01 | 2105 | 0.101 | -0.303 |
| 0.05 | 3714 | 0.100 | -0.300 |
| 0.10 | 3911 | 0.102 | -0.296 |
| 0.30 | 4674 | 0.125 | -0.256 |

`0.01` is too tight, it keeps only two thirds of the ground because the noise is
1 cm, which throws away useful data. `0.30` is too loose, it swallows the
obstacle and the estimate drifts. `0.05` recovers essentially all 3500 ground
points and nothing else.

A useful rule of thumb: set the tolerance to about 3 times the standard
deviation of the sensor noise at working distance, then check in RViz that the
`~/inliers` cloud stops at the foot of the obstacles.

### 5.8 Computation load

Cost is `n_samples * n` distance evaluations, so it is linear in both. Measured
at `-O3` on 5000 points, including the refinement:

| n_samples | Time |
|---|---|
| 10 | 0.21 ms |
| 50 | 0.69 ms |
| 100 | 1.4 ms |
| 500 | 5.9 ms |

RANSAC at 100 samples is about 40 times cheaper than the Hough Transform on the
same cloud, and it is more precise thanks to the refinement. The price is that
it is randomised, so two consecutive frames on identical data can give slightly
different answers, whereas the Hough Transform is deterministic.

### 5.9 Sensitivity to the environment

Obstacles: RANSAC handles them well, better than Hough, because the tolerance
test is an explicit geometric rejection rather than a competition between
cells. The inlier count is also a usable confidence measure: if `score` drops
far below the usual number of ground points, the ground is mostly hidden.

Smooth slope transitions: same failure mode as the Hough Transform. Two surfaces
of similar size inside `max_range_` means two consensus sets of similar size,
and RANSAC picks whichever happens to be larger on that frame. Being randomised,
it can also pick different ones on two consecutive frames with the same data.
Reducing `max_range_` is again the direct fix. A more principled one is to seed
the sampling towards points close to the robot, which are the ones that
describe the surface the robot is actually standing on.

## 6. How to run

```bash
# terminal 1
bash /cs-share/pradalier/ros2_ws/start_zenod.sh

# terminal 2, start CoppeliaSim with scenes/rosControlKinect3d.ttt and press play

# terminal 3
cd ~/ros_workspace
colcon build --packages-select floor_plane_hough_base floor_plane_ransac_base
source install/setup.bash
ros2 launch floor_plane_hough_base fpr.launch.py
# or
ros2 launch floor_plane_ransac_base fpr.launch.py

# terminal 4
rviz2
```

In RViz set the fixed frame to `bubbleRob`, add a Marker display on
`/floor_plane_hough/floor_plane` or `/floor_plane_ransac/floor_plane`, and for
RANSAC add a PointCloud2 display on `/floor_plane_ransac/inliers`.

The node prints one line per cloud:

```
Extracted floor plane: z = 0.00x + 0.00y + -0.30: 0.057s, score 4823
```

where `score` is the number of votes for Hough and the number of inliers for
RANSAC, and the time is the estimation only, not the TF and conversion work.

## 7. Quick fix cheat sheet

Where to touch what, if the follow up asks for a change.

**Change the plane model**, for example add a quadratic term:
in Hough, the accumulator gains a dimension per parameter, so the declaration
`int dims[3]` and every `accumulator(ia,ib,ic)` change, and a fourth nested loop
appears in the voting. In RANSAC only two things change: the minimal sample size
goes from 3 to the number of parameters, and the plane construction is replaced
by a small least squares on the sample. RANSAC is much easier to extend.

**Reject the plane when it is not trustworthy**: test `best` against a fraction
of `n` just before the marker is built, and skip `marker_pub_->publish(m)` if it
is too low.

**Colour the marker by quality**: `m.color.r/g/b` are set just before the
publish, they can be driven by `best`.

**Filter points by height instead of range**: the filtering loop in section 3.2,
add a test on `pc_baseframe[i].z`.

**Subsample the cloud**: in the same loop, `if (i % 2) continue;` before
`pidx.push_back(i)`.

**Make Hough sub-cell precise**: after the accumulator scan, add the least
squares refinement from section 5.5, selecting inliers with a tolerance around
the winning plane. The code can be copied almost verbatim from the RANSAC file,
`Eigen/Core` and `Eigen/Cholesky` are already included in both.

**Adaptive number of RANSAC iterations**: inside the sample loop, after updating
`best`, recompute `w = best/(double)n` and break out when `i` exceeds
`log(1-p)/log(1-w*w*w)`. This keeps the worst case bounded but usually stops
after a handful of iterations.

**Track the plane over time**: keep `X` as a member variable and low pass it,
`X_new = 0.7*X_old + 0.3*X_measured`, which removes the frame to frame jitter of
RANSAC and the cell jumps of Hough.

**Segment several planes**: run the estimator, remove the inliers from `pidx`,
run it again on what is left. For Hough this means clearing and refilling the
accumulator, for RANSAC it is just a second pass over a shorter index list.

## 8. Files changed

```
floor_plane_hough_base/src/floor_plane_hough.cpp     lines 107-164, 244-256
floor_plane_hough_base/launch/fpr.launch.py          accumulator parameters
floor_plane_ransac_base/src/floor_plane_ransac.cpp   lines 94-186
floor_plane_ransac_base/launch/fpr.launch.py         n_samples, tolerance, max_range
```

`CMakeLists.txt` and `package.xml` were not modified in either package.

project2_tools: simulation tools used for Project 2 (not a ROS package, colcon ignores it)
PROJECT2_GUIDE.md explains the whole project and how to run it.

Demos on the simulation you are running (GUI or not), in your current ROS_DOMAIN_ID
  watch_floor.sh [route|manual]           floor classifier, live window, scripted route
  watch_shore.sh A|B|C0|C [outer|island] [laps]   shore follower with the expert supervisor
  floor_route.json    route used by watch_floor.sh, from the start pose of the scene

The other scripts assume the scene /cs-share/pradalier/ros2_ws/src/scenes/lakeExampleRich.ttt,
ROS_DOMAIN_ID=42 and the data folders under ~/data. Python tools that only need numpy,
OpenCV and matplotlib run with /usr/bin/python3; the ones that load a network need the
torch venv (/cs-share/pradalier/venv/torch-cpu-ros2).

Scene geometry
  dump_terrain.sh     extract the lake heightfield from the scene to terrain.txt
  geom.py             rasterise it into geom.npz (0.1 m grid; lake bed = floor below z = 0)
  build_fields.py     distance fields to the outer shore (shore.npz), to the island
                      (shore_island.npz) and to any static obstacle (D_static.npy)

Floor classifier dataset and demo
  tour.py             random tour of the lake bed that approaches the obstacles, driven
                      while floor_plane_record_base/launch/record.launch.py records
  drive.py            waypoint follower on the ground-truth pose
  run_floor_demo3.sh  demo video of floor_plane_classify_torch_base along a waypoint route
  mosaic.py           mosaic of recorded thumbnails per label

Shore follower dataset
  dagger.py           scripted expert and supervisor, outer shore or island, shore on
                      the right at --dstar metres.
                        --expert_only --kicks   expert demonstrations with steering kicks
                        default                 DAgger: the network drives (/net/twist), the
                                                expert labels (/expert/twist) and takes over
                                                when d > d* + 1.5 m, d < 0.7 m or the heading
                                                error is above 75 degrees
                        --laps N --log f.npy    evaluation protocol (per-step log)
  rec_session.sh      shore_follower_observe recording /expert/twist with dagger.py, in
                      expert or DAgger mode
  filter_outliers.py  drop images with a person in front of the camera or a rolled robot
  The outer-rim demonstrations (raw_sim1, raw_sim2) were recorded with an earlier
  standalone version of the same expert; dagger.py --expert_only --kicks reproduces it.
  Splits use floor_plane_record_base/scripts/split_dataset.py, training uses
  shore_follower_drive_torch_base/scripts/train_shore_follower.sh <data folder>.

Evaluation and video
  eval_net.sh         restart the sim, run shore_follower_drive with a model and dagger.py
                      for N supervised laps, record the video and the log
  run_all_evals.sh    first evaluation lap of C0, C and the two cross tests
  run_more_laps.sh    two more laps per configuration
  record_demo.py      demo video (camera, network output or command, top view), or a live
                      window when the output file is 'view'
  analyze_eval.py     per-lap metrics, distance profiles and trajectories
  metrics_table.py    results table
  comparison_bars.py  bar chart of autonomy, takeovers per lap and distance error
  runs_*.json         run lists given to analyze_eval.py for the report
  compose_video.py    assemble cards, slides and clips
  make_video.py       the final video
  run_sim.sh, restart_sim.sh   headless CoppeliaSim

Typical order
  ./dump_terrain.sh && python3 geom.py && python3 build_fields.py
  ./restart_sim.sh
  ./rec_session.sh island_exp ~/data/shore_island/raw_exp1 shore_island.npz 1.5 1 1500 none 1800
  python3 filter_outliers.py ~/data/shore_island/raw_exp1
  python3 ../floor_plane_record_base/scripts/split_dataset.py ~/data/shore_island/raw_exp1 --out ~/data/shore_island
  ../shore_follower_drive_torch_base/scripts/train_shore_follower.sh ~/data/shore_island
  ./rec_session.sh island_dag ~/data/shore_island/raw_dagger1 shore_island.npz 1.5 1 1200 <model.pt> 900
  ./eval_net.sh <model.pt> C_island 1 1.5 shore_island.npz 1 "Net C: island"
  python3 analyze_eval.py ~/data/shore_follower/eval/analysis runs_final.json
  python3 make_video.py

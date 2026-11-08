#!/bin/bash
T=$(cd "$(dirname "$0")" && pwd)
export ROS_DOMAIN_ID=42
source /cs-share/pradalier/venv/torch-cpu-ros2/bin/activate
source /opt/ros/kilted/setup.bash
source $HOME/ros_workspace/install/setup.bash
cd $T
M=$(ls ~/data/floor_plane/output_*/models/model_ce_99.pt)
ros2 launch floor_plane_classify_torch_base start.launch.py model:=$M > $T/classify_demo.log 2>&1 &
L=$!
until grep -q 'ready to run' $T/classify_demo.log; do sleep 1; done
/usr/bin/python3 record_demo.py floor $HOME/data/videos/floor_classifier_demo.mp4 900 'Floor classifier (CNN, model_ce_99)' 2 > $T/rec_floor_demo.log 2>&1 &
R=$!
sleep 2
python3 drive.py "$(cat demo_route3.json)" 0.5 > $T/drive_demo.log 2>&1
kill -INT $R; wait $R
kill -INT $L; sleep 3
pkill -INT -u $USER -x floor_plane_cla; sleep 2; pkill -9 -u $USER -x floor_plane_cla

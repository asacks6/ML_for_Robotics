#!/bin/bash
# usage: eval_net.sh model.pt tag laps dstar field side "title"
# Reinicia la simulacion, la red conduce y el supervisor solo interviene si se pierde.
T=$(cd "$(dirname "$0")" && pwd)
OUT=$HOME/data/shore_follower/eval
mkdir -p $OUT $HOME/data/videos
export ROS_DOMAIN_ID=42
source /cs-share/pradalier/venv/torch-cpu-ros2/bin/activate
source /opt/ros/kilted/setup.bash
source $HOME/ros_workspace/install/setup.bash
cd $T
for p in $(pgrep -u $USER -x coppeliaSim); do kill -TERM $p; done; sleep 3
for p in $(pgrep -u $USER -x coppeliaSim); do kill -9 $p; done
for p in $(ps -u $USER -o pid=,args= | awk '$2=="tail" && $3=="-f" && $4=="/dev/null" {print $1}'); do kill $p; done
mkdir -p /tmp/asacks-coppelia
$T/run_sim.sh /cs-share/pradalier/ros2_ws/src/scenes/lakeExampleRich.ttt > $OUT/sim_$2.log 2>&1 &
until timeout 3 ros2 topic echo --once /vrep/simTime > /dev/null 2>&1; do sleep 2; done
printf '/**:\n  ros__parameters:\n    "~/model": "%s"\n    "~/linear_vel": 0.3\n    "~/twist_factor": 0.4\n' "$1" > $OUT/drive_$2.yaml
ros2 run shore_follower_drive_torch_base shore_follower_drive_node --ros-args --params-file $OUT/drive_$2.yaml -r '~/image:=/vrep/kision/image' -r '~/twist:=/net/twist' > $OUT/net_$2.log 2>&1 &
until grep -q 'ready to run' $OUT/net_$2.log; do sleep 1; done
/usr/bin/python3 record_demo.py shore $HOME/data/videos/shore_$2.mp4 3000 "$7" 3 $4 > $OUT/rec_$2.log 2>&1 &
R=$!
python3 dagger.py --laps $3 --duration 2400 --dstar $4 --field $5 --side $6 --log $OUT/$2_log.npy > $OUT/sup_$2.log 2>&1
kill -INT $R; wait $R
pkill -INT -u $USER -x shore_follower_; sleep 2; pkill -9 -u $USER -x shore_follower_
tail -1 $OUT/sup_$2.log

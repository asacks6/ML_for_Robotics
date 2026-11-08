#!/bin/bash
# usage: rec_session.sh tag out_dir field dstar side max_per_class model.pt|none duration_sim [seed]
# Sin modelo: el experto conduce con golpes de direccion. Con modelo: DAgger.
T=$(cd "$(dirname "$0")" && pwd)
L=$T/logs; mkdir -p $L $2
export ROS_DOMAIN_ID=42
source /cs-share/pradalier/venv/torch-cpu-ros2/bin/activate
source /opt/ros/kilted/setup.bash
source $HOME/ros_workspace/install/setup.bash
cd $T
printf '/**:\n  ros__parameters:\n    "~/base_frame": bubbleRob\n    "~/world_frame": world\n    "~/out_dir": %s\n    "~/rotation_threshold": 0.2\n    "~/min_displacement": 0.1\n    "~/min_rotation": 0.1\n    "~/max_image_per_type": %s\n    "~/joystick_button": 3\n' "$2" "$6" > $L/observe_$1.yaml
ros2 run shore_follower_observe shore_follower_observe --ros-args --params-file $L/observe_$1.yaml -r '~/joy:=/joy' -r '~/image:=/vrep/kision/image' -r '~/twist:=/expert/twist' > $L/observe_$1.log 2>&1 &
if [ "$7" != "none" ]; then
  printf '/**:\n  ros__parameters:\n    "~/model": "%s"\n    "~/linear_vel": 0.3\n    "~/twist_factor": 0.4\n' "$7" > $L/drive_$1.yaml
  ros2 run shore_follower_drive_torch_base shore_follower_drive_node --ros-args --params-file $L/drive_$1.yaml -r '~/image:=/vrep/kision/image' -r '~/twist:=/net/twist' > $L/net_$1.log 2>&1 &
  until grep -q 'ready to run' $L/net_$1.log; do sleep 1; done
  MODE=""
else
  MODE="--expert_only --kicks"
fi
python3 dagger.py $MODE --duration $8 --labels $2/labels.txt --max $6 --dstar $4 --field $3 --side $5 --seed ${9:-0} > $L/sup_$1.log 2>&1
pkill -INT -u $USER -x shore_follower_; sleep 3; pkill -9 -u $USER -x shore_follower_
tail -1 $L/sup_$1.log
awk '{print $2}' $2/labels.txt | sort | uniq -c

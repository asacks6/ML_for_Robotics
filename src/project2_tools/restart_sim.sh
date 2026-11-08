#!/bin/bash
# Reinicia CoppeliaSim con la escena del lago y espera a que publique
export ROS_DOMAIN_ID=42
source /opt/ros/kilted/setup.bash
T=$(cd "$(dirname "$0")" && pwd)
for p in $(pgrep -u $USER -x coppeliaSim); do kill -TERM $p; done; sleep 3
for p in $(pgrep -u $USER -x coppeliaSim); do kill -9 $p; done
for p in $(ps -u $USER -o pid=,args= | awk '$2=="tail" && $3=="-f" && $4=="/dev/null" {print $1}'); do kill $p; done
mkdir -p /tmp/asacks-coppelia $T/logs
nohup $T/run_sim.sh /cs-share/pradalier/ros2_ws/src/scenes/lakeExampleRich.ttt > $T/logs/sim.log 2>&1 &
until timeout 3 ros2 topic echo --once /vrep/simTime > /dev/null 2>&1; do sleep 2; done
echo "sim up"

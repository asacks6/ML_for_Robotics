#!/bin/bash
export ROS_DOMAIN_ID=42
export TMPDIR=/tmp/asacks-coppelia
source /opt/ros/kilted/setup.bash
source /cs-share/pradalier/ros2_ws/zenoh.bash 2>/dev/null
C=/cs-share/pradalier/CoppeliaSim_Edu_V4_10_0_rev0_Ubuntu24_04
export LD_LIBRARY_PATH=$C:$LD_LIBRARY_PATH
cd $C
tail -f /dev/null | ./coppeliaSim -h -s7200000 "$1"

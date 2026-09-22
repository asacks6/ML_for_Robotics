#!/bin/bash

WS=/home/GTL/asacks/ros_workspace
BAG=$1
NAME=$2
RATE=${3:-2.0}

OUT=$WS/sysid/data
mkdir -p $OUT

ros2 topic echo /vrep/commandTwist geometry_msgs/msg/TwistStamped --csv > $OUT/${NAME}_cmd.csv &
CMD_PID=$!
ros2 topic echo /vrep/localTwist geometry_msgs/msg/TwistStamped --csv > $OUT/${NAME}_vel.csv &
VEL_PID=$!

sleep 3
ros2 bag play $BAG --rate $RATE
sleep 3

kill -INT $CMD_PID $VEL_PID 2>/dev/null
sleep 2
kill -9 $CMD_PID $VEL_PID 2>/dev/null
sleep 1

echo "$NAME: $(wc -l < $OUT/${NAME}_cmd.csv) command rows, $(wc -l < $OUT/${NAME}_vel.csv) velocity rows"

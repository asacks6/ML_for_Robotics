#!/bin/bash
# Demo de un seguidor de orilla sobre la simulacion que ya esta corriendo, en el
# ROS_DOMAIN_ID actual, con el mismo protocolo que el video: el experto (dagger.py) lleva
# el robot hasta la orilla, luego conduce la red y el experto solo toma el control si el
# robot se sale de la banda. Abre una ventana con la camara, el mando y la vista cenital.
# usage: watch_shore.sh A|B|C0|C [outer|island] [laps]
#   A  orilla exterior, solo datos del experto      B  orilla exterior, experto + DAgger
#   C0 isla, solo datos del experto                 C  isla, experto + DAgger
#   sin pista se usa la de entrenamiento de la red; laps = vueltas (1 por defecto)
# VIEW=fichero.mp4 graba en un fichero en lugar de abrir la ventana.
T=$(cd "$(dirname "$0")" && pwd)
NET=${1:-B}
case $NET in
  A)  MODEL=$(ls $HOME/data/shore_follower/old_v2/output_*/models/model_ce_70.pt); TRACK=outer ;;
  B)  MODEL=$(ls $HOME/data/shore_follower/output_20261013_184009/models/model_ce_71.pt); TRACK=outer ;;
  C0) MODEL=$(ls $HOME/data/shore_island/old_c0/output_*/models/model_ce_67.pt); TRACK=island ;;
  C)  MODEL=$(ls $HOME/data/shore_island/output_*/models/model_ce_69.pt); TRACK=island ;;
  *)  echo "usage: watch_shore.sh A|B|C0|C [outer|island] [laps]"; exit 1 ;;
esac
TRACK=${2:-$TRACK}
LAPS=${3:-1}
FIELD=shore.npz
[ "$TRACK" = island ] && FIELD=shore_island.npz
VIEW=${VIEW:-view}
source /cs-share/pradalier/venv/torch-cpu-ros2/bin/activate
source /opt/ros/kilted/setup.bash
source $HOME/ros_workspace/install/setup.bash
cd $T
mkdir -p logs
if [ ! -f $FIELD ]; then
  echo "building the distance fields (once)"
  /usr/bin/python3 geom.py > /dev/null && /usr/bin/python3 build_fields.py > /dev/null
fi
echo "ROS_DOMAIN_ID=$ROS_DOMAIN_ID  network $NET on the $TRACK shore, $LAPS lap(s)  model $MODEL"
if ! timeout -s INT 10 ros2 topic echo --once /vrep/simTime > /dev/null 2>&1; then
  echo "No simulation on ROS_DOMAIN_ID=$ROS_DOMAIN_ID: open lakeExampleRich.ttt in CoppeliaSim and press play"
  exit 1
fi

cleanup() {
  kill -INT $S $V 2>/dev/null
  pkill -INT -u $USER -x shore_follower_; sleep 2; pkill -9 -u $USER -x shore_follower_
  ros2 topic pub --once /vrep/twistCommand geometry_msgs/msg/Twist "{}" > /dev/null
}
trap cleanup EXIT

printf '/**:\n  ros__parameters:\n    "~/model": "%s"\n    "~/linear_vel": 0.3\n    "~/twist_factor": 0.4\n' "$MODEL" > logs/watch_drive.yaml
ros2 run shore_follower_drive_torch_base shore_follower_drive_node --ros-args --params-file logs/watch_drive.yaml \
    -r '~/image:=/vrep/kision/image' -r '~/twist:=/net/twist' > logs/watch_shore_net.log 2>&1 &
until grep -q 'ready to run' logs/watch_shore_net.log; do sleep 1; done
/usr/bin/python3 record_demo.py shore $VIEW 1e9 "Net $NET on the $TRACK shore" 1 1.5 > logs/watch_shore_view.log 2>&1 &
V=$!
sleep 4
if ! kill -0 $V 2>/dev/null; then echo "the viewer failed:"; tail -5 logs/watch_shore_view.log; exit 1; fi
echo "the expert first drives to the shore, then the network takes over (progress every 30 s of sim time)"
python3 dagger.py --laps $LAPS --duration 3000 --dstar 1.5 --field $FIELD --side 1 &
S=$!
wait $S

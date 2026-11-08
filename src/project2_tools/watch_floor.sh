#!/bin/bash
# Demo del clasificador de suelo sobre la simulacion que ya esta corriendo (con o sin GUI),
# en el ROS_DOMAIN_ID actual. Abre una ventana con camara, salida de la red y vista cenital.
# usage: watch_floor.sh [route|manual] [model.pt]
#   route   (por defecto) el robot recorre floor_route.json desde la pose inicial de la escena
#   manual  el robot no se mueve solo: conducir con el joystick o el teclado
# VIEW=fichero.mp4 graba en un fichero en lugar de abrir la ventana.
T=$(cd "$(dirname "$0")" && pwd)
MODE=${1:-route}
MODEL=${2:-$(ls $HOME/data/floor_plane/output_*/models/model_ce_99.pt | head -1)}
VIEW=${VIEW:-view}
source /cs-share/pradalier/venv/torch-cpu-ros2/bin/activate
source /opt/ros/kilted/setup.bash
source $HOME/ros_workspace/install/setup.bash
cd $T
mkdir -p logs
if [ ! -f shore.npz ]; then
  echo "building the scene maps (once)"
  /usr/bin/python3 geom.py > /dev/null && /usr/bin/python3 build_fields.py > /dev/null
fi
echo "ROS_DOMAIN_ID=$ROS_DOMAIN_ID  model $MODEL"
if ! timeout -s INT 10 ros2 topic echo --once /vrep/simTime > /dev/null 2>&1; then
  echo "No simulation on ROS_DOMAIN_ID=$ROS_DOMAIN_ID: open lakeExampleRich.ttt in CoppeliaSim and press play"
  exit 1
fi

cleanup() {
  kill -INT $V 2>/dev/null
  pkill -INT -u $USER -x floor_plane_cla; sleep 2; pkill -9 -u $USER -x floor_plane_cla
  ros2 topic pub --once /vrep/twistCommand geometry_msgs/msg/Twist "{}" > /dev/null
}
trap cleanup EXIT

ros2 launch floor_plane_classify_torch_base start.launch.py model:=$MODEL > logs/watch_floor_classifier.log 2>&1 &
until grep -q 'ready to run' logs/watch_floor_classifier.log; do sleep 1; done
echo "classifier running, output on /floor_plane_classify/image_label"
/usr/bin/python3 record_demo.py floor $VIEW 1e9 'Floor classifier (model_ce_99)' > logs/watch_floor_view.log 2>&1 &
V=$!
sleep 4
if ! kill -0 $V 2>/dev/null; then echo "the viewer failed:"; tail -5 logs/watch_floor_view.log; exit 1; fi
if [ "$MODE" = route ]; then
  echo "driving the obstacle route (about 2 minutes)"
  python3 drive.py "$(cat floor_route.json)" 0.5
  echo "route done, Ctrl+C (or Esc in the window) to quit"
else
  echo "drive with the joystick or the keyboard, Ctrl+C (or Esc in the window) to quit"
fi
wait $V

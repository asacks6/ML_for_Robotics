After cloning and building the workspace:

cd src/final_project/arm_training
cat model_ce_74.pt.part* > model_ce_74.pt
sha256sum -c model_ce_74.pt.sha256
ros2 launch vsv_treasure auto.launch.py model:=$PWD/model_ce_74.pt
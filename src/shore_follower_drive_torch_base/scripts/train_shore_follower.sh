#!/bin/bash
# A lanzar con el venv y el workspace ya cargados:
#   source /opt/venv/torch-gpu-ros2/bin/activate
#   source ~/ros_workspace/install/setup.bash

ROOT=${1:-$HOME/data/shore_follower}

ros2 run pytorch_models_base train \
    --val_file $ROOT/val/labels.txt \
    --train_file $ROOT/train/labels.txt \
    --train_root $ROOT/train \
    --val_root $ROOT/val \
    --learning_rate 0.00005 \
    --weight_decay 0.001 \
    --batch_size 64 \
    --iter 12 \
    --dropout 0.3 \
    --classes 3 \
    --loss_func ce \
    --output $ROOT/output_$(date +%Y%m%d_%H%M%S)

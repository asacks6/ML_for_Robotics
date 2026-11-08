#!/bin/bash
# A lanzar con el venv y el workspace ya cargados:
#   source /opt/venv/torch-gpu-ros2/bin/activate
#   source ~/ros_workspace/install/setup.bash
# Se lanza desde la carpeta donde se quiera la carpeta runs/ de tensorboard.

ROOT=$HOME/data/floor_plane

ros2 run pytorch_models_base train \
    --val_file $ROOT/val/labels.txt \
    --train_file $ROOT/train/labels.txt \
    --train_root $ROOT/train \
    --val_root $ROOT/val \
    --learning_rate 0.0001 \
    --weight_decay 0.0001 \
    --batch_size 64 \
    --iter 20 \
    --dropout 0.2 \
    --classes 2 \
    --loss_func ce \
    --output $ROOT/output_$(date +%Y%m%d_%H%M%S)

#!/bin/bash
# usage: train_arm.sh [carpeta con las sesiones raw_*] [opciones extra de train.py]
# Separa las sesiones grabadas en train/ y val/, entrena la red del brazo y deja
# el mejor modelo en <carpeta>/model.pt

BASE_DIR=$(realpath "${1:-$HOME/ros_workspace/src/final_project/data/arm}")
shift
SCRIPTS=$(dirname "$(realpath "$0")")

source /cs-share/pradalier/venv/torch-cpu-ros2/bin/activate

# Se rehace la separacion cada vez, por si hay sesiones nuevas
rm -rf ${BASE_DIR}/train ${BASE_DIR}/val
python3 ${SCRIPTS}/split_dataset.py ${BASE_DIR}/raw_* --out ${BASE_DIR} || exit 1

# runs/ (tensorboard), loss.png y acc.png se escriben en la carpeta actual
cd ${BASE_DIR}
OUT=${BASE_DIR}/output_$(date +%Y%m%d_%H%M%S)

# Agg: las curvas se guardan en png sin abrir ventanas que bloqueen el final
MPLBACKEND=Agg PYTHONUNBUFFERED=1 ros2 run pytorch_models_base train \
    --train_file ${BASE_DIR}/train/labels.txt \
    --train_root ${BASE_DIR}/train \
    --val_root ${BASE_DIR}/val \
    --val_file ${BASE_DIR}/val/labels.txt \
    --learning_rate 0.0001 \
    --weight_decay 0.0001 \
    --batch_size 64 \
    --iter 15 \
    --dropout 0.2 \
    --classes 3 \
    --loss_func ce \
    --output ${OUT} \
    $*

# cada modelo pesa unos 300 MB: solo guardamos el ultimo, que es el de mejor val acc
ls -t ${OUT}/models/*.pt | tail -n +2 | xargs -r rm -f
BEST=$(ls ${OUT}/models/*.pt)
ln -sfn ${BEST} ${BASE_DIR}/model.pt
echo "best model: ${BEST}"
echo "linked as:  ${BASE_DIR}/model.pt"
echo "curves:     ${BASE_DIR}/loss.png ${BASE_DIR}/acc.png"

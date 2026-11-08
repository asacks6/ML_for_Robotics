#!/bin/bash
# Todas las evaluaciones de la comparativa, una vuelta supervisada cada una, sim reiniciada
T=$(cd "$(dirname "$0")" && pwd)
A=$(ls $HOME/data/shore_follower/old_v2/output_20261013_180724/models/model_ce_70.pt)
B=$(ls $HOME/data/shore_follower/output_20261013_184009/models/model_ce_71.pt)
C0=$1
C=$2
$T/eval_net.sh $C0 C0_island 1 1.5 shore_island.npz 1 "Net C0: island 1.5 m, expert data only"
$T/eval_net.sh $C  C_island  1 1.5 shore_island.npz 1 "Net C: island 1.5 m, expert + DAgger"
$T/eval_net.sh $B  B_island  1 1.5 shore_island.npz 1 "Cross test: net B (outer) on the island"
$T/eval_net.sh $C  C_outer   1 1.5 shore.npz 1 "Cross test: net C (island) on the outer rim"

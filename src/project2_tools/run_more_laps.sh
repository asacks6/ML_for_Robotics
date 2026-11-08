#!/bin/bash
# Dos vueltas mas por configuracion para tener 3 vueltas en total
T=$(cd "$(dirname "$0")" && pwd)
A=$HOME/data/shore_follower/old_v2/output_20261013_180724/models/model_ce_70.pt
B=$HOME/data/shore_follower/output_20261013_184009/models/model_ce_71.pt
C0=$(ls $HOME/data/shore_island/old_c0/output_*/models/model_ce_67.pt)
C=$(ls $HOME/data/shore_island/output_*/models/model_ce_69.pt)
$T/eval_net.sh $C0 C0_island_r2 2 1.5 shore_island.npz 1 "Net C0: island, laps 2-3"
$T/eval_net.sh $C  C_island_r2  2 1.5 shore_island.npz 1 "Net C: island, laps 2-3"
$T/eval_net.sh $B  B_island_r2  2 1.5 shore_island.npz 1 "Net B on the island, laps 2-3"
$T/eval_net.sh $A  A_expert_r2  2 1.5 shore.npz 1 "Net A: outer, laps 2-3"
$T/eval_net.sh $B  B_dagger_r2  2 1.5 shore.npz 1 "Net B: outer, laps 2-3"
$T/eval_net.sh $C  C_outer_r2   2 1.5 shore.npz 1 "Net C on the outer rim, laps 2-3"

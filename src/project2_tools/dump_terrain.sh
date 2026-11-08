#!/bin/bash
# Extrae los vertices del heightfield del lago a terrain.txt (x y z en el mundo)
# usage: dump_terrain.sh [scene.ttt]
HERE=$(cd $(dirname $0); pwd)
SCENE=${1:-/cs-share/pradalier/ros2_ws/src/scenes/lakeExampleRich.ttt}
cat > $HERE/dump_terrain.lua <<LUA
local h=sim.getObject('/10mX10m_terrain')
local v,i=sim.getShapeMesh(h)
local m=sim.getObjectMatrix(h,-1)
local f=io.open('$HERE/terrain.txt','w')
for k=1,#v,3 do
  local p=sim.multiplyVector(m,{v[k],v[k+1],v[k+2]})
  f:write(string.format('%.3f %.3f %.3f\n',p[1],p[2],p[3]))
end
f:close()
LUA
export TMPDIR=/tmp/$USER-coppelia ROS_DOMAIN_ID=43
mkdir -p $TMPDIR
C=/cs-share/pradalier/CoppeliaSim_Edu_V4_10_0_rev0_Ubuntu24_04
export LD_LIBRARY_PATH=$C:$LD_LIBRARY_PATH
cd $C && timeout 90 ./coppeliaSim -h "-csim.loadScene('$SCENE');dofile('$HERE/dump_terrain.lua');sim.quitSimulator()" < /dev/null > /dev/null 2>&1
wc -l $HERE/terrain.txt

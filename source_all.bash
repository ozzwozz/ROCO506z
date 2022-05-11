#! /bin/bash 

PIONEER3DX_DRIVERS_WS=~/pioneer3dx_wss/pioneer3dx
PIONEER3DX_SIMULATION_WS=~/pioneer3dx_wss/pioneer3dx_simulation
PIONEER3DX_2DSLAM_WS=~/pioneer3dx_wss/pioneer3dx_2dslam
PIONEER3DX_map_and_nav_WS=~/pioneer3dx_wss/pioneer3dx_map_and_nav

source ~/.bashrc
source /opt/ros/noetic/setup.bash
source $PIONEER3DX_DRIVERS_WS/devel/setup.bash --extend
source $PIONEER3DX_SIMULATION_WS/devel/setup.bash --extend
source $PIONEER3DX_2DSLAM_WS/devel/setup.bash --extend
source $PIONEER3DX_map_and_nav_WS/devel/setup.bash --extend

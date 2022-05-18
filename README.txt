install gmapping using
sudo apt-get ros-noetic-gmapping-*

install octomap
sudo apt-get install ros-noetic-octomap-*

install the pointcloud2 message creator inside of the sensorfusion workspace
git clone https://github.com/marco-teixeira/float32multiarray_to_pointcloud2.git
and in the launch file change parameters to 
        <arg name="input_topic" default="/depth_buff" />
        <arg name="output_topic" default="/cloud_out" />
        <arg name="frame_id" default="camera_link" />
        <arg name="open_rviz" default= "false" />

install move_base by running both of the following
sudo apt install ros-noetic-move-base
sudo apt install ros-noetic-move-base-*

install the local planner using
sudo apt-get install ros-noetic-dwa-local-planner

install keyboard teleop using
sudo apt-get install ros-noetic-teleop-twist-keyboard


source pioneer3dx_sensorfusion/devel/setup.bash --extend
source pioneer3dx_simulation/devel/setup.bash --extend
source pioneer3dx_map_and_nav/devel/setup.bash --extend
source pioneer3dx_2dslam/devel/setup.bash --extend
source pioneer3dx/devel/setup.bash --extend
source pioneer3dx_movement/devel/setup.bash --extend

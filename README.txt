%install gmapping using
sudo apt-get ros-noetic-gmapping-*

%install octomap
sudo apt-get install ros-noetic-octomap-*

%install the pointcloud2 message creator inside of the sensorfusion workspace
git clone https://github.com/marco-teixeira/float32multiarray_to_pointcloud2.git
%and in the launch file change parameters to 
        <arg name="input_topic" default="/depth_buff" />
        <arg name="output_topic" default="/cloud_out" />
        <arg name="frame_id" default="camera_link" />
        <arg name="open_rviz" default= "false" />

%install move_base by running both of the following
sudo apt install ros-noetic-move-base
sudo apt install ros-noetic-move-base-*

%install the local planner using
sudo apt-get install ros-noetic-dwa-local-planner

%install keyboard teleop using
sudo apt-get install ros-noetic-teleop-twist-keyboard

%the source_all file should include these sources but if it doesn't work here they are
source pioneer3dx_sensorfusion/devel/setup.bash --extend
source pioneer3dx_simulation/devel/setup.bash --extend
source pioneer3dx_map_and_nav/devel/setup.bash --extend
source pioneer3dx_2dslam/devel/setup.bash --extend
source pioneer3dx/devel/setup.bash --extend
source pioneer3dx_movement/devel/setup.bash --extend

%The source all file also contains
source ~/.bashrc
source /opt/ros/noetic/setup.bash
%which allow the terminal to find all of the relevent ROS commands


%To run everything 1st you will need to catkin make in all of the folders

source source_all.bash
cd pioneer3dx 
catkin_make
cd ..
cd pioneer3dx_2dslam
catkin_make
cd ..
cd pioneer3dx_map_and_nav
catkin_make
cd ..
cd pioneer3dx_movement
catkin_make
cd ..
cd pioneer3dx_sensorfusion
catkin_make
cd ..
cd pioneer3dx_simulation
catkin_make
cd ..

% The order in which everything is run matters so 1st we need to run Roscore, then Gmapping, then the simulation, then octomap, and then the Path planning.
%Run RosCore by inputting
source source_all.bash
roscore

%in a new terminal
%Run Gmapping with
source source_all.bash
roslaunch pioneer3dx_2dslam/src/pioneer3dx_gmapping/launch/pioneer3dx_gmapping.launch 

%in a new terminal
%Then run the simulation with
source source_all.bash
roslaunch coppeliasim_p3dx_sim coppeliasim_p3dx_all.launch

%in a new terminal
%Run Octomap with
source source_all.bash
roslaunch pioneer3dx_map_and_nav/src/pioneer3dx_octomap/launch/pioneer3dx_octomap.launch

%in a new terminal
%Run path planning
source source_all.bash
roslaunch pioneer3dx_movement/src/pioneer3dx_move_base/launch/pioneer3dx_move_base_launch.launch


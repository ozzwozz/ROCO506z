install gmapping using
sudo apt-get ros-noetic-gmapping-*
install octomap
sudo apt-get install ros-noetic-octomap
install the pointcloud2 message creator
git clone https://github.com/marco-teixeira/float32multiarray_to_pointcloud2
install move_base by running both of the following
sudo apt install ros-noetic-move-base
sudo apt install ros-noetic-move-base-*

source pioneer3dx_sensorfusion/devel/setup.bash --extend
source pioneer3dx_simulation/devel/setup.bash --extend
source pioneer3dx_map_and_nav/devel/setup.bash --extend
source pioneer3dx_2dslam/devel/setup.bash --extend
source pioneer3dx/devel/setup.bash --extend


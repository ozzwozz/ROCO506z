cmake_minimum_required(VERSION 3.0.2)
project(segmentation_and_clustering)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  pcl_ros
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

find_package(PCL REQUIRED)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

add_executable(planar_segmentation_node src/planar_segmentation.cpp)


target_link_libraries(planar_segmentation_node ${catkin_LIBRARIES} ${PCL_LIBRARIES})


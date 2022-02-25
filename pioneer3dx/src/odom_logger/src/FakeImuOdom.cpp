#ifndef FakeImuOdom_H
#define FakeImuOdom_H
#include <string>
#include <stdio.h>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>

template<typename T>
T getParam(ros::NodeHandle& n, const std::string& name, const T& defaultValue)
{
	T v;
	if (n.getParam(name, v))
	{
		ROS_INFO_STREAM("Found parameter: " << name << ", value: " << v);
		return v;
	}
	else
        {
		ROS_WARN_STREAM("Cannot find value for parameter: " << name << ", assigning default: " << defaultValue);
        }
	return defaultValue;
}

class FakeImuOdom{
    
private:

    ros::NodeHandle n_;
    
    double linear_ref_vel;

protected:
    
    ros::NodeHandle node;
    
    std::string fake_imu_odom_topic_name;
    
    double rate;

public:

	nav_msgs::Odometry fake_msg;

    ros::Publisher fake_imu_odom_pub;
    
    void ros_spin();
    
    FakeImuOdom();
    ~FakeImuOdom();
    
};

void FakeImuOdom::ros_spin()
{
    ros::Rate r(rate); // 15 hz default
    while (ros::ok()){
        
        // ROS_INFO("ros spin");
        fake_msg.header.stamp = ros::Time::now();
        fake_msg.header.frame_id = "/imu";
        fake_msg.child_frame_id = "/imu";
        
        fake_msg.pose.pose.position.x = linear_ref_vel * (1/rate);
        fake_msg.pose.pose.position.y = 0;
        fake_msg.pose.pose.position.z = 0;
        fake_msg.pose.pose.orientation.x = 0;
        fake_msg.pose.pose.orientation.y = 0;
        fake_msg.pose.pose.orientation.z = 0;
        fake_msg.pose.pose.orientation.w = 1;
        // fake_msg.pose.covariance
        
        fake_msg.twist.twist.linear.x = 0;
        fake_msg.twist.twist.linear.y = 0;
        fake_msg.twist.twist.linear.z = 0;
        fake_msg.twist.twist.angular.x = 0;
        fake_msg.twist.twist.angular.y = 0;
        fake_msg.twist.twist.angular.z = 0;
        // fake_msg.twist.covariance
        
        fake_imu_odom_pub.publish(fake_msg);
    
        ros::spinOnce();
        r.sleep();
    }
}

FakeImuOdom::FakeImuOdom():
        n_("~"),
        linear_ref_vel(0.5) // meters per second
{
	fake_imu_odom_topic_name = getParam<std::string>(n_, "fake_imu_odom_topic_name", "/fake_imu_odom");
	rate = getParam<double>(n_, "loop_rate", 20);
	fake_imu_odom_pub = node.advertise<nav_msgs::Odometry>(fake_imu_odom_topic_name, 1000);
}

FakeImuOdom::~FakeImuOdom(){}

int main(int argc, char* argv[]){
    
    ros::init (argc, argv, "fake_imu_odom");
    FakeImuOdom fake_imu_odom;
    fake_imu_odom.ros_spin();
    return 0;
}

#endif /* FakeImuOdom_H */


#ifndef FakeImuOdomAndTwist_H
#define FakeImuOdomAndTwist_H
#include <string>
#include <stdio.h>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>

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

class FakeImuOdomAndTwist{
    
private:

    ros::NodeHandle n_;
    
    double linear_ref_vel;

protected:
    
    ros::NodeHandle node;
    
    std::string fake_imu_odom_topic_name;
    std::string fake_twist_topic_name;
    
    double rate;

public:

	nav_msgs::Odometry fake_msg;
	geometry_msgs::TwistStamped fake_twist;

    ros::Publisher fake_imu_odom_pub;
    ros::Publisher fake_twist_pub;
    
    void ros_spin();
    
    FakeImuOdomAndTwist();
    ~FakeImuOdomAndTwist();
    
};

void FakeImuOdomAndTwist::ros_spin()
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
        
        fake_twist.header.stamp = fake_msg.header.stamp;
        fake_twist.header.frame_id = "/imu";
        
        fake_twist.twist.linear.x = linear_ref_vel;
        fake_twist.twist.linear.y = 0;
        fake_twist.twist.linear.z = 0;
        fake_twist.twist.angular.x = 0;
        fake_twist.twist.angular.y = 0;
        fake_twist.twist.angular.z = 0;
        
        fake_imu_odom_pub.publish(fake_msg);
        fake_twist_pub.publish(fake_twist);
    
        ros::spinOnce();
        r.sleep();
    }
}

FakeImuOdomAndTwist::FakeImuOdomAndTwist():
        n_("~"),
        linear_ref_vel(0.5) // meters per second
{
	fake_imu_odom_topic_name = getParam<std::string>(n_, "fake_imu_odom_topic_name", "/fake_imu_odom");
	fake_twist_topic_name = getParam<std::string>(n_, "fake_twist_topic_name", "/fake_cmd_vel");
	rate = getParam<double>(n_, "loop_rate", 20);
	fake_imu_odom_pub = node.advertise<nav_msgs::Odometry>(fake_imu_odom_topic_name, 1000);
	fake_twist_pub = node.advertise<geometry_msgs::TwistStamped>(fake_twist_topic_name, 1000);
}

FakeImuOdomAndTwist::~FakeImuOdomAndTwist(){}

int main(int argc, char* argv[]){
    
    ros::init (argc, argv, "fake_imu_odom_and_twist");
    FakeImuOdomAndTwist fake_imu_odom_and_twist;
    fake_imu_odom_and_twist.ros_spin();
    return 0;
}

#endif /* FakeImuOdomAndTwist_H */


//============================================================================
// Name        : TestTopicPublisher.cpp
// Author      : Yonghan Lee
// Version     : 1.0
// Date		   : 2016. 8. 3
// Copyright   : Inrol
// Description : Test Topic Publisher for Delayer Node
//============================================================================

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"
#include <iostream>
#include <iomanip>
int main(int argc, char **argv)
{
	ros::init(argc, argv, "TestTopicPublisher");
	ros::NodeHandle n;

	//ros::Publisher Int32_pub =n.advertise<std_msgs::Int32>("TestTopicPublisher/Integer", 10);
	ros::Publisher Float32_pub = n.advertise<std_msgs::Float32>("TestTopicPublisher/Float", 10);

	ros::Rate loop_rate(10);
	ros::Time time_class_init = ros::Time::now();
	double time_init = time_class_init.sec + time_class_init.nsec/1000000000.0;
	while (ros::ok())
	{
        ros::Time time_class_now = ros::Time::now();
		double time_now = time_class_now.sec + time_class_now.nsec/1000000000.0;
		double time_elapsed = time_now - time_init;
		//std::cout << std::fixed <<  std::setw(15) << std::setprecision(9) << time_elapsed  << std::endl;

		//std_msgs::Int32 Int32_msg;
		//Int32_msg.data = (int)time_elapsed;
		//Int32_pub.publish(Int32_msg);

		std_msgs::Float32 Float32_msg;
		Float32_msg.data = (float)time_elapsed;
		Float32_pub.publish(Float32_msg);

		loop_rate.sleep();
	}
	return 0;
}

//============================================================================
// Name        : Delayer.cpp
// Author      : Yonghan Lee
// Version     : 1.0
// Date		   : 2016. 8. 3
// Copyright   : Inrol
// Description : Delayer Node Main
//============================================================================

#include "ros/ros.h"
#include <iostream>
#include "DelayElement.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "Delayer");
	ros::NodeHandle n;

	/* ---------------------------------------------------------------------------- */
	// Template Class Constructor Definition :
	//     Template <typename T>
	//     DelayElement<T>::DelayElement(ros::NodeHandle& n, double delay, double loop_rate, std::string topic_name)
	// Usage :
	//     1. Define a DelayElement									
	//			DelayElement<std_msgs::Float32> mDelayElement(n, 2, 10, "/TestTopicPublisher/Float");
	//     2. Call DelayElement<T>::publish() method inside a loop
	//			mDelayElement.publish();
	/* ---------------------------------------------------------------------------- */

	DelayElement<std_msgs::Float32> mDelayElement(n, 2, 10, "/TestTopicPublisher/Float");



	ros::Rate loop_rate(10);
	while (ros::ok())
	{
		ros::spinOnce();

		mDelayElement.publish();

		loop_rate.sleep();
	}
	return 0;
}

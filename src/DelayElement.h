//============================================================================
// Name        : DelayElement.h
// Author      : Yonghan Lee
// Version     : 1.0
// Date		   : 2016. 8. 3
// Copyright   : Inrol
// Description : DelayElement Declaration and Definition
//============================================================================

#pragma once

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"
#include <queue>
#include <string>
#include <iostream>
#include <iomanip>


template <typename T>
class QueueElement {
public:
	QueueElement(T msg, double time);
	T msg;
	double time;
};

template <typename T>
class DelayElement
{
public:
	DelayElement(ros::NodeHandle& _n, double _delay, double _rate, std::string _name_subscribing_topic);
	void publish();
	
private:
	ros::NodeHandle n;

	ros::Publisher publisher;
	ros::Subscriber subscriber; 

	void callback(const T& msg);
	
	std::queue<QueueElement<T> > mQueue;
	double delay;
	double rate;

};

template <typename T>
QueueElement<T>::QueueElement(T msg, double time) : msg(msg), time(time) {}


template <typename T>
DelayElement<T>::DelayElement(ros::NodeHandle& _n, double _delay, double _rate, std::string _name_subscribing_topic) : n(_n), delay(_delay), rate(_rate)
{
	std::string name_publishing_topic;
	if(_name_subscribing_topic[0] != '/')
		name_publishing_topic = "/Delayer/" + _name_subscribing_topic;
	else
		name_publishing_topic = "/Delayer" + _name_subscribing_topic;
	publisher = n.advertise<T>(name_publishing_topic, rate);
	subscriber = n.subscribe(_name_subscribing_topic, rate, &DelayElement::callback, this);
}

template<typename T>
void DelayElement<T>::publish()
{
    ros::Time time_class = ros::Time::now();
	double time = time_class.sec + time_class.nsec/1000000000.0;
	while(!mQueue.empty() && time - mQueue.front().time > delay)
	{
		publisher.publish(mQueue.front().msg);
		mQueue.pop();
	}
}

template<typename T>
void DelayElement<T>::callback(const T& msg)
{
    ros::Time time_class = ros::Time::now();
	double time = time_class.sec + time_class.nsec/1000000000.0;
	mQueue.push(QueueElement<T>(msg, time));
}


/*
 *  The Spiri Project
 *
 *  File: takeoff_and_land.cpp
 *
 *  Purpose: Action client for autonomous flights
 *           simpely test for takeoff and land.
 *
 *  @author Penguin Cheng
 *  @version 0.1.0 24/12/15
 */

#include "ros/ros.h"
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <spiri_go/TakeoffAction.h>
#include <spiri_go/LandHereAction.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "spiri_go_client");
	
	actionlib::SimpleActionClient<spiri_go::TakeoffAction> ac("spiri_take_off", true);      //first param: server name, second param: true means a new thread
	actionlib::SimpleActionClient<spiri_go::LandHereAction> ac1("spiri_land_here", true);  //first param: server name, second param: false means not to use threads

	ROS_INFO("Waiting for action server(takeOff) to start.");

	ac.waitForServer();	
	
	ROS_INFO("Action server started--Taking off!");

	spiri_go::TakeoffGoal goal;

	//set the target height to take off!
	goal.height = 10;
	ac.sendGoal(goal);

	//wait for action(takeOff) to return
	bool is_takeOff_finished = ac.waitForResult(ros::Duration(60.0));

	if(is_takeOff_finished ) {
		ROS_INFO("reached target height!");

		//do something
		ros::Duration(10).sleep();
	}
	else {
		ROS_INFO("should set mode Land!");
	}

	//land
	ROS_INFO("Waiting for action server(land) to start.");
	ac1.waitForServer();	
	ROS_INFO("Start to land!.");
	
	spiri_go::LandHereGoal goal_1;
	goal_1.height = 0;
	ac1.sendGoal(goal_1);

	//wait for action(land) to return
	bool is_land_finished = ac1.waitForResult(ros::Duration(60.0));
	if(is_land_finished ) {
		ROS_INFO("Land success!");
	}

	return 0;

}

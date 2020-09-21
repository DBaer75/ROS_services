#include "geometry_msgs/Twist.h" //publishing topic
#include "ros/ros.h"
#include "std_srvs/Empty.h"
// Import the service message header file generated from the Empty.srv message

float robot_forward;    // variable to be written to linear velocity
float robot_left_right; // varible to be written to angular velocity

// We define the callback function of the service
bool my_callback(std_srvs::Empty::Request &req,
                 std_srvs::Empty::Response &res) {
  // res.some_variable = req.some_variable + req.other_variable;
  ROS_INFO(
      "My_callback has been called, bb8 turning in a circle"); // We print an
                                                               // string
                                                               // whenever the
                                                               // Service gets
                                                               // called

  robot_forward = 0.4;
  robot_left_right = 0.3;

  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "move_bb8_in_circle_node");
  ros::NodeHandle nh;

  ros::ServiceServer move_bb8_in_circle = nh.advertiseService(
      "/move_bb8_in_circle",
      my_callback); // create the Service called // my_service
                    // with the defined // callback

  // create object of type Twist
  geometry_msgs::Twist robot;

  // loop rate at 10Hz
  ros::Rate loop_rate(10);

  // publisher to the cmd_vel to move robot
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  while (ros::ok()) {
    robot.linear.x = robot_forward;
    robot.angular.z = robot_left_right;

    pub.publish(robot);

    ros::spinOnce();
    loop_rate.sleep();
  }

  ros::spin(); // mantain the service open.

  return 0;
}
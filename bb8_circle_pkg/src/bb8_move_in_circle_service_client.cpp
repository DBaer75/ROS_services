#include "ros/ros.h"

int main(int argc, char **argv) {
  ros::init(
      argc, argv,
      "move_bb8_in_circle_node_client"); // Initialise a ROS node 
  ros::NodeHandle nh;

  // Create the connection to the service /trajectory_by_name
  ros::ServiceClient move_bb8_in_circle_node =
      nh.serviceClient<move_bb8_in_circle_node::ExecTraj>(
          "/move_bb8_in_circle");

  execute_trajectory::ExecTraj srv; // Create an object of type TrajByName
  srv.request.traj_name =
      "release_food"; // Fill the variable traj_name with the desired value

  if (traj_by_name_service.call(srv)) // Send through the connection the name of
                                      // the trajectory to execute
  {
    ROS_INFO("%s",
             srv.response.status_message
                 .c_str()); // Print the result given by the service called
  } else {
    ROS_ERROR("Failed to call service /trajectory_by_name");
    return 1;
  }

  return 0;
}
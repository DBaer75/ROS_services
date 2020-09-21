#include "ros/ros.h"
#include "execute_trajectory/ExecTraj.h"
// Import the service message used by the service /trajectory_by_name

int main(int argc, char **argv) {
  ros::init(
      argc, argv,
      "service_client"); // Initialise a ROS node with the name service_client
  ros::NodeHandle nh;

  // Create the connection to the service /trajectory_by_name
  ros::ServiceClient traj_by_name_service =
      nh.serviceClient<execute_trajectory::ExecTraj>(
          "/trajectory_by_name");
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
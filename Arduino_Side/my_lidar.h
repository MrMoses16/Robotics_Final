#include "RPLidar.h"
// The local map represents a one meter (100 centimeter) square map
// that stores the evironment and the robots location within the 
// local map: 0 = OPEN, 1 = WALL
#define SIZE 100 
int local_map[SIZE][SIZE];

#define MIN_DEGREES 200

// // The robot's dimensions 
#define ROBOT_WIDTH 10
#define ROBOT_LENGTH 10

void send_data(String data);

// updates the local map with objects recorded from lidar
// angle is in degrees and distance is in mm
void update_local_map(float angle, float distance){
  // convert distance in meters to distance in centimeters
  int new_distance = int(distance / 10);

  int object_X = new_distance * cos(angle + robot_orientation) + robot_X;
  int object_Y = new_distance * sin(angle + robot_orientation) + robot_Y;

  local_map[object_X][object_Y] = 1;
}

// updates variables to the robot's new location
void update_position(int X, int Y){
  // clear robot's previous position from local map 
  local_map[robot_X][robot_Y] = 0;

  // update local map and robot's coordinates with new position
  local_map[X][Y] = 2;
  robot_X = X;
  robot_Y = Y;
}
// updates orientation to the robot's new orientation
void update_orientation(int orient){
  robot_orientation = orient;
}

void scan_360(RPLidar lidar){
  // The degree map checks whether the data given by the lidar has already
  // been received in the robot's current position based on degree
  int degrees_received = 0;
  bool degree[360];
  for(int i =0; i < 360; i++)
    degree[i] = false;

  while(degrees_received == MIN_DEGREES){
    // collect angle and distance 
    int angle = lidar.getCurrentPoint().angle;
    float distance = lidar.getCurrentPoint().distance;

    // check if angle has already been received
    if(!degree[int(angle)])
      continue;

    // store new angle and update count
    degree[int(angle)] = true;
    degrees_received++;

    // create data to transfer
    String data = String(angle, 0) + "," + String(distance, 2);
   
    send_data(data);
  }
}


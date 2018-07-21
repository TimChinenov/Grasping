using namespace std;
#include <vector>
#include <cstddef>
#include <iostream>
#include "robot.h"

#include <Eigen/Dense>
using Eigen::MatrixXd;

Robot::Robot(){
  //matrix for first prismatic arm
  l1(0,0) = 12.0;
  l1(1,0) = 0;
  l1(2,0) = 0;
  //matrix for second prismatic arm
  l2(0,0) = 0;
  l2(1,0) = -7.5;
  l2(2,0) = 0;
  //matrix for origin
  P0(0,0) = 0;
  P0(1,0) = 10;
  P0(2,0) = 0;
  //set the distance of the claw center
  cC(0,0) = 0;
  cC(1,0) = -1.25;
  cC(1,0) = 0;
  //set the prismatic angles
  q1 = 0;
  q2 = 0;
}

MatrixXf Robot::ClawCenter(float[2] Q){
  float a1 = Q[0];
  float a2 = Q[1];
  clawCent = P0 + q1*l1 + q2*l2 + cC;
  return clawCent;
}

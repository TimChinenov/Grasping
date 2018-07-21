using namespace std;
#include <Eigen/Dense>

using Eigen::MatrixXf;

class Robot{
  private:
    //the max lengths of the prismatic joints
    MatrixXf l1(3,1);
    MatrixXf l2(3,1);
    MatrixXf P0(3,1);
    MatrixXf cC(3,1);
    // //the dimanesions of the claw
    // float c1;
    // float c2;
    // float c3;
    //the position of the robot along the prismatic joints
    float q1;
    float q2;
    // //the angles of the claw
    // float q3;
    // float q4;
    //the position of the claw centroid;
    MatrixXf clawCent(3,1);
  public:
    //default constructor
    Robot();
    float[2] fwdKin(float[4]);
    float[4] invKin(float[2]);
    //destructor
    ~Robot();
};

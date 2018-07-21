using namespace std;
#include <Eigen/Dense>
using Eigen::MatrixXf;
using Eigen::Vector2f;

class Obs{
  private:
    vector<MatrixXf> Edges;
    Vector2f centroid;
    //coefficient of friction
    float mu;
    //function for finding the half-edges
    //takes centroid and builds obs around it
    vector<MatrixXf> makeEdges();
  public:
    Obs(float,float center []);
    //copy constructor
    Obs(const Obs&);
    //////establish getters
    //the following will get the half-edges of the object
    vector<MatrixXf> getEdges();
    //the following will get the center of the object
    Vector2f getCentroid();
    //get coefficient of friction
    float getMu();
    //////
    //The following determines whether a point is in the object
    //point is a 2d matrix;
    bool isInside(Vector2f);

};

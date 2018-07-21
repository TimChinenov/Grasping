using namespace std;
#include <vector>
#include <cstddef>
#include <iostream>
#include "obs.h"


Obs::Obs(float coef, float center []){
  //make sure coefficient of friction is a fraction
  if (coef > 1 || coef < 0){
    throw std::string("coefficient of friction out of bounds");
  }
  else{
    mu = coef;
  }
  centroid(0) = center[0];
  centroid(1) = center[1];
  Edges = makeEdges();
}

Obs::Obs(const Obs& n_obs){
//will make this later.
}

//return the edges
vector<MatrixXf> Obs::getEdges(){
  return Edges;
}

//recturn centroid
Vector2f Obs::getCentroid(){
  return centroid;
}

//return the coefficient of friction
float Obs::getMu(){
  return mu;
}

//the following function checks if a point is inside
//the object.
bool Obs::isInside(Vector2f point){
  //go through each edge
  bool inside = false;
  for(int itr = 0;itr<Edges.size();itr++){
    //retrieve information from matrices
    float Ax = Edges[itr](0,0);
    float Ay = Edges[itr](0,1);
    float Bx = Edges[itr](1,0);
    float By = Edges[itr](1,1);
    float X = point(0);
    float Y = point(1);
    //take determinant and find sign
    float pos = (Bx-Ax)*(Y-Ay)-(By-Ay)*(X-Ax);
    if (pos >= 0){inside = true;}
    else{return false;}
  }
  return inside;
}

// function for making edges
// this will need to be made into a child class
// in the future
vector<MatrixXf> Obs::makeEdges(){
  //This function is very dependent on the shape we are making
  //in this case, the "I" shape is being made. There are 12
  //half edges that need to be made for the shape.
  MatrixXf cent(2,2);
  cent << centroid(0),centroid(0),
          centroid(1),centroid(1);
  MatrixXf v1(2,2);
  MatrixXf v2(2,2);
  MatrixXf v3(2,2);
  MatrixXf v4(2,2);
  MatrixXf v5(2,2);
  MatrixXf v6(2,2);
  MatrixXf v7(2,2);
  MatrixXf v8(2,2);
  MatrixXf v9(2,2);
  MatrixXf v10(2,2);
  MatrixXf v11(2,2);
  MatrixXf v12(2,2);
  //vector 1
  MatrixXf offset(2,2);
  offset(0,0) = 1;offset(0,1) = 1;offset(1,0) = 1.45;offset(1,1) = 1.45;
  v1(0,0)=0; v1(0,1)=-2; v1(1,0)=0;v1(1,1)=0;
  v1 = v1 + offset + cent;
  //vector 2
  offset << -1,-1,
            1.45,1.45;
  v2 << 0,0,
        0,-.2;
  v2 = v2+offset+ cent;
  //vector 3
  offset << -1,-1,
            1.25,1.25;
  v3 << 0,0.2,
        0,0;
  v3 = v3+offset+ cent;
  //vector 4
  offset << -0.8,-0.8,
            1.25,1.25;
  v4 << 0,0,
        0,-2.5;
  v4 = v4+offset+ cent;
  //vector 5
  offset << -0.8,-0.8,
            -1.25,-1.25;
  v5 << 0,-0.2,
        0,0;
  v5 = v5+offset+ cent;
  //vector 6
  offset << -1,-1,
            -1.25,-1.25;
  v6 << 0,0,
        0,-.2;
  v6 = v6+offset+ cent;
  //vector 7
  offset << -1,-1,
            -1.45,-1.45;
  v7 << 0,2,
        0,0;
  v7 = v7 + offset+ cent;
  //vector 8
  offset << 1,1,
            -1.45,-1.45;
  v8 << 0,0,
        0,0.2;
  v8 = v8+offset+ cent;
  //vector 9
  offset << 1,1,
            -1.25,-1.25;
  v9 << 0,-.2,
        0,0;
  v9 = v9+offset+ cent;
  //vector 10
  offset << 0.8,0.8,
            -1.25,-1.25;
  v10 << 0,0,
         0,2.5;
  v10 = v10 + offset+ cent;
  //vector 11
  offset << 0.8,0.8,
            1.25,1.25;
  v11 << 0,0.2,
         0,0;
  v11 = v11 + offset+ cent;
  //vector 12
  offset << 1,1,
            1.25,1.25;
  v12 << 0,0,
         0,0.2;
  v12 = v12 + offset+ cent;
  //add all vectors to vector and return
  vector<MatrixXf> halfEdges;
  halfEdges.push_back(v1);halfEdges.push_back(v2);
  halfEdges.push_back(v3);halfEdges.push_back(v4);
  halfEdges.push_back(v5);halfEdges.push_back(v6);
  halfEdges.push_back(v7);halfEdges.push_back(v8);
  halfEdges.push_back(v9);halfEdges.push_back(v10);
  halfEdges.push_back(v11);halfEdges.push_back(v12);
  return halfEdges;
}

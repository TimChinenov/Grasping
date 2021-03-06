#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdbool>
#include <Eigen/Dense>
#include <math.h>
#include <fstream>
#include <string>
//following are needed for random numbers
#include <stdlib.h>
#include <time.h>
//python calls
#include <Python.h>
/////////////////////////////////////////
#include "node.h"
#include "obs.h"
using namespace std;
using Eigen::MatrixXd;
/*
Things to do:
ok obs can be made
and nodes are good to
lets get that RRT* algorithm going
-current approach to picking node inside object, takes the first node.
this may not always be good
*/

//prototype functions
Node* findClosest(Node target, vector<Node*> &allNodes);
vector<Node*> findNeighbors(Node &center, vector<Node*> &allNodes,float radius);
Node* bestValue(Node &center, vector<Node*> &neighbors);
vector<Node*> chainNodes(Node &start, Node &end, float step);
float dist(const Vector2f  &pt1,const Vector2f  &pt2);
void makeRelation(Node &parent,Node &child);
void addNodes(vector<Node> &allN, vector<Node*> &newN);
vector<Node*> RRTstar(float Qstart [],Obs &obstacle);
void saveData(ofstream &file, vector<Node*> &nodes);
void savePath(ofstream &file, Node* node);
//

int main(int argc, char *argv[]){
  //declare output file stream
  ofstream resultsFile("results.txt");
  ofstream pathFile("path.txt");
  float pos[2] = {0,10};
  //
  //create obstacle item
  float obsCenter[2] = {5,1.45}; //temp values for obstacle center
  float coef = 0.5;
  Obs obs1(coef,obsCenter);
  srand(time(NULL));
  vector<Node*> allNodes = RRTstar(pos,obs1);
  // for(int j = 0; j<allNodes.size();j++)
  // {
  //   cout << (allNodes[j]->getValue()) << endl;
  // }
  cout << "Number of nodes generated: " << allNodes.size() << endl;
  cout << "Success!" << endl;
  saveData(resultsFile,allNodes);
  //check if the final node completed the path
  if(obs1.isInside(allNodes[allNodes.size()-1]->getPosition()))
  {
    //if it did, then we can generate a path
    cout << "path was found" << endl;
    savePath(pathFile,allNodes[allNodes.size()-1]);
  }
  //The following executes the python plotter to show the results
  system("python plotter.py");
  // Py_Initialize();
  // PyRun_SimpleString("import sys");
  // PyRun_SimpleString("sys.path.append('plotter.py')");
  // Py_Finalize();
  //End python script
}

//the following is a simple linear algorithm to find the closest node
//to an added node
Node* findClosest(Node target, vector<Node*> &allNodes)
{
  float best_dist = 10000; //set the best distance to something big
  Node* best; //best is empty
  for(int itr = 0; itr < allNodes.size(); itr++)
  { //find the distance between the two ndoes
    Vector2f one = target.getPosition();
    Vector2f two = allNodes[itr]->getPosition();
    float diff = dist(one,two);
    if(diff<best_dist)//check if the distance is smaller than current best
    {
      best_dist = diff;
      best = (allNodes[itr]);
    }
  }
  return best;
}
//The following function finds all the nodes that are in the
//neighborhood
vector<Node*> findNeighbors(Node &center, vector<Node*> &allNodes,float radius){
  //final vector that will be returned. Neighbor pointers placed here
  vector<Node*> neighbors; //
  Vector2f centPos = center.getPosition();
  for(int itr = 0 ; itr < allNodes.size(); itr++){

    //if the distance is less/equal to the radius, add it to the vector
    float val = dist(centPos,allNodes[itr]->getPosition());
    // cout << "The center position is: " << centPos <<endl;
    // cout <<"The nodes positions is: " <<allNodes[itr].getPosition()<<endl;
    // cout <<"The distance between the two is: "<<val<<endl;
    if(val <= radius){
      Node* p = allNodes[itr];
      neighbors.push_back(p);
    }
  }
  // cout << "size of neighbors in the function: " << neighbors.size() << endl;
  return neighbors;
}

//function finds the best value alternative in the
//region of a center node neighbors
Node* bestValue(Node &center, vector<Node*> &neighbors){
  Node* bestNode = new Node();
  float bestValue = center.getValue();
  Vector2f centPos = center.getPosition();
  for(int itr = 0; itr < neighbors.size(); itr++)
  {
    float tempVal = neighbors[itr]->getValue();
    Vector2f tempPos = neighbors[itr]->getPosition();
    float distance  = dist(tempPos,centPos);
    if(bestValue > tempVal + distance){
      if (bestNode->getValue() == -1)
      {
        delete bestNode;
        bestNode = NULL;
      }
      bestNode = neighbors[itr];
      bestValue = tempVal + distance;
    }
  }
  return bestNode;
}

vector<Node*> chainNodes(Node &start, Node &end, float step){
  //find the distance between the two
  vector<Node*> nodeList;
  Vector2f spos = start.getPosition();
  Vector2f epos = end.getPosition();
  float diff = dist(spos,epos);
  float nodeDiff;
  //find the number of nodes that need to be generated.
  int numNodes = static_cast<int>(diff/step);
  //find the slope of the two points
  float slope;
  float theta;
  //the denominator is not 0, find the slope the normal way
  if(spos(0) != epos(0))
  {
    slope = (spos(1)-epos(1))/(spos(0)-epos(0));
    theta = atan(slope);
  }
  //otherwise set slope to null
  else
  {
    slope = NULL;
  }
  int dircX = 1;
  int dircY = 1;
  //change vector direction depending on conditions
  if (spos(1) > epos(1) && spos(0) > epos(0))
  {
    dircX = -1;
    dircY = -1;
  }
  if (spos(0) > epos(0) && spos(1) < epos(1))
  {
    dircX = -1;
    dircY = -1;
  }

  //iterate through each node that needs to be made
  for(int i = 1; i < numNodes; i++)
  {
    //if the slope is defined, use the following equation
    // to determine the position of the next node.
    float nxy [2];
    if(slope != NULL)
    {
      nxy[0] = spos(0) + cos(theta)*step*i*dircX;
      nxy[1] = spos(0) + sin(theta)*step*i*dircY;
    }
    else
    {
      nxy[0] = spos(0);
      nxy[1] = spos(1) + step*i*dircY;
    }
    //create pointer to new node that may be added to the chain
    Node* tempNode = new Node(nxy);
    if(nodeList.size() > 0){
      Node* par = nodeList[i-2];
      makeRelation(*par, *tempNode);
    }
    //find the distance between the two nodes
    nodeDiff = dist(tempNode->getPosition(),spos);
    //set the value of new node.

    tempNode->setValue(nodeDiff + start.getValue());
    nodeList.push_back(tempNode);
  }
  //once the chain is complete add the ending node
  Node* ending = &end;
  if(nodeList.size() != 0){
    Node* last = (nodeList[nodeList.size()-1]);
    makeRelation(*last,end);
    nodeList.push_back(ending);
    nodeDiff = dist(last->getPosition(),ending->getPosition());
    ending->setValue(nodeDiff+last->getValue());
  }
  else{
    nodeDiff = dist(end.getPosition(),start.getPosition());
    end.setValue(nodeDiff+start.getValue());
    nodeList.push_back(ending);
  }
  return nodeList;
}


//the following returns the disctance between two vectors
float dist(const Vector2f &pt1,const Vector2f &pt2)
{
  return sqrt((pt1(0)-pt2(0))*(pt1(0)-pt2(0))+(pt1(1)-pt2(1))*(pt1(1)-pt2(1)));
}

//the following function handles making a child-parent relation
//between two nodes
void makeRelation(Node &parent,Node &child){
  Node *p = &parent; //make pointer to the parent
  Node *c = &child; //make pointer to the child
  parent.addChild(c); //add child to the parent
  child.setParent(p); // add a parent to the child
}

//
void addNodes(vector<Node> &allN, vector<Node*> &newN){
  for(int itr = 0; itr< newN.size();itr++){
    allN.push_back(*newN[itr]);
  }
}

// void clearOldNodes(vector<*Node> newN){
//   return;
// }

vector<Node*> RRTstar(float Qstart [],Obs &obstacle){
  float RAD = 1.5; //neighbor radius
  int NODE_SIZE = 500; //lower bound of of Nodes to produce
  int counter = 0; //how many iterations have been completed
  float STEP_SIZE = 0.45; //step discretization of nodes
  //boolean that keeps track of whether a node in the obs has been
  //generated
  bool inObs = false;
  //create nodes for starting and ending position
  Node start(Qstart);
  Node* sp = &start;
  Node* end;
  start.setValue(0.0); //set value of initial node
  //create vectors for all nodes
  vector<Node*> AllNodes;
  //create a pointer vector for just the new nodes
  vector<Node*> NewNodes;
  //add the first node to the start and ending nodes
  AllNodes.push_back(sp);
  NewNodes.push_back(sp);

  int count = 0;
  //start RRTstar graph generation
  while(AllNodes.size() < NODE_SIZE  || inObs == false){
    //check if any of the newly added nodes are in the obs
    //if a new point is in the obstacle, a path is found
    if(!inObs){
      for(int itr = 0; itr < NewNodes.size(); itr++)
      {
        if (obstacle.isInside(NewNodes[itr]->getPosition())){
          inObs = true; //set a node in obstacle bool to true
          Vector2f finalPos = (NewNodes[itr]->getPosition());
          float Qend[2] = {finalPos(0),finalPos(1)};
          //create new node representing the end
          end = new Node(Qend);
          makeRelation(*(NewNodes[itr]),*end);
          break;
        }
      }
    }
    //now generate random (x,y)
    float x = static_cast <float> (rand())/(static_cast <float> (RAND_MAX/12));
    float y = static_cast <float> (rand())/(static_cast <float> (RAND_MAX/10));
    if(x > 12 || y >10 || x<0 || y <0 ){continue;}
    // cout << "(x,y) = (" << x << ","<<y<<")"<< endl;
    //generate a new node with the random position
    float new_pos [2] = {x,y};
    Node* new_node = new Node(new_pos);
    //find the closest node by distance
    Node* closest;
    closest = findClosest(new_pos, AllNodes);
    // //find the distance between the two
    float clstDist = dist(new_node->getPosition(),closest->getPosition());
    //set the value of the new node to the distance of the closest node
    //plus the value of the closest node
    // // cout << "closests position" << closest->getPosition() << endl;
    // // cout << "closests value" << closest->getValue() << endl;
    new_node->setValue(clstDist + closest->getValue());
    //find the neighbors of the new Node
    // cout <<"The new nodes position: " << new_node.getPosition() << endl;
    // cout <<"The new nodes value: " << new_node.getValue() << endl;
    vector<Node*> neighbors = findNeighbors(*new_node,AllNodes,RAD);
    Node* bestNode = bestValue(*new_node,neighbors);
    //check if a better node was found
    if(bestNode->getValue() == -1)
    {
       //if not, set the best node to the closest node.
       bestNode = closest;
    }
    else{
       //other wise set the new nodes cost.
       new_node->setValue(bestNode->getValue() + dist(new_node->getPosition(),
                          bestNode->getPosition()));
     }
    //rewireing of the path will be added in a future patch :)
    // NewNodes.clear();
    // NewNodes = chainNodes(*bestNode,*new_node,0.45);
    //
    NewNodes = {new_node};
    makeRelation(*bestNode,*(NewNodes[0]));
    for(int itr = 0; itr< NewNodes.size();itr++){
    //   // cout << (*NewNodes[itr]).getPosition() << endl;
       AllNodes.push_back(NewNodes[itr]);//<----Something wrong is happening here. The nodes are getting cleared?
    }
  }
  // for(int k = 0; k < AllNodes.size();k++){
  //   cout << AllNodes[k]->getPosition() <<endl;
  // }
  if(AllNodes.size() > NODE_SIZE  && inObs != false){
    AllNodes.push_back(end);
  }
  return AllNodes;
}

//Function takes a file stream and nodes and saves
//each nodes positions along with its childs positions in the format:
//(x,y);(x1,y1)(x2,y2)....(xm,yn)
//currently designed poorly, perform using DFS in the future
void saveData(ofstream &file, vector<Node*> &nodes){
  string line = "";
  Vector2f pos;
  for(int itr = 0; itr < nodes.size();itr++)
  {
    pos = nodes[itr]->getPosition();
    line = "("+to_string(pos[0])+","+to_string(pos[1])+");";
    vector<Node*>* children = nodes[itr]->getChildren();
    if((*children).size() < 1000){
      //iterate through children of parent.
      for(int jtr = 0; jtr < (*children).size();jtr++){
        //get position of the child
        Vector2f cpos = (*children)[jtr]->getPosition();
        line = line + "("+to_string(cpos[0])+","+to_string(cpos[1])+")";
      }
    }
    line = line + "\n";
    //print line to the file
    file << line;
    //refresh line string value
    line = "";
  }
}

void savePath(ofstream &file, Node* node){
  Node* tracker = node;
  string line = "";
  while(tracker != NULL){
    Vector2f cpos = tracker->getPosition();
    line = "("+to_string(cpos[0])+","+to_string(cpos[1])+")\n";
    file << line;
    line = "";
    tracker = tracker->getParent();
  }
}

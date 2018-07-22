using namespace std;
#include <vector>
#include <cstddef>
#include <iostream>
#include "node.h"
Node::Node(){
  value = -1;
}

//constructor
Node::Node(float pos []){
  position(0) = pos[0];
  position(1) = pos[1];
  vector<Node*> children;
  Node *Parent = NULL;
  value = 1000000000;
  visited = false;
}
//copy constructor
Node::Node(const Node &n_in){
//well come back to this later
}


//getter
Vector2f Node::getPosition(){
  return position;
}

Node* Node::getParent(){
  return Parent;
}

vector<Node*>* Node::getChildren(){
  vector<Node*>* p = &children;
  return p;
}

bool Node::getVisStat(){
  return visited;
}

double Node::getValue(){
  return value;
}
//setter
Node* Node::setParent(Node* newP){
  Parent = newP;
  return Parent;
}

Node* Node::addChild(Node* newC){
  children.push_back(newC);
}

bool Node::setVisSat(bool stat){
  visited = stat;
  return visited;
}

double Node::setValue(double val){
  value  = val;
  return value;
}

//destructor
Node::~Node(){
}

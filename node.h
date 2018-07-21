using namespace std;
#include <Eigen/Dense>
using Eigen::MatrixXf;
using Eigen::Vector2f;

class Node{
  private:
    //holds position of node
    Vector2f position;
    //holds pointers to children
    vector<Node*> children;
    //holds pointer to parent
    Node *Parent;
    //holds value of node
    double value;
    //holds value if has been visited
    bool visited;

  public:
    Node();
    //constructor
    Node(float []);
    //copy constructor
    Node(const Node&);
    //getters
    Vector2f getPosition();
    Node* getParent();
    vector<Node*> getChildren();
    bool getVisStat();
    double getValue();
    //setters
    Node* setParent(Node*);
    Node* addChild(Node*);
    bool setVisSat(bool);
    double setValue(double);
    //destructor
    ~Node();

};

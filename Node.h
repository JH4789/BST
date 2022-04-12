#ifndef NODEHEADER
#define NODEHEADER
#include <iostream>
using namespace std;
//Nothing to see here
class Node{
 public:
  Node(int newdata);
  void setData(int newdata);
  int getData();
  int getSLeft();
  int getSRight();
  ~Node();
  void setLeft(Node*);
  void setRight(Node*);
  Node* getLeft();
  Node* getRight();
 private:
  int data;
  Node* left;
  Node* right;
};
#endif

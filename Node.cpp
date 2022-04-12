#include "Node.h"
//Standard node construction, copied from previous projects
Node::Node(int newdata) {
  data = newdata;
  left = NULL;
  right = NULL;
}
Node::~Node() {
  left = NULL;
  right = NULL;
}
void Node::setData(int newdata) {
  data = newdata;
}
int Node::getData() {
  return data;
}
void Node::setLeft(Node* newleft) {
  left = newleft;
}
void Node::setRight(Node* newright) {
  right = newright;
}
Node* Node::getLeft() {
  return left;
}
Node* Node::getRight() {
  return right;
}

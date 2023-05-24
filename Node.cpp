#include "Node.h"

// ==========
// Accessors
// ==========
string Node::getKey() const {
  return key;
}

int Node::getCount() const {
  return count;
}

Node* Node::getLeft() const {
  return leftSubtree;
}

Node* Node::getRight() const {
  return rightSubtree;
}

int Node::getHeight() const {
  return height;
}

// ==========
//  Mutators
// ==========
void Node::copyFrom(Node *node) {
  key = node->getKey();
  count = node->getCount();
}

void Node::incrementCount() {
  count++;
}

void Node::decrementCount() {
  count--;
}

void Node::setLeft(Node *node) {
  leftSubtree = node; 
}

void Node::setRight(Node *node) {
  rightSubtree = node; 
}

void Node::deleteLeft() {
  leftSubtree = 0;
}

void Node::deleteRight() { 
  rightSubtree = 0;
}

void Node::incrementHeight() {
  ++height;
}

void Node::setParent(Node *node) {
  parent = node;
}


// ==========[]
// Comparators
// ==========
bool Node::operator==(const Node &node) {
  return node.getKey() == key;
}


// ==========
//  Printing
// ==========

ostream& operator<<(ostream &out, const Node &node) {
  out << node.key << "(" << node.count << ")";
  return out;
}

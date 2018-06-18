#include "Node.h"
#include <cstddef>

Node::Node(){
  left = NULL;
  right = NULL;
  parent = NULL;
  content = NULL;
  sibiling = NULL;
  //1 is red, 2 is black
  color = 1;
}

// getters
Node * Node::getRight(){
  return right;
}

Node * Node::getLeft(){
  return left;
}

Node * Node::getParent(){
  return parent;
}

Node * Node::getSibiling() {
  return sibiling;
}

int Node::getContent(){
  return content;
}

int Node::getColor() {
  return color;
}

// setters
void Node::setContent(int newContent){
  content = newContent;
}

void Node::setRight(Node* newRight){
  right = newRight;
}

void Node::setLeft(Node* newLeft){
  left = newLeft;
}

void Node::setParent(Node* newParent){
  parent = newParent;
}

void Node::setColor(int newColor){
  color = newColor;
}

void Node::setSibiling(Node* newSibiling){
  sibiling = newSibiling;
}


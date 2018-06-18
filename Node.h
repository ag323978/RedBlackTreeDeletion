#ifndef NODE_H
#define NODE_H

class Node{
 public:
  Node();

  // getters
  Node * getRight();
  Node * getLeft();
  Node * getParent();
  Node * getSibiling();
  int getColor();
  int getContent();

  // setters
  void setContent(int);
  void setLeft(Node*);
  void setRight(Node*);
  void setParent(Node*);
  void setColor(int);
  void setSibiling(Node*);

  ~Node();
 private:
  Node* left;
  Node* right;
  Node* parent;
  Node* sibiling;
  int content;
  int color;
};
#endif

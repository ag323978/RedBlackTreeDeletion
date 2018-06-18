/*
 * Author: Aryan GunewNodea
 * Red-Black Tree (RBT): this program does the same thing as RBT Insertion but allows the user to also delete and search for nodes
 */

#include "Node.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

//declare methods
Node* addNode(Node* head, Node* newNode);
bool search(Node* root, int num);
void rotateLeft(Node *&root, Node  *newNode);
void rotateRight(Node *&root, Node *newNode);
void correctTree(Node* &root, Node* &newNode);
void print(Node * head, int space);
void case1(Node *&root, Node *n);
void case2(Node *&root, Node *n);
void case3(Node *&root, Node *n);
void case4(Node *&root, Node *n);
void case5(Node *&root, Node *n);
void case6(Node *&root, Node *n);
void delete_node(Node *&root, int num);
void replaceNode(Node *& , Node *);

int main(){

  Node* head = NULL;

  cout << "'ADD' to add a number." << endl;
  cout << "'PRINT' to print the tree." << endl; 
  cout << "'READ' to read in numbers from a file." << endl;
  cout << "'DELETE' to delete a number." << endl;
  cout << "'SEARCH' to search for a value." << endl;
  cout << "Or 'EXIT' to exit the program" << endl;
    
  while(1){
    cout << '\n';
    cout << "Enter a command: ";
    char* command = new char[10];
    cin.getline(command, 10);
    int number = 0;
    if(strcmp(command, "ADD") == 0){
      //allows adding 1 number to the tree
      cout << "Enter the number you want to add: ";
      cin >> number;
      cin.get();
      //makes a new node with the number to be added
      Node* newNode = new Node();
      newNode->setContent(number);
      //if this is the first time (creating the tree) this function still works because a NULL pointer for head was made
      head = addNode(head, newNode);
      //calls the method to fix the tree after every insertion
      correctTree(head, newNode);
    }else if(strcmp(command, "PRINT") == 0){
      if(head == NULL){
	cout << "There is nothing in the tree" << endl;
      }else{
	print(head, 0);
	cout << '\n';
      }
    }else if(strcmp(command, "DELETE") == 0){
      cout << "Enter the number you want to delete: ";
      cin >> number;			
      cin.get();
      delete_node(head, number);
    }
    else if(strcmp(command, "READ") == 0){
		
      int count = 0;
      int * stor = new int[1000];
      //gets filename
      cout << "Enter the filename: ";
      char* filename = new char[50];
      cin.getline(filename, 50);
      ifstream inFile;
      inFile.open(filename);
      //puts all into the storage of numbers starting from 1
      char* input2  = new char[400];		
      inFile.getline(input2, 400);
      char* token = strtok(input2, ",");
		
      while(token != NULL){
	//changes it to int and puts it in the array starting from 1
	stor[count] = atoi(token);
	//deletes token
	token = strtok(NULL, ", ");
	count ++;
      }
      //for each item in the storage call the addNode and then correctTree, one by one
      for(int i =0; i< count; i++){
	Node* newNode = new Node();
	newNode->setContent(stor[i]);
	head = addNode(head, newNode);
	correctTree(head, newNode);
      }
	
    }else if(strcmp(command, "SEARCH") == 0){
            
      cout << "Enter the value you want to search for: ";
      int searchNum = 0;
      cin >> searchNum;
      cin.get();
      if(search(head, searchNum)){
	cout << "The tree contains the number."<< endl;
      }else{
	cout << "The tree does not contain the number."<< endl;
      }
    }
    else if(strcmp(command, "EXIT") == 0){
      exit(0);
    }
	
  }	

}

//recursive function that returns the head (usually same as input)
Node* addNode(Node* head, Node* newNode){
  if(head==NULL){
    //the root of the new tree is the new node to be added
    return newNode;
  }else if(head->getContent()>=newNode->getContent()){
    head->setLeft(addNode(head->getLeft(), newNode));
    //set parent of the new node
    head->getLeft()->setParent(head);
  }else if(head->getContent()<newNode->getContent()){
    head->setRight(addNode(head->getRight(), newNode));
    //set parent of the new node
    head->getRight()->setParent(head);
  }
  return head;
}

// performs a left rotation
void rotateLeft(Node *&root, Node *newNode)
{
  //makes a right node of the new node for easier rotation
  Node *right = newNode->getRight();
  newNode->setRight(right->getLeft());
  //checks if the node to be set actually exist before proceding with rotation
  if (newNode->getRight() != NULL){
    newNode->getRight()->setParent(newNode);
  }
  right->setParent(newNode->getParent());
  if (newNode->getParent() == NULL){
    root = right;
  }else if (newNode == newNode->getParent()->getLeft()){
    newNode->getParent()->setLeft(right);
  }
  else{
    newNode->getParent()->setRight(right);
  }
  right->setLeft(newNode);
  newNode->setParent(right);
}
//same thing but just the other way
void rotateRight(Node *&root, Node *newNode)
{
  Node *left = newNode->getLeft();
  newNode->setLeft(left->getRight());
  if (newNode->getLeft() != NULL){
    newNode->getLeft()->setParent(newNode);
  }
  left->setParent(newNode->getParent());
 
  if (newNode->getParent() == NULL){
    root = left;
  }
  else if (newNode == newNode->getParent()->getLeft()){
    newNode->getParent()->setLeft(left);
  }
  else{
    newNode->getParent()->setRight(left);
  }
  left->setRight(newNode);
  newNode->setParent(left);
}

//call this function to fix the tree after every insertion
void correctTree(Node* &root, Node* &newNode){
  //makes parent and grandparent of newly inserted node (helps with checking uncle and if parent is left or right)
  Node *parent = NULL;
  Node *grandParent = NULL;
  while ((newNode != root) && (newNode->getColor() != 2) && (newNode->getParent()->getColor() == 1)) {
      //set variables
      parent = newNode->getParent();
      grandParent = newNode->getParent()->getParent();
      //if the parent is the left of grandparent
      if (parent == grandParent->getLeft())
        {
	  Node *uncle_pt = grandParent->getRight();
	  //the uncle is red - just recolor some nodes, no rotation is needed
	  if (uncle_pt != NULL && uncle_pt->getColor() == 1)
            {
	      grandParent->setColor(1);
	      parent->setColor(2);
	      uncle_pt->setColor(2);
	      newNode = grandParent;
            }
 	
	  else{
          
	    //  if the new node is the right of parent rotate the tree left
	    if (newNode == parent->getRight())
	      {
		rotateLeft(root, parent);
		newNode = parent;
		parent = newNode->getParent();
	      }
	    rotateRight(root, grandParent);
	    int parentcolor = parent->getColor();
	    int grandcolor = grandParent->getColor();
	    parent->setColor(grandcolor);
	    grandParent->setColor(parentcolor);
                
	    newNode = parent;
	  }
        }
 
      //the parent is right of grandparent
      else
        {
	  Node *uncle_pt = grandParent->getLeft();
 
	  // if the uncle is read then recolor
	  if ((uncle_pt != NULL) && (uncle_pt->getColor() == 1))
            {
	      grandParent->setColor(1);
	      parent->setColor(2);
	      uncle_pt->setColor(2);
	      newNode = grandParent;
            }
	  else {
	    //the new node is left of its parent
	    if (newNode == parent->getLeft())
	      {
		rotateRight(root, parent);
		newNode = parent;
		parent = newNode->getParent();
	      }
	    rotateLeft(root, grandParent);
	    int parentcolor = parent->getColor();
	    int grandcolor = grandParent->getColor();
	    parent->setColor(grandcolor);
	    grandParent->setColor(parentcolor);
	    newNode = parent;
	  }
        }
    }
  //set the root to be black (because the root must always be black in the end)
  root->setColor(2);

}

//prints the tree spacing to make things look clear
void print(Node* head, int space){
  if (head == NULL)
    return;
  space += 10;
  print(head->getRight(), space);
  cout << '\n';
  for (int i = 10; i < space; i++)
    cout << " ";
	
  if(head->getColor()==1){
    cout <<"\033[1;31m" << head->getContent()<< "\033[0m";
  }else{
    cout << "\033[30;47m" << head->getContent() << "\33[0m";
  }
  print(head->getLeft(), space);
}

bool search(Node* root, int num){
  if(root!=NULL){
    if(root->getContent() == num){
      return true;
    }else if(root->getContent() > num){
      if(search(root->getLeft(),num)){
	return true;
      } 
    }else{
      if(search(root->getRight(), num)){
	return true;
      }
    }
  }
  return false;
}

//returns the minimum node - used in deletion (not right now though, just when this was a bst)
Node* minValueNode(Node* node){
  Node* current = node;
  while(current->getLeft()!=NULL){
    current = current->getLeft();
  }
  return current;
}

Node* sibling(Node* n){
  Node* p = n->getParent();
  if(p==NULL){
    return NULL;
  }else if(n == p->getLeft()){
    return p->getRight();
  }else if(n == p->getRight()){
    return p->getLeft();
  }

}

void replaceNode(Node *&n, Node *child){	
  if(n->getParent()!=NULL){
    cout << "to be replaced parent not NULL";
    cout << n->getParent()->getContent();		
    child->setParent(n->getParent());
   
    if( n == n->getParent()->getLeft()){
      n->getParent()->setLeft(child);
    }else{
      n->getParent()->setRight(child);
    }		
  }
  else{
    cout << child->getContent() << endl;
    cout << "to be replaced parent is NULL" ;
    n->setContent(child->getContent());
    n->setLeft(child->getLeft());
    n->setRight(child->getRight());
			
  }
}

void case1(Node *&root, Node *n){
  cout << endl;
  cout << "case 1";
  if(n->getParent()!=NULL){
    case2(root,n);

  }
}

void case2(Node *&root, Node *n){
  cout << "case 2";
  Node* s = sibling(n);
  if(s->getColor() == 1){
    n->getParent()->setColor(1);
    s->setColor(2);
    if( n == n->getParent()->getLeft()){
      rotateLeft(root, n->getParent());
    }else{
      rotateRight(root, n->getParent());
    }         
  }   
  case3(root, n); 
}

void case3(Node *&root, Node *n){
  cout << "case 3" << endl;
  Node* s = sibling(n);
  if((n->getParent()->getColor()==2) && (s->getColor() == 2) && (s->getLeft()==NULL || s->getLeft()->getColor() == 2) && (s->getRight()== NULL || s->getRight()->getColor() == 2)){
    s->setColor(1);
    case1(root, n->getParent());
	
  }else{
    case4(root, n);
    
  }
}

void case4(Node *&root, Node *n){
  cout << "case 4" <<endl;
  Node* s = sibling(n);
  cout << n->getContent();
  cout << n->getParent();
  cout << s->getColor() << endl;
  cout << s->getLeft()<< endl;
  cout << s->getRight() <<endl;
  // if(s->getLeft()!=NULL && s->getRight()!=NULL){
  if((n->getParent()->getColor() == 1) && (s->getColor() == 2) && (s->getLeft()==NULL || s->getLeft()->getColor()==2) && (s->getRight() == NULL || s->getRight()->getColor()==2)){
    s->setColor(1);
    n->getParent()->setColor(2);
  }else{
    case5(root, n);
    
  }    
}

void case5(Node *&root, Node *n){
  cout << "case 5" <<endl;
  Node * s = sibling(n);
  if(s->getColor() == 2){
    if((n==n->getParent()->getLeft()) && (s->getRight()==NULL || s->getRight()->getColor() ==2) && (s->getLeft()!=NULL && s->getLeft()->getColor() == 1)){
      s->setColor(1);
      s->getLeft()->setColor(2);
      rotateRight(root, s);
    }else if((n == n->getParent()->getRight()) && (s->getLeft()==NULL || s->getLeft()->getColor() == 2) && (s->getRight()!=NULL && s->getRight()->getColor()==1)){
      s->setColor(1);
      s->getRight()->setColor(2);
      rotateLeft(root, s);
        
    }
        
  }   
  case6(root, n);
}

void case6(Node *&root, Node *n){
  cout << "case 6" << endl;
  Node* s = sibling(n);
  s->setColor(n->getParent()->getColor());
  n->getParent()->setColor(2);
  if(n==n->getParent()->getLeft()){
    s->getRight()->setColor(2);
    rotateLeft(root, n->getParent());
        
    
  }else{
    s->getLeft()->setColor(2);
    rotateRight(root, n->getParent());
  }
}

Node* findNode(Node* root, int num){
  cout << "root is:" << root->getContent(); 
  if(root->getContent() == num){
    return root;
  }else if(root->getContent() > num){
    return findNode(root->getLeft(),num);         
  }else{
    return findNode(root->getRight(), num);        
  }
  return NULL;
}

void delete_node(Node *&root, int num){
  if(!search(root, num)){
    cout << "number not found, not attempting to delete" << endl;
    return;
  }	
  Node* deletionNode = findNode(root, num);
  cout << deletionNode->getContent() << endl;
	
  if(deletionNode==NULL){
    return;	
  }
  //left and right contain values
  if (deletionNode->getLeft()!=NULL  && deletionNode->getRight()!=NULL ) { 
    cout << "2 children" << endl;
    Node* successor = deletionNode->getRight(); 
    // find successor 
    while (successor->getLeft()!=NULL){ 
      successor = successor->getLeft();
    }
    deletionNode->setContent(successor->getContent()); // copy just the value of the successor
    deletionNode = successor; // set successor to be deleted with one or no child methods that follow
  }
  //if the color is red
  if (deletionNode->getColor()==1) {  
    //delete deletionNode->getRight(); 
    cout << "color is red";
    //redundant if statement
    if(deletionNode->getParent()!=NULL){
      if(deletionNode->getParent()->getLeft() == deletionNode){
	deletionNode->getParent()->setLeft(NULL);
      }else{
	deletionNode->getParent()->setRight(NULL);
      }
    }else{
      //root = NULL;
    }
    //there is left child
  } else if (deletionNode->getLeft()!=NULL) { 
    //cout << "left is not null";
    deletionNode->getLeft()->setColor(2); // red child turns black and takes node to delete's position
    replaceNode(deletionNode, deletionNode->getLeft());
    //there is right child
  } else if (deletionNode->getRight()!=NULL ) { 
    /*cout << "right is not null";*/
		
    deletionNode->getRight()->setColor(2);
    replaceNode(deletionNode, deletionNode->getRight());

    //no children
  } else {
    if(root==deletionNode){
      root = NULL;
    }else{
      //call all the deletion cases
      case1(root, deletionNode); 
      if(deletionNode->getParent()->getLeft() == deletionNode){
	deletionNode->getParent()->setLeft(NULL);
      }else{
	deletionNode->getParent()->setRight(NULL);
      }
    }
				
  }
  return;
}

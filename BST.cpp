/*
Name: Jayden Huang
Date: 4/20/2022
Project: Binary Search Tree, with file load capabilities.
*/
#include <iostream>
#include "Node.h"
#include <cstring>
#include <math.h>
#include <fstream>
void printFormat(Node* head, int space);
void addTree(Node* & head, Node* current, Node* newnode);
void searchTree(Node* current, int data);
void deleteTree(Node* & head, Node* current, Node* parent, int data);
using namespace std;
int main() {
  Node* heaparray[100];
  int sizecount = 1;
  Node* treehead = NULL;
  int input = 0;
  bool running = true;
  char commandinput[7];
  //Main loop
  while(running == true){
    cout << "Please enter your input. Enter ADD to add a number to the tree, PRINT to print the tree, SEARCH to search the tree for a number, FILE to load a tree from the file, DELETE to delete the tree, and QUIT to end the program." << endl;
    cin >> commandinput;
    if(strcmp(commandinput, "ADD") == 0) {
       cout << "Insert number" << endl;
       cin >> input;
       Node* newnode = new Node(input);
       addTree(treehead, treehead, newnode);
    }
    else if (strcmp(commandinput, "PRINT") == 0) {
      printFormat(treehead, 3);
    }
    else if (strcmp(commandinput, "SEARCH") == 0) {
      cout << "Enter the number you would like to search for: " << endl;
      cin >> input;
      searchTree(treehead, input);
    }
    else if (strcmp(commandinput, "FILE") == 0) {
      //Opens from file and iterates through using the same add function
      fstream File;
      int fileinput = 0;
      File.open("File.txt");
      for(int i = 0; i <100; i++) {
	File >> fileinput;
	Node* newnode = new Node(fileinput);
	addTree(treehead, treehead, newnode);
      }
    }
    else if (strcmp(commandinput, "DELETE") == 0) {
       cout << "Enter the number you would like to delete: " << endl;
       cin >> input;
       deleteTree(treehead, treehead, treehead, input);
    }
    else if (strcmp(commandinput, "QUIT") == 0) {
      running = false;
    }
    else {
      cout << "Please enter a valid input" << endl;
    }
  }
  return 0;
}
void addTree(Node* & head, Node* current, Node* newnode) {
  //Sets the new node as head if the tree is empty
  if(head == NULL) {
    head = newnode;
    return;
  }
  //Uses the value of the data to determine where it goes in the tree (DOES NOT ACCOUNT FOR DUPLICATES)
  else {
    if(newnode->getData() > current->getData()) {
      if(current->getRight() == NULL) {
	current->setRight(newnode);
	return;
      }
      else {
        addTree(head, current->getRight(), newnode);
      }
    }
    else if(newnode->getData() < current->getData()) {
    if(current->getLeft() == NULL) {
      current->setLeft(newnode);
      return;
    }
    else {
      addTree(head, current->getLeft(), newnode);
    }
    }
    else {
       if(current->getLeft() == NULL) {
           current->setLeft(newnode);
           return;
       }
       else if(current->getRight() == NULL) {
           current->setRight(newnode);
            return;
       }
       else {
	 return;
       }
    }
  }
  
}
void printFormat(Node* head, int space) {
  //Same print function from heap
  if (head == NULL) {
    return;
  }
    space = space + 5;
    if(head->getRight() != NULL) {
      
    printFormat(head->getRight(), space);
    }
    cout<<endl;
    for (int i = 0; i < space; i++) {
        cout<<" ";
    }
    cout<<head->getData()<<"\n";
    cout << endl;
    if(head->getLeft() != NULL) {
    printFormat(head->getLeft(), space);
    }
}
void searchTree(Node* current, int data) {
  //Goes through the tree, implementation is a little bit messy
  //The while loop here could just be a recursive call
  while(current->getData() != data && current != NULL) {
    if(current != NULL) {
      if(current->getData() > data) {
	current = current->getLeft();
      }
      else {
        current = current->getRight();
      }
    }
    if(current == NULL) {
       break;
    }
  }
  if(current != NULL) {
    if(current->getData() == data) {
    cout << "The element is present in the list!" << endl;
  }
  }
  else {
    cout << "The element is not present in the list!" << endl;
  }
}


void deleteTree(Node* & head, Node* current, Node* parent, int data) {
  //Could use a bit more recursion on the two child case
  if(head == NULL) {
    cout << "The tree is empty!" << endl;
  }
  //Checks for three cases: one child, two children, no children
  //Parent is needed because just calling the destructor was not working
  if(current != NULL) {
    if(current->getData() == data) {
      //No children case
      if(current->getLeft() == NULL && current->getRight() == NULL) {
	if(current == head) {
          delete head;
	  head = NULL;
	}
        else if(parent->getLeft() == current) {
	  parent->setLeft(NULL);
	  delete current;
	}
	else {
          parent->setRight(NULL);
	  delete current;
	}
      }
      //Only right child present case
      else if(current->getLeft() == NULL) {
	if(current == head) {
	  Node* temp = head;
	  head = head->getRight();
	  delete temp;
	}
	else if(parent->getLeft() == current) {
          Node* temp = current;
	  parent->setLeft(current->getRight());
	  delete temp;
	}
	else {
          Node* temp = current;
	  parent->setRight(current->getRight());
	  delete temp;
	}
      }
      //Only left child present case
      else if(current->getRight() == NULL) {
        //cout << "RIGHT" << endl;
	if(current == head) {
	  Node* temp = head;
	  head = head->getLeft();
	  delete temp;
	}
	else if(parent->getLeft() == current) {
          Node* temp = current;
	  parent->setLeft(current->getLeft());
	  delete temp;
	}
	else {
          Node* temp = current;
	  parent->setRight(current->getLeft());
	  delete temp;
	}
      }
      //Two children case
      else {
	//Swaps the current node and its inorder successor
	Node* inorder = current->getRight();
	Node* orderparent = current;
	while(inorder->getLeft() != NULL) {
          orderparent = inorder;
	  inorder = inorder->getLeft();
	}
	int newdata = inorder->getData();
	int deletedata = current->getData();
	inorder->setData(current->getData());
	current->setData(newdata);
	//This should be a recursive call but it wasn't working so I just copied the code
	if(inorder->getLeft() == NULL && inorder->getRight() == NULL) {
          if(orderparent->getLeft() == inorder) {
	    orderparent->setLeft(NULL);
	  }
	  else {
            orderparent->setRight(NULL);
	  }
	  Node* temp = inorder;
	  delete temp;
	}
	else if(inorder->getRight() == NULL) {
          Node* temp = inorder;
	  
	  orderparent->setLeft(inorder->getLeft());
	  delete temp;
	}
	else {
	  Node* temp = inorder;
	  orderparent->setRight(inorder->getRight());
	  delete temp;
	}
      }
    }
    //Same as in print, navigates through the tree
    else if(current->getData() > data) {
      parent = current;
      deleteTree(head, current->getLeft(), parent, data);
    }
    else {
      parent = current;
      deleteTree(head, current->getRight(), parent, data);
    }
  }
}

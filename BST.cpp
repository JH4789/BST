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
    cout << "Please enter your input. Enter ADD to add a number to the heap, PRINT to print the heap, FILE to load a heap from the file, DELETE to delete the heap, and QUIT to end the program." << endl;
    cin >> commandinput;
    if(strcmp(commandinput, "ADD") == 0) {
       cout << "Insert number" << endl;
       cin >> input;
       Node* newnode = new Node(input);
       addTree(treehead, treehead, newnode);
    }
    else if (strcmp(commandinput, "PRINT") == 0) {
      printFormat(treehead, 1);
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
      for(int i = 0; i < 100; i++) {
	File >> fileinput;
	Node* newnode = new Node(fileinput);
	//addHeap(newnode, treehead, heaparray, sizecount);
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
  if(head == NULL) {
    head = newnode;
    return;
  }
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
  if (head == NULL) {
    return;
  }
    space = space + 10;
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
  if(head == NULL) {
    cout << "The tree is empty!" << endl;
  }
  
  if(current != NULL) {
    if(current->getData() == data) {
      if(current->getLeft() == NULL && current->getRight() == NULL) {
        //cout << "Delete attempted!" << endl;
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
      else if(current->getRight() == NULL) {
	if(current == head) {
	  Node* temp = head;
	  head = head->getRight();
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
      else {
	
      }
    }
    else if(current->getData() > data) {
      parent = current;
      deleteTree(head, current->getLeft(), parent, data);
      
    }
    else {
      parent = current;
      deleteTree(head, current->getRight(), parent, data);
    }
  }
    
  
  
  /*
  if(data < head->getData()) {
    deleteTree(head->getLeft(), data);
  }
  else if (data > head->getData()) {
    deleteTree(head->getRight(), data);
  }
  
  else {
    if(head->getLeft() == NULL && head->getRight() == NULL) {
      Node* temp = head;
      head = NULL;
      delete temp;
    }
  }
  */
}

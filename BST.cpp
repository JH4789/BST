#include <iostream>
#include "Node.h"
#include <cstring>
#include <math.h>
#include <fstream>
void printFormat(Node* head, int space);
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
       addHeap(newnode, treehead, heaparray, sizecount);
    }
    else if (strcmp(commandinput, "PRINT") == 0) {
      printFormat(treehead, 1);
    }
    else if (strcmp(commandinput, "FILE") == 0) {
      //Opens from file and iterates through using the same add function
      fstream File;
      int fileinput = 0;
      File.open("File.txt");
      for(int i = 0; i < 100; i++) {
	File >> fileinput;
	Node* newnode = new Node(fileinput);
	addHeap(newnode, treehead, heaparray, sizecount);
      }
    }
    else if (strcmp(commandinput, "DELETE") == 0) {
      //Deletes the heap and resets the important variables and pointers
      deleteTree(heaparray, sizecount-2);
      sizecount = 1;
      treehead = NULL;
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
void addTree(node* & treehead, Node* newnode) {
  if(treehead == NULL) {
    treehead = newnode;
  }
  else {
    
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
 
    if(head->getLeft() != NULL) {
    printFormat(head->getLeft(), space);
    }
}



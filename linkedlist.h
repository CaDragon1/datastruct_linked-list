/*********************
* Author: Caleb Drake
* Class: COSC 2436 Data Structures
* Program: Linked List
* Purpose: This program creates a linkedlist object consisting of nodes that work with the Data struct using pointers.
*          This is the "linkedlist.h" file, which contains all of the linkedlist headers and prototypes.
**********************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Includes data.h
#include "data.h"
#include <iostream>

class LinkedList {

public:
	// Constructor
	LinkedList();
	// Destructor
	~LinkedList();

	bool addNode(int, string*);
	bool deleteNode(int);
	bool getNode(int, Data*);
	void printList(bool = false);
	int getCount();
	bool clearList();
	bool exists(int);

private:
	Node* head;	// The head of the entire list, a pointer to a Node object

	bool makeHead(int, string*);
	bool makeTail(int, string*, Node*);
	bool makeNode(int, string*, Node*);
	bool deleteHead(Node*);
	bool deleteNode(Node*);
};

#endif // !LINKEDLIST_H

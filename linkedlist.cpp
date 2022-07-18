/*********************
* Author: Caleb Drake
* Class: COSC 2436 Data Structures
* Program: Linked List
* Purpose: This program creates a linkedlist object consisting of nodes that work with the Data struct using pointers.
*          This is the "linkedlist.cpp" file, which contains all of the linkedlist methods.
**********************/

#include "linkedlist.h"

LinkedList::LinkedList() {
	head = nullptr;
}

LinkedList::~LinkedList() {
	clearList();
}

bool LinkedList::addNode(int index, string* input) {			// There is definitely a better way to write this to be more efficient
	bool added = false;
	Node* current = head;	// This is to track which node we are in
	if ((index > 0) && (*input != "")) {
		if (!current || index < head->data.id) {				// CHECK: If the head is a nullptr or the index parameter is less than the head's id, make a head.
			added = makeHead(index, input);
		}

		else if (current->next) {								// CHECK: If there is another node in the list, start running through the list.
            while (current->next && current->data.id < index) {		// If current->next points to a valid node and current's id is less than the index parameter, move to the next node in the list. 
                current = current->next;							// I check for (current->next) rather than (current) so that current->data.id doesn't segment.
            }
		}
		if (!added) {
			if (((head == current) && (index > head->data.id)) || ((current->data.id < index) && (!current->next))) {	// If the current node is the head and the index is greater than the head->data.id
				added = makeTail(index, input, current);																// OR the new id is greater than than the current id and the next node is null, makeTail.
			}
			else if (current->data.id != index && !added) {		// The new node can't be a head or tail node by this point. If the current id isn't equal to index, then we need to add a new node.
				added = makeNode(index, input, current->prev);
			}
		}

	}
	return added;
}

bool LinkedList::deleteNode(int index) {
	Node* current = head;
	bool deleted = false;

	if (current) {
		while ((current->data.id != index) && (current->next)) {	// While the current node's index isn't equal to the parameter, move to the next node
			current = current->next;
		}
		if (current->data.id == index) {
			if (current == head) {						// If the current node is the head node, deleteHead.
				deleted = deleteHead(current);
			}
			else {										// If the current node isn't the head node, deleteNode.
				deleted = deleteNode(current);
			}
			delete current;
		}
	}
	return deleted;
}

bool LinkedList::getNode(int index, Data* data) {
	Node* current = head;
	bool got = false;

	if (current) {
		while ((current->data.id != index) && (current->next)) {
			current = current->next;
		}
		if (current) {
			if (current->data.id == index) {
				*data = current->data;
				got = true;
			}
		}
	}

	return got;
}

void LinkedList::printList(bool backward) {
	Node* current = head;
	Node* backCurrent;
	while (current != nullptr) {			// Run through the list until you reach the tail
		if (!backward) {
			std::cout << current->data.id << "  " << current->data.data << std::endl;
		}
		backCurrent = current;
		current = current->next;
	}
	if (backward) {
		while (backCurrent != nullptr) {		// Run through this list backwards until you reach the beginning if backward == true
			std::cout << backCurrent->data.id << "  " << backCurrent->data.data << std::endl;
			backCurrent = backCurrent->prev;
		}
	}
}

int LinkedList::getCount() {
	Node* current = head;
	int count = 0;

    while (current) {
		current = current->next;
		count++;
    }
	return count;
}

bool LinkedList::clearList() {
	Node* current = head;
	bool cleared = false;
	if (current) {
		while (current->next) {
			current = current->next;
			delete current->prev;
		}
		delete current;
		head = nullptr;
	}
	cleared = true;
	return cleared;
}

bool LinkedList::exists(int index) {
	Node* current = head;
	bool exists = false;

	if (current) {
		while (current && (current->data.id != index)) {
			current = current->next;
		}
		if (current) {							// Check to make sure current is valid
			if (current->data.id == index) {
				exists = true;
			}
		}
	}
	
	return exists;
}

bool LinkedList::makeHead(int index, string* data) {
	bool made = false;
	Node* newHead = new Node;
	Node* oldHead = head;
	newHead->prev = nullptr;
	if (!oldHead) {
		newHead->next = nullptr;
	}
	else {
		newHead->next = oldHead;
		oldHead->prev = newHead;
	}
	newHead->data.id = index;
	newHead->data.data = *data;
	head = newHead; 
	made = true;
	return made;
}

bool LinkedList::makeTail(int index, string* data, Node* current) {
	bool made = false;
	Node* listNode = new Node;
	listNode->data.id = index;
	listNode->data.data = *data;
	listNode->next = nullptr;
	listNode->prev = current;
	current->next = listNode;			// Change the node before and after listNode to point to listNode
	made = true;
	return made;
}

bool LinkedList::makeNode(int index, string* data, Node* current) {
	bool made = false;
	Node* listNode = new Node;
	listNode->data.id = index;
	listNode->data.data = *data;
	listNode->next = current->next;
	listNode->prev = current;
	current->next = listNode;			// Change the node before and after listNode to point to listNode
	listNode->next->prev = listNode;
	made = true;
	return made;
}

bool LinkedList::deleteHead(Node* current) {
	bool deleted = false;
	if (current->next) {						// if the current (head) node isn't the tail node
		current->next->prev = nullptr;				// the next node's "prev" attribute = nullptr and becomes the new head
		head = current->next;
		deleted = true;
	}
	else {										// if the current (head) node is the tail node
		head = nullptr;								// the head won't exist after deletion
		deleted = true;
	}
	return deleted;
}

bool LinkedList::deleteNode(Node* current) {
	bool deleted = false;
	if (current->next) {						// if the current node isn't the tail node
		current->next->prev = current->prev;		// make the next and previous nodes point to each other
		current->prev->next = current->next;
		deleted = true;
	}
	else {										// if the current node is the tail node,
		current->prev->next = nullptr;				// make the previous node point to nullptr as its next node
		deleted = true;
	}
	return deleted;
}
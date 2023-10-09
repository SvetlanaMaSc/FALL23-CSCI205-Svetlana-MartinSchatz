/*
	This class defines a singly linked list. It is templated to allow for
	any type of data to be stored in the list. The list is implemented as
	a linked list of nodes. Each node contains a "payload" of templated type
	and a pointer to the next node in the list. The list class tracks the
	head of the list and the size of the list. The list class contains
	methods for adding and removing nodes from the list. The list class
	also contains a method for printing the contents of the list.
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <vector>
using namespace std;


template <class T>
struct Node{
	T item;				// The node's "payload"
	Node<T>* next;		// pointer to the "next" node
};

template <class T>
class LinkedList{
	private:
		Node<T>* head;
		Node<T>* tail;
		Node<T>* newNode(T item);
		string name;

	public:
		LinkedList();								// default constructor
		LinkedList(string nme);								// default constructor
		LinkedList(T payload_array[], int size);	// constructor with payload array
		~LinkedList();								// destructor, frees memory

		string getName();
		Node<T>* getHead();
		void insert(T item);				// insert item at beginning of list
		void insert(T item, int position);	// insert item at position
		void append(T item);				// append item to end of list
		T get(int position);				// get item at position, does not remove item
		T remove(int position);				// remove and return item at position
		T pop();
		void print();						// print list in neat format
		int length();						// return length of list

		int count(T items);
		void remove_duplicates();
		void reverse();
		void append(LinkedList<T> &list);
		void printRecursive(Node<T>* node);
		Node<T>* reverseRecursive(Node<T>* node);
};

// ==================================
// || Constructors
// ==================================
template <class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = head;
}

template <class T>
LinkedList<T>::LinkedList(string n) {
	name = n;
    head = nullptr;
    tail = head;
}

template <class T>
LinkedList<T>::LinkedList(T payload_array[], int size) {
	head = newNode(payload_array[0]);
	Node<T> nodeC = head;
	for (int i = 1; i < size - 1; i++) {
		Node<T>* n = newNode(payload_array[i]);
		nodeC->next = n;
		tail = nodeC;
	}
}

template<class T>
LinkedList<T>::~LinkedList() {
	Node<T>* nodeC = head;
	while (nodeC != nullptr) {
		Node<T>* nextNode = nodeC->next;  // Save the next node
		delete nodeC;            // Delete the current node
		nodeC = nextNode;
	}
	head = nullptr;
}

// ==================================
// || Helper Functions
// ==================================
template <class T>
Node<T>* LinkedList<T>::newNode(T item) {
	Node<T>* n = new Node<T>;
	n->item = item;
	n->next = nullptr;
	return n;
}

// ==================================
// || Methods
// ==================================

/**
 * Get name
*/
template <typename T>
string LinkedList<T>::getName() {
	return name;
}

/**
 * Get head
*/
template <typename T>
Node<T>* LinkedList<T>::getHead() {
	Node<T>* node = head;
	return node;
}

/**
 * Insert element at head
*/
template <class T>
void LinkedList<T>::insert(T item) {
	Node<T>* newN = newNode(item);
	newN->next = head;
	head = newN;
	if (head->next == nullptr) {

		tail = head;
	}
}

/**
 * Insert element at specific position
*/
template <class T>
void LinkedList<T>::insert(T item, int position) {
	Node<T>* newN = newNode(item);
	int count = 0;
	if (head == nullptr) {
		head = newN;
		tail = head;
	}
	else {
		Node<T>* nodeC = head; 
		while (nodeC->next != nullptr) {
			if (count == position) {
				Node<T>* nodeNext = nodeC->next;
				nodeC->next = newN;
				newN->next = nodeNext;
			}
			count++;
		}
	}
}

/**
 * Append node to the tail
*/
template <class T>
void LinkedList<T>::append(T item) {
	if (head == nullptr) {
		head = newNode(item);
		tail = head;
	}
	else {
		Node<T>* nodeC = newNode(item);
		tail->next = nodeC;
		tail = nodeC;

	}
}

/**
 * Get item from list (does not remove)
*/
template <class T>
T LinkedList<T>::get(int position) {
	Node<T>* nodeC = head;
	int pos = 0;
	while (nodeC != nullptr) {
		if (pos == position) {
			return nodeC->item;
		}
		nodeC = nodeC->next;
		pos++;
	}

	throw std::out_of_range("Position out of bounds in LinkedList::get");
}

/**
 * Remove item from specific spot in the list
*/
template <class T>
T LinkedList<T>::remove(int position) {
    if (head == nullptr) {
        throw std::runtime_error("List is empty"); 
    }

    if (position == 0) {  // Special case for head
        Node<T>* temp = head;
        T item = temp->item;
        head = head->next;
        if (head == nullptr) {  // List becomes empty
            tail = nullptr;
        }
        delete temp;
        return item;
    }

    Node<T>* nodePrev = nullptr;
    Node<T>* nodeC = head;
    int pos = 0;
    
    while (nodeC != nullptr && pos != position) {
        nodePrev = nodeC;
        nodeC = nodeC->next;
        pos++;
    }
    
    if (nodeC == nullptr) {  // Position out of bounds
        throw std::runtime_error("Position out of bounds"); 
    }

    // Remove node
    nodePrev->next = nodeC->next;
    if (nodeC->next == nullptr) {  // If removing the last node
        tail = nodePrev;
    }
    T item = nodeC->item;
    delete nodeC;
    return item;
}

template <typename T>
T LinkedList<T>::pop() {
	Node<T>* nodeC = head;
	T item = nodeC->item;
	head = nodeC->next;
	delete nodeC;
	return item;
}

/**
 * Get length of list
*/
template <class T>
int LinkedList<T>::length() {
	Node<T>* nodeC = head;
	int pos = 0;
	while (nodeC != nullptr) {
		nodeC = nodeC->next;
		pos++;
	}
	return pos;
}

/**
 * Print out list
*/
template <class T>
void LinkedList<T>::print() {
    // Iterate through nodes
	Node<T>* nodeC = head;
	while (nodeC != nullptr) {
		cout << "(" << nodeC->item << ")";
		nodeC = nodeC->next;
		if (nodeC != nullptr) {
			cout << " -> ";
		}
	}
	cout << endl;
}

// ==================================
// || Additional commands
// ==================================

/**
 * count the instances of an element in the array
*/
template <class T>
int LinkedList<T>::count(T items) {
	Node<T>* nodeC = head;
	int c = 0;
	while (nodeC != nullptr) {
		if (nodeC->item == items) {
			c++;
		}
		nodeC = nodeC->next;
	}
	return c;
}

/**
 * Remove duplicates
*/
template <class T>
void LinkedList<T>::remove_duplicates() {
	vector<T> values;
	Node<T>* nodeC = head;
	Node<T>* nodePrev = nullptr;
	while (nodeC != nullptr) {
		T value = nodeC->item;
		// Search for current node item in values
		if (find(values.begin(), values.end(), value) != values.end()) {
			if (nodePrev != nullptr) {
				nodePrev->next = nodeC->next;
				// delete the current duplicate node and connect its next node to the previous node
				delete nodeC;
				nodeC = nodePrev->next;
			}
			else {
				head = nodeC->next;
				delete nodeC;
				nodeC = head;
			}
		}
		else {
			values.push_back(nodeC->item);
			nodePrev = nodeC;
			nodeC = nodeC->next;
		}
	}
}

/**
 * Reverse the list
*/
template <class T>
void LinkedList<T>::reverse() {
    Node<T>* nodeL = nullptr;
    Node<T>* nodeC = head;
    Node<T>* nodeR = nullptr;
	// head wil1 end up being the last element so we update tail to it now
	tail = head;
    
    while (nodeC != nullptr) {
        nodeR = nodeC->next;   // store nodeR node
        nodeC->next = nodeL;   // reverse the nodeC node's pointer
        nodeL = nodeC;         // move nodeL to this node
        nodeC = nodeR;         // move to next node
    }
    head = nodeL;  // after the loop, reset the head to the last node in the original list
}



/**
 * Append a list
*/
template <class T>
void LinkedList<T>::append(LinkedList<T> &list) {
    Node<T>* nodeC = list.head;

    while (nodeC != nullptr) {
        this->append(nodeC->item);  // Using the existing append function to add to the end of this list
        nodeC = nodeC->next;
    }
}

template <class T>
void LinkedList<T>::printRecursive(Node<T>* node) {
	if (node == nullptr) {
		cout << endl;
		return;
	}

	cout << "(" << node->item << ")";
	if (node->next != nullptr) {
		cout << " -> ";
	}
	printRecursive(node->next);
}

/**
 * Reverse List Recursively
*/
template <class T>
Node<T>* LinkedList<T>::reverseRecursive(Node<T>* node) {
	// Check if list is empty or only had the head
	if (node == nullptr || node->next == nullptr) {
        head = node;
        return node;
    }

	// Keep going until you reach the last node
    Node<T>* nextNode = reverseRecursive(node->next);

    nextNode->next = node;
    node->next = nullptr;

    return node;
	
}

#endif
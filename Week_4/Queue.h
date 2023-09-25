#ifndef QUEUE_H
#define QUEUE_H
using namespace std;

#include "Deque.h"

template <typename T> class Queue : public Deque<T> { // template class. Type T is a placeholder that's defined at instantiation

    public:
        Queue();                // Base constructor. Sets capacity to 100
        Queue(int capacity);    // Constructor. Accepts an int for capacity 
        void enque(T item);     // Add an item to the queue      
        T deque();              // Remove item from queue

};

#include <iostream>
#include "Queue.h"
using namespace std;

/**
 * Default constructor. Starts with 100 items
*/
template <typename T> 
Queue<T>::Queue() : Deque<T>() {}

/**
 * Constructor that takes a capacity as an argument
*/
template <typename T> 
Queue<T>::Queue(int cap) : Deque<T>(cap){}

/**
 * Add to queue
*/
template <typename T> 
void Queue<T>::enque(T item) {
    Deque<T>::push_back(item);
}

/** 
 * Remove from Queue
*/
template <typename T>
T Queue<T>::deque() {
	return Deque<T>::remove_front();
}


#endif
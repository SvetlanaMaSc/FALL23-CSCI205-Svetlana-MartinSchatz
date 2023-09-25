#ifndef STACK_H
#define STACK_H
using namespace std;

#include "Deque.h"

template <typename T> class Stack : public Deque<T> { // template class. Type T is a placeholder that's defined at instantiation

    public:
        Stack();                // Base constructor. Sets capacity to 100
        Stack(int capacity);    // Constructor. Accepts an int for capacity
        void push(T item);      // Push item to the stack
        T pop();                // Pop item off the stack
        T peek();               // Look at item on top of the stack

};

#include <iostream>
#include "Stack.h"
using namespace std;

/**
 * Default constructor. Starts with 100 items
*/
template <typename T> 
Stack<T>::Stack() : Deque<T>() {}

/**
 * Constructor that takes a capacity as an argument
*/
template <typename T> 
Stack<T>::Stack(int cap) : Deque<T>(cap){}

/**
 * Push an item onto the array
*/
template <typename T>
void Stack<T>::push(T item) {
	Deque<T>::push_back(item);
}

/**
 * Pop item off array
*/
template <typename T>
T Stack<T>::pop() {
	return Deque<T>::remove_back();
}

/**
 * Look at the item at the top of the stack without removing it
*/
template <typename T>
T Stack<T>::peek() {
	return Deque<T>::getArray()[Deque<T>::getBackIndex()];
}

#endif
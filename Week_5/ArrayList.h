#ifndef H_List_ARRAY
#define H_LIST_ARRAY

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
class ArrayList{
	private:
		T* memory_array;   // memory allocation for list elements
		unsigned int size;  // variable to hold the size
		int tail;
		int arraySize;
		void shiftForward(int start, int end);
		void shiftBackward(int start, int end);
		void resize();

	public:
		ArrayList();								// default constructor
		ArrayList(int size);						// constructor with size
		ArrayList(T payload_array[], int size);	// constructor with payload array
		~ArrayList();							// destructor, frees memory

		void insert(T item);				// insert item at beginning of list
		void insert(T item, int position);	// insert item at position
		void append(T item);				// append item to end of list
		T get(int position);				// get item at position, does not remove item
		T remove(int position);				// remove and return item at position
		void removeAll(T item);				// remove all instances of item from list
		void print();						// print list in neat format
		int length();						// return length of list

		int count(T item);					// count instances of item
		void remove_duplicates();
		void reverse();
		void append(ArrayList &list);
		void purge();
};

// ==================================
// || Constructors
// ==================================
template <class T>
ArrayList<T>::ArrayList() {
	// Default size is 10
    memory_array = new T[10];
	tail = 0;
	// This is used to keep track of the length of the entire array, including empty slots 
	arraySize = 10;
}

template <class T>
ArrayList<T>::ArrayList(int capacity) {
    memory_array = new T[capacity];
	tail = 0;
	arraySize = capacity;
}

template <class T>
ArrayList<T>::ArrayList(T payload_array[], int size) {
    memory_array = new T[size + 10];
    this->size = size;
    for (int i = 0; i < size; i++) {
        memory_array[i] = payload_array[i];
    }
}

template <class T>
ArrayList<T>::~ArrayList() {
    delete[] memory_array;
}

// ==================================
// || Helper Functions
// ==================================
/**
 * Shift elements in an array over to the right by one
*/
template <class T>
void ArrayList<T>::shiftForward(int start, int end) {
    for (int i = end; i > start; i--) {
        memory_array[i] = memory_array[i-1];
    }
}

/**
 * Shift elements in an array over to the left by one
*/
template <class T>
void ArrayList<T>::shiftBackward(int start, int end) {
	for (int i = start; i < end; i++) {
		memory_array[i] = memory_array[i+1];
	}
}

/**
 * Resize array
 * 
 * The algorithm is in O(n) complexity as it depends on the array size. Efficiency wise, it increases the array by a relatively small amountand it cleans up the former array to prevent meory leaks.
*/
template <class T>
void ArrayList<T>::resize() {
	// 50 % incease
	int newSize = (arraySize * 1.5);
	// Create new array
	T* newArray = new T[newSize];
	// Add old array
	for (int i = 0; i < tail; i++) {
		newArray[i] = memory_array[i];
	}

	// Free up memory by deleting the old arary
	delete[] memory_array;

	// Set new array to memoryOne_array
	memory_array = newArray;
	// Update size of array
	arraySize = newSize;
}


// ==================================
// || Methods
// ==================================
/** 
 * Insert at the head
*/
template <class T>
void ArrayList<T>::insert(T item) {
	if (tail >= arraySize) {
		resize();
	}
	shiftForward(0, tail);
	memory_array[0] = item;
	tail++;
}

/**
 * Insert at any point in the array
*/
template <class T>
void ArrayList<T>::insert(T item, int position) {
    if (position < 0 || position >= arraySize) {
        // Handle invalid positions, possibly throw an exception or resize
        return;
    }

    if (tail + 1 >= arraySize) {
        resize();
    }
    shiftForward(position, tail);
    memory_array[position] = item;
    tail++;  // Increment tail by one, not the position
}


/**
 * Append to the tail
*/
template <class T>
void ArrayList<T>::append(T item) {
	if (tail - 1 <= arraySize) {
		memory_array[tail] = item;
		tail++;
	}
}

/**
 * Get node at specific postion
*/
template <class T>
T ArrayList<T>::get(int position) {
	return memory_array[position];
}

/**
 * Remove node from array
*/
template <class T>
T ArrayList<T>::remove(int position) {
	// get item
	T item = get(position);
	// Move items after back
	shiftBackward(position, tail - 1);
	tail--;
	return item;
}

/**
 * Get lentgth of list
*/
template <class T>
int ArrayList<T>::length() {
	return tail;
}

/**
 * Print out list
*/
template <class T>
void ArrayList<T>::print() {
    for (int i = 0; i < tail; i++) {
        cout << "[" << memory_array[i] << "] ";
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
int ArrayList<T>::count(T item) {
	int count = 0;
	for (int i = 0; i < tail; i++) {
		T value = memory_array[i];
		if (value == item) {
			count++;
		}
	}

	return count;
}

/**
 * Remove duplicates
 * 
*/
template <class T>
void ArrayList<T>::remove_duplicates() {
	// values that have been collected
	vector<T> values;
	int i = 0;
	while (i < tail) {
		T value = memory_array[i];
		if (find(values.begin(), values.end(), value) != values.end()) {
			remove(i);
			tail--;
		}
		else {
			values.push_back(value);
			i++;
		}
	}
}

/**
 * Reverse the list
*/
template <class T>
void ArrayList<T>::reverse() {
	int t = tail - 1;
	int h = 0;
	for (int i = 0; i < (tail + 1) / 2; i++) {
		T front = memory_array[h];
		T back = memory_array[t];
		memory_array[h] = back;
		memory_array[t] = front;
		h++;
		t--;
	}
}

/**
 * Append a list
*/
template <class T>
void ArrayList<T>::append(ArrayList &list) {
	int listLength = list.arraySize;
	while (tail + listLength > arraySize) {
		resize();
	}
	for (int i = 0; i < listLength; i++) {
		append(list.get(i));
	}
	
}


#endif

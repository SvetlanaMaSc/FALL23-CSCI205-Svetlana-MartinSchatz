#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
using namespace std;

template <typename T> class Deque{	// template class. Type T is a placeholder that's defined at instantiation
	private:
		int size;					// tracks current queue size
		int capacity;				// tracks max queue capacity
		int front_index;			// tracks index of front of queue
		int back_index;				// tracks index of back of queue
		T* array;					// pointer to underlying array

	public:
		Deque();					//Constructs a Deque with default capacity of 100 items
		Deque(int cap);				//Constructs a Deque with given capacity (size of underlying array)
		~Deque();					//Frees dynamic memory
		// Deque(Deque<T>& other);
		void push_front(T item);	//Pushes an item to the front of the deque
		void push_back(T item);		//Pushes an item to the back of the deque
		T remove_front();			//Removes the item at the front of the deque and returns it
		T remove_back();			//Removes the item at the back of the deque and returns it
		bool is_full();				//Returns whether or not the deque is full
		bool is_empty();			//Returns whether or not the deque is empty
		T* getArray();
		int getBackIndex();
		void print();
};

// Creates a Deque with default capacity of 100 items
template <typename T>
Deque<T>::Deque(){
	capacity 	= 100;			// default capacity
	size 		= 0;
	front_index = -1;
	back_index 	= 0; // back index points to last item in array
	array = new T[capacity];	// create dynamic memory for array of template type T
}

// Creates a Deque with given capacity (size of underlying array)
template <typename T>
Deque<T>::Deque(int cap){
	capacity 	= cap;			// set capacity
	size 		= 0;
	front_index = -1;
	back_index 	= 0;	// back index points to last item in array
	// =====================================================
	// || TO DO: Create dynamic memory for the array of T ||
	// =====================================================
	array = new T[capacity];	// create dynamic memory for array of template type T
}

// Frees dynamic memory
template <typename T>
Deque<T>::~Deque(){
	// ==========================================
	// || TO DO #1: De-allocate dynamic memory ||
	// ==========================================
	delete[] array;
}


// Pushes an item to the front of the deque
template <typename T>
void Deque<T>::push_front(T item){
	// ==================================
	// || TO DO #2: Handle wrap around ||
	// ==================================
	if (is_full()) {
		cerr << "Deque is full" << endl;
		return; 
	}			
	else {
		if (front_index == -1) {
			// Initialize the pointers of the empty array to the head and tail, both starting at [0] 
			front_index = 0;
			back_index = 0;
		}
		if (front_index == 0) {
			front_index = capacity - 1;
		}
		else {
			front_index--;
		}
		array[front_index] = item;	// add item to front of array
	}
}

// Pushes an item to the back of the deque
template <typename T>
void Deque<T>::push_back(T item){
	// ==================================
	// || TO DO #3: Handle wrap around ||
	// ==================================
	if (is_full()) {
		cerr << "Deque is full" << endl;
		return;
	}
	else {
		if (front_index == -1) {
			front_index = 0;
			back_index = 0;			
		}
		else if (back_index == capacity - 1) {
			back_index = 0;
		}
		else {
			back_index++;
		}
		array[back_index] = item;	// add item to back of array
	}
}

// Removes the item at the front of the deque and returns it
template <typename T>
T Deque<T>::remove_front(){
	// ==================================
	// || TO DO #4: Handle wrap around ||
	// ==================================
	T temp;
	if (is_empty()) {
		cerr << "Array is empty" << endl;
		temp = array[0];
	}
	else {
		if (front_index == back_index) {
			temp = array[front_index];	// get item at front of array
			front_index = -1;
			back_index = -1;
		}
		else if (front_index == capacity - 1) {
			temp = array[front_index];
			front_index = 0;
		}
		else {
			temp = array[front_index];
			front_index++;
		}
	}
	return temp;					// return item
}

// Removes the item at the back of the deque and returns it
template <typename T>
T Deque<T>::remove_back(){
	// ==================================
	// || TO DO #5: Handle wrap around ||
	// ==================================
	T temp;
	if (is_empty()) {
		cerr << "Array is empty" << endl;
		temp = array[capacity - 1];
	}
	else {
		temp = array[back_index];	// get item at back of array
		if (front_index == back_index) {
			front_index = -1;
			back_index = -1;
		}
		else if (back_index == 0) {
			back_index = capacity - 1;
		}
		else {
			back_index--;
		}
	}
	return temp;					// return item
}

// Returns whether or not the deque is full
template <typename T>
bool Deque<T>::is_full(){
	// return size == capacity;		// if size == capacity, then the deque is full
	return ((front_index == 0 && back_index == capacity - 1)
			|| front_index == back_index + 1);
}

// Returns whether or not the deque is empty
template <typename T>
bool Deque<T>::is_empty(){
	// return size == 0;				// if size == 0, then the deque is empty
	return (front_index == -1);
}

template <typename T>
int Deque<T>::getBackIndex() {
	if (back_index != -1) {
		return back_index;
	}
	else {
		return 0;
	}
}

template <typename T>
T* Deque<T>::getArray() {
	return array;
}

template <typename T>
void Deque<T>::print() {
	cout << endl;
	for (int i = 0; i < capacity; i++) {
		cout << "[" << array[i] << "]" << " ";
	}
	cout << endl;
	cout << "arrr[0]: " << "[" << array[0] << "]" << endl;
	cout << "arr[-1]: " << "[" << array[capacity - 1] << "]" << endl;
	cout << "arr[FI]: " << "[" << array[front_index] << "]" << endl;
	cout << "arr[BI]: " << "[" << array[back_index] << "]" << endl;
	cout << "capacity: " << capacity << endl;
	cout << "back index: " << back_index << endl;
	cout << "front index: "  << front_index << endl;
}

#endif

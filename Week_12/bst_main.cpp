#include <iostream>
#include <ctime>
#include <vector>
#include "AVLBST.hpp"

int main() {
	BinarySearchTree<int> bst;
	AVLBST<int> avl;
	const int SIZE = 10;

	// fill with random numbers
	srand(time(nullptr));
	for (int i = 0; i < SIZE; i++)
		bst.insert(rand() % 90 + 10);

	// degrade BST to O(n) operations with this input
	for (int i = 1; i <= SIZE; i++)
		bst.insert(i);

	// use this data to test remove
	std::vector<int> temp = { 50, 30, 20, 40, 70, 60, 65, 80 };
	for (int i = 0; i < temp.size(); i++)
		bst.insert(temp[i]);
	bst.print();
	
	std::cout << "In-order traversal: ";
	bst.in_order();
	std::cout << "Pre-order traversal: ";
	bst.pre_order();
	std::cout << "Post-order traversal: ";
	bst.post_order();
	
	if (bst.search(60)) std::cout << "Found 60 in the BST." << std::endl;
	else std::cout << "60 not found in the BST." << std::endl;

	// remove an item
	std::cout << "Before removing 50" << std::endl;
	bst.print();
	std::cout << "After removing 50" << std::endl;
	bst.remove(50);
	bst.print();
	return 0;
}
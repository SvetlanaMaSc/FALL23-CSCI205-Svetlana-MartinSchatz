/*
	A Binary Search Tree (BST) is a hierarchical data structure used in computer science to store and organize data efficiently. 
	It is a type of binary tree with the following key characteristics:

	1.	Binary Tree Structure: A BST is a binary tree, meaning that each node has at most two child nodes: a left child and a right child. 
		These child nodes are also BSTs, forming sub-trees within the main tree.

	2.	Ordering Property: The defining feature of a BST is the ordering property. Each node in a BST is associated with a value, 
		and this value is such that for any given node:
		~ All values in the left sub-tree are less than the value of the node.
		~ All values in the right sub-tree are greater than the value of the node.

		This ordering property ensures that the tree is organized in such a way that you can quickly search for, insert, or delete values in logarithmic time.

	3.	No Duplicates: In most BST implementations, duplicate values are not allowed. If a duplicate value is encountered, it can be placed in 
		either the left or right sub-tree, depending on the specific implementation.

	4.	Balanced vs. Unbalanced: BSTs can be balanced or unbalanced. In a balanced BST, the tree is structured such that its height is minimized,
		leading to efficient search, insert, and delete operations. In an unbalanced BST, the height can approach that of a linked list,
		resulting in poor performance for these operations. Techniques such as AVL trees and Red-Black trees are used to ensure that the tree remains balanced.

	5. Traversal: Common ways to traverse a BST include in-order, pre-order, and post-order traversal.
		~ In-order traversal of a BST results in visiting the nodes in ascending order of their values.
		~ Pre-order traversal of a BST results in visiting the root node first, followed by the left and right sub-trees.
		~ Post-order traversal of a BST results in visiting the left and right sub-trees first, followed by the root node.

	BSTs are widely used in various applications, including databases, search algorithms, and data structures like sets and maps. 
	The efficiency of search, insertion, and deletion operations in a BST makes it a valuable tool for managing and organizing data. 
	However, it's important to note that the efficiency of these operations depends on the tree's balance, and unbalanced trees 
	may degrade to linear time complexity for these operations. To maintain balance, self-balancing binary search trees, 
	such as AVL trees and Red-Black trees, are often used.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

// TreeNode class
template <typename T>
class TreeNode {
	public:
		T data;				// node's payload. Custom instances of T should have comparison operators defined
		TreeNode* left;		// pointer to left child
		TreeNode* right;	// pointer to right child

		TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

// BinarySearchTree class
template <typename T>
class BinarySearchTree {
	private:
		TreeNode<T>* root;									// pointer to root node
		int nodeCount;										// number of nodes in the tree

		// helper function with arguments to insert a node recursively
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* insert(TreeNode<T>* node, T key) {
			if (node == nullptr)							// if node is null, create new node
				return new TreeNode<T>(key);				// return new node

			if (key < node->data)							// if key is less than node's data
				node->left = insert(node->left, key);		// recursively insert key into left subtree
			else if (key > node->data)						// if key is greater than node's data
				node->right = insert(node->right, key);		// recursively insert key into right subtree
			nodeCount++;									// increment node count
			return node;									// return node
		}

		// helper function to find the minimum value in a subtree
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* min(TreeNode<T>* node) {
			while (node->left != nullptr)					// while node has a left child
				node = node->left;							// go left
			return node;									// return node
		}

		// helper function to find the maximum value in a subtree
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* max(TreeNode<T>* node) {
			while (node->right != nullptr)					// while node has a right child
				node = node->right;							// go right
			return node;
		}

		// helper function to find the inorder successor of a node
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* remove(TreeNode<T>* node, T key) {							// args: start, key to remove
			if (node == nullptr)		return node;							// key was not found in tree
			if (key < node->data)		node->left  = remove(node->left, key);  // key is smaller than node's data, go left
			else if (key > node->data)	node->right = remove(node->right, key); // key is greater than node's data, go right
			else {
				if (node->left == nullptr && node->right == nullptr) {			// node is a leaf node
					delete node;												// delete node
					return nullptr;												// found the node, remove it
				}else if (node->left == nullptr) {								// node has one child (right child))
					TreeNode<T>* temp = node->right;							// store right child
					delete node;												// delete node
					return temp;												// return right child
				} else if (node->right == nullptr) {							// node has one child (left child)
					TreeNode<T>* temp = node->left;								// store left child
					delete node;												// delete node
					return temp;												// return left child
				}
				// node has two children, get inorder successor
				TreeNode<T>* temp	= min(node->right);							// smallest in right subtree
				node->data			= temp->data;								// copy inorder successor's content to this node (to delete)
				node->right			= remove(node->right, temp->data);			// delete inorder successor
			}
			return node;														// return node (potentially modified)
		}

		// helper function to traverse the tree in order
		// O(n) where n is the number of nodes in the tree
		void inOrderTraversal(TreeNode<T>* node) {
			if (node != nullptr) {					// if node is not null
				inOrderTraversal(node->left);		// traverse left subtree
				std::cout << node->data << " ";		// print node's data
				inOrderTraversal(node->right);		// traverse right subtree
			}
		}

		// helper function to traverse the tree in pre-order
		// O(n) where n is the number of nodes in the tree
		void preOrderTraversal(TreeNode<T>* node) {
			if (node != nullptr) {					// if node is not null
				std::cout << node->data << " ";		// print node's data
				preOrderTraversal(node->left);		// traverse left subtree
				preOrderTraversal(node->right);		// traverse right subtree
			}
		}

		// helper function to traverse the tree in post-order
		// O(n) where n is the number of nodes in the tree
		void postOrderTraversal(TreeNode<T>* node) {
			if (node != nullptr) {					// if node is not null
				postOrderTraversal(node->left);		// traverse left subtree
				postOrderTraversal(node->right);	// traverse right subtree
				std::cout << node->data << " ";		// print node's data
			}
		}

		// just for illustration purposes
		void printTree(TreeNode<T>* root, int level = 0, const std::string& prefix = "", int spacing = 4) {
			if (root) {																	// if root is not null
				if (level == 0) {														// if root is the root node
					std::cout << "Root: " << root->data << std::endl;					// print root node
				} else {																// node is not the root node
					std::string branch = (level % 2 == 1) ? "└─" : "├─";				// determine branch
					std::string spaces(spacing * level - 2, ' ');						// determine spacing
					std::cout << spaces << branch << prefix << root->data << std::endl;	// print node
				}

				if (root->left || root->right) {										// if node has children
					printTree(root->left, level + 1, "L: ", spacing);					// print left child
					printTree(root->right, level + 1, "R: ", spacing);					// print right child
				}
			}
		}
		// private recursive helper function to destroy the tree
		void destroyTree(TreeNode<T>* node) {
			if (node != nullptr) {				// if node is not null
				destroyTree(node->left);		// destroy left subtree
				destroyTree(node->right);		// destroy right subtree
				delete node;					// delete node
			}
		}

		// Helper method to perform in-order traversal and fill the vector
		void inOrderHelper(TreeNode<T>* node, std::vector<T>& vec) {
			if (node != nullptr) {
				inOrderHelper(node->left, vec);   // Traverse left subtree
				vec.push_back(node->data);        // Visit node
				inOrderHelper(node->right, vec);  // Traverse right subtree
			}
		}

		// Helper function to recursively find the closest value
		T closestHelper(TreeNode<T>* node, T target, T closest) {
        	if (node == nullptr) {
				return closest; // Return the closest found so far if we've reached a leaf node
			}

			// If the current node is closer to the target than the previous closest, update closest
			if (std::abs(target - closest) > std::abs(target - node->data)) {
				closest = node->data;
			}

			// Recursively search the left or right subtree depending on the target's relation to the current node
			if (target < node->data) {
				return closestHelper(node->left, target, closest);
			} else if (target > node->data) {
				return closestHelper(node->right, target, closest);
			} else {
				// If the target is equal to the current node, we've found the closest value
				return node->data;
			}
		}

		// Helper function for is_valid, recursively checks the BST property
		bool is_valid_helper(TreeNode<T>* node, TreeNode<T>*& prev) {
			if (node == nullptr) return true; // An empty tree is a valid BST

			// Check the left subtree
			if (!is_valid_helper(node->left, prev)) return false;

			// Ensure current node's value is greater than the previous node's value
			if (prev != nullptr && node->data <= prev->data) return false;

			// Update prev to current node before checking right subtree
			prev = node;

			// Check the right subtree
			return is_valid_helper(node->right, prev);
   		}

		// Helper function to insert nodes recursively to form a balanced BST
		TreeNode<T>* sortedArrayToBST(std::vector<T>& arr, int start, int end) {
			// Base case
			if (start > end) return nullptr;

			// Get the middle element and make it root
			int mid = (start + end) / 2;
			TreeNode<T>* node = new TreeNode<T>(arr[mid]);

			// Recursively construct the left subtree and make it left child of root
			node->left = sortedArrayToBST(arr, start, mid - 1);

			// Recursively construct the right subtree and make it right child of root
			node->right = sortedArrayToBST(arr, mid + 1, end);

			return node;
		}

		// Helper function to recursively find the k-th smallest node
		void find_kth_smallest_helper(TreeNode<T>* node, int k, int& count, TreeNode<T>*& result) {
			if (node == nullptr || result != nullptr) return;

			// Traverse the left subtree
			find_kth_smallest_helper(node->left, k, count, result);

			// Process the current node
			count++; // Increment count of nodes visited
			if (count == k) {
				result = node; // Found k-th smallest
				return; // Stop the traversal
			}

			// Traverse the right subtree
			find_kth_smallest_helper(node->right, k, count, result);
		}

	public:
		// no-arg constructor
		BinarySearchTree() : root(nullptr) {}
		
		// destructor
		~BinarySearchTree() {
			destroyTree(root);	// call private recursive helper destroyTree
		}

		// public insert with T argument
		void insert(T key) {
			root = insert(root, key);	// call private recursive helper insert
		}

		// public remove with T argument
		void remove(T key) {
			root = remove(root, key);	// call private recursive helper remove
		}

		// public search with T argument
		// O(log n) where n is the number of nodes in the tree
		bool search(T key) {
			TreeNode<T>* current = root;									// start at root
			while (current != nullptr) {									// while current is not null
				if (key == current->data)		return true;				// found key
				else if (key < current->data)	current = current->left;	// key is less than current, go left
				else							current = current->right;	// key is greater than current, go right
			}
			return false;													// key not found
		}

		// public in-order traversal, no arguments
		void in_order() {
			inOrderTraversal(root);							// call private recursive helper
			std::cout << std::endl;							// new line
		}

		// public pre-order traversal, no arguments
		void pre_order() {
			preOrderTraversal(root);						// call private recursive helper
			std::cout << std::endl;
		}

		// public post-order traversal, no arguments
		void post_order() {
			postOrderTraversal(root);						// call private recursive helper
			std::cout << std::endl;
		}
		
		// public print with no arguments
		void print() {
			printTree(root);								// call private recursive helper
		}

		// public min with no arguments
		T min() {
			return min(root)->data;							// call private recursive helper min
		}

		// public max with no arguments
		T max() {
			return max(root)->data;							// call private recursive helper max
		}

		// Method to flatten the tree into a sorted vector
		std::vector<T> flatten() {
			std::vector<T> sortedElements;
			inOrderHelper(root, sortedElements);
			return sortedElements;
		}
		
		// Function to find the value closest to the target
		T closest(T target) {
			return closestHelper(root, target, root->data); // Start with the root's value as the closest
		}
		
		// Function to validate the BST
	    bool is_valid() {
			TreeNode<T>* prev = nullptr;
			return is_valid_helper(root, prev);
		}

		// Function to create a balanced BST from an unsorted vector
		void generate(std::vector<T>& arr) {
			// Sort the array - O(n log n)
			std::sort(arr.begin(), arr.end());

			// Create the balanced BST - O(n)
			root = sortedArrayToBST(arr, 0, arr.size() - 1);
		}

		// Function to find the k-th smallest element in the BST
		T find_kth_smallest(int k) {
			int count = 0; // Counter for the number of nodes processed
			TreeNode<T>* result = nullptr; // To store the k-th smallest node
			find_kth_smallest_helper(root, k, count, result);
			if (result == nullptr) {
				throw std::runtime_error("Not enough elements in the BST.");
			}
			return result->data;
		}

		// Method to compute the height of a node
		int height(TreeNode<T>* node) {
			// A null node has height -1, which indicates there's no node present.
			if (node == nullptr) {
				return -1;
			}

			// Compute the height of the left and right subtrees and take the max.
			int leftHeight = height(node->left);
			int rightHeight = height(node->right);

			// Add 1 for the current node and return.
			return 1 + std::max(leftHeight, rightHeight);
		}

		    // Method to compute the balance factor of a node
		int balance_factor(TreeNode<T>* node) {
			if (node == nullptr) {
				// An empty node is perfectly balanced.
				return 0;
			}

			// Calculate the height of the left subtree.
			int leftHeight = height(node->left);

			// Calculate the height of the right subtree.
			int rightHeight = height(node->right);

			// The balance factor is the difference between the heights.
			return leftHeight - rightHeight;
		}

};

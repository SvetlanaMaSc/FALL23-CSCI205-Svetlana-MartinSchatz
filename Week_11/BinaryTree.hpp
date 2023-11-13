#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template <typename T>
class BinaryTree {

	private:
		T* key;											// node's payload
		BinaryTree<T> *leftChild;						// pointer to left child
		BinaryTree<T> *rightChild;						// pointer to right child
		
		// just for illustration purposes
		void printTree(BinaryTree<T>* root, int level = 0, const string& prefix = "", int spacing = 4) {
			if (root) {																	// if root is not null
				if (level == 0) {														// if root is the root node
					std::cout << "Root: " << root->key << std::endl;					// print root node
				} else {																// node is not the root node
					string branch = (level % 2 == 1) ? "└─" : "├─";				// determine branch
					string spaces(spacing * level - 2, ' ');						// determine spacing
					std::cout << spaces << branch << prefix << root->key << std::endl;	// print node
				}

				if (root->leftChild || root->rightChild) {									// if node has children
					printTree(root->leftChild, level + 1, "L: ", spacing);					// print left child
					printTree(root->rightChild, level + 1, "R: ", spacing);					// print right child
				}
			}

		}

	public:
		BinaryTree(T* rootObj) : key(rootObj), leftChild(nullptr), rightChild(nullptr) {										// constructor
			this->key = rootObj;									// set root's payload
			this->leftChild = NULL;									// set left child to null
			this->rightChild = NULL;								// set right child to null
		}

		~BinaryTree(){												// destructor
			if (this->leftChild != NULL)							// if left child is not null
				delete this->leftChild;								// delete left child
			if (this->rightChild != NULL)							// if right child is not null
				delete this->rightChild;							// delete right child
		}

		void insertLeft(T newNode){									// insert left child
			if (this->leftChild == NULL)							// if left child is null
				this->leftChild = new BinaryTree<T>(newNode);		// create new node
			else {													// left child is not null
				BinaryTree<T> *t = new BinaryTree<T>(newNode);		// create new node
				t->leftChild = this->leftChild;						// set new node's left child to current left child
				this->leftChild = t;								// set current left child to new node
			}
		}

		void insertRight(T newNode){								// insert right child
			if (this->rightChild == NULL)							// if right child is null
				this->rightChild = new BinaryTree<T>(newNode);		// create new node
			else {													// right child is not null
				BinaryTree<T> *t = new BinaryTree<T>(newNode);		// create new node
				t->rightChild = this->rightChild;					// set new node's right child to current right child
				this->rightChild = t;								// set current right child to new node
			}
		}

		BinaryTree<T> *getRightChild(){								// get right child
			return this->rightChild;								// return right child
		}

		BinaryTree<T> *getLeftChild(){								// get left child
			return this->leftChild;									// return left child
		}

		void setRootVal(T obj){										// set root's payload
			this->key = obj;										// set root's payload
		}

		T* getRootVal(){												// get root's payload
			return this->key;										// return root's payload
		}

		void preorder(){											// preorder traversal
			std::cout << this->key << " ";							// print root
			if (this->leftChild != NULL)							// if left child is not null
				this->leftChild->preorder();						// preorder left child
			if (this->rightChild != NULL)							// if right child is not null
				this->rightChild->preorder();						// preorder right child
		}

		void inorder(){												// inorder traversal
			if (this->leftChild != NULL)							// if left child is not null
				this->leftChild->inorder();							// inorder left child
			std::cout << this->key << " ";							// print root
			if (this->rightChild != NULL)							// if right child is not null
				this->rightChild->inorder();						// inorder right child
		}

		void postorder(){											// postorder traversal
			if (this->leftChild != NULL)							// if left child is not null
				this->leftChild->postorder();						// postorder left child
			if (this->rightChild != NULL)							// if right child is not null
				this->rightChild->postorder();						// postorder right child
			std::cout << this->key << " ";							// print root
		}

		void printTree(){
			printTree(this);
		}

};
#endif


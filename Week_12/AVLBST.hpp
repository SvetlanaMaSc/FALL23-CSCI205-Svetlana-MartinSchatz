#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "BinarySearchTree.hpp"

template <typename T>
class AVLBST : public BinarySearchTree<T> {

    public:
        void _put(int key, string val, TreeNode *currentNode){
            if (key < currentNode->key){
                if (currentNode->hasLeftChild()){
                    this->_put(key, val, currentNode->leftChild);
                }
                else{
                    currentNode->leftChild = new TreeNode(key, val, currentNode);
                    this->updateBalance(currentNode->leftChild);
                }
            }
            else{
                if (currentNode->hasRightChild()){
                    this->_put(key, val, currentNode->rightChild);
                }
                else{
                    currentNode->rightChild = new TreeNode(key, val, currentNode);
                    this->updateBalance(currentNode->rightChild);
                }
            }
        }

        int updateBalance(TreeNode *node){
            if (node->balanceFactor > 1 || node->balanceFactor < -1){
                this->rebalance(node);
                return 0;
            }
            if (node->parent != NULL){
                if (node->isLeftChild()){
                    node->parent->balanceFactor += 1;
                }
                else if (node->isRightChild()){
                    node->parent->balanceFactor -= 1;
                }
                if (node->parent->balanceFactor != 0){
                    this->updateBalance(node->parent);
                }
            }
        }

        void rotateLeft(TreeNode *rotRoot){
            TreeNode *newRoot = rotRoot->rightChild;
            rotRoot->rightChild = newRoot->leftChild;
            if (newRoot->leftChild != NULL){
                newRoot->leftChild->parent = rotRoot;
            }
            newRoot->parent = rotRoot->parent;
            if (rotRoot->isRoot()){
                this->root = newRoot;
            }
            else{
                if (rotRoot->isLeftChild()){
                    rotRoot->parent->leftChild = newRoot;
                }
                else{
                    rotRoot->parent->rightChild = newRoot;
                }
            }
            newRoot->leftChild = rotRoot;
            rotRoot->parent = newRoot;
            rotRoot->balanceFactor = rotRoot->balanceFactor + 1 - min(newRoot->balanceFactor, 0);
            newRoot->balanceFactor = newRoot->balanceFactor + 1 + max(rotRoot->balanceFactor, 0);
        }

        void rebalance(TreeNode *node){
            if (node->balanceFactor < 0){
                if (node->rightChild->balanceFactor > 0){
                    this->rotateRight(node->rightChild);
                    this->rotateLeft(node);
                }
                else{
                    this->rotateLeft(node);
                }
            }
            else if (node->balanceFactor > 0){
                if (node->leftChild->balanceFactor < 0){
                    this->rotateLeft(node->leftChild);
                    this->rotateRight(node);
                }
                else {
                    this->rotateRight(node);
                }
            }
        }

        // Helper function to find the minimum value node
        TreeNode* findMin(TreeNode* node) {
            TreeNode* current = node;
            while (current->leftChild != NULL) {
                current = current->leftChild;
            }
            return current;
        }

        // Helper function to delete a node
        TreeNode* deleteNode(TreeNode* root, int key) {
            if (root == NULL)
                return root;

            // If the key to be deleted is smaller than the root's key,
            // then it lies in left subtree
            if (key < root->key)
                root->leftChild = deleteNode(root->leftChild, key);

            // If the key to be deleted is greater than the root's key,
            // then it lies in right subtree
            else if (key > root->key)
                root->rightChild = deleteNode(root->rightChild, key);

            // if key is same as root's key, then this is the node to be deleted
            else {
                // node with only one child or no child
                if ((root->leftChild == NULL) || (root->rightChild == NULL)) {
                    TreeNode* temp = root->leftChild ? root->leftChild : root->rightChild;

                    // No child case
                    if (temp == NULL) {
                        temp = root;
                        root = NULL;
                    } else // One child case
                        *root = *temp; // Copy the contents of the non-empty child
                    
                    delete temp;
                } else {
                    // node with two children: Get the inorder successor (smallest
                    // in the right subtree)
                    TreeNode* temp = findMin(root->rightChild);

                    // Copy the inorder successor's data to this node
                    root->key = temp->key;
                    root->value = temp->value;

                    // Delete the inorder successor
                    root->rightChild = deleteNode(root->rightChild, temp->key);
                }
            }

            // If the tree had only one node then return
            if (root == NULL)
                return root;

            // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
            root->height = 1 + max(height(root->leftChild), height(root->rightChild));

            // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
            // this node became unbalanced)
            int balance = getBalance(root);

            // If this node becomes unbalanced, then there are 4 cases

            // Left Left Case
            if (balance > 1 && getBalance(root->leftChild) >= 0)
                return rotateRight(root);

            // Left Right Case
            if (balance > 1 && getBalance(root->leftChild) < 0) {
                root->leftChild = rotateLeft(root->leftChild);
                return rotateRight(root);
            }

            // Right Right Case
            if (balance < -1 && getBalance(root->rightChild) <= 0)
                return rotateLeft(root);

            // Right Left Case
            if (balance < -1 && getBalance(root->rightChild) > 0) {
                root->rightChild = rotateRight(root->rightChild);
                return rotateLeft(root);
            }

            return root;
        }

        // Helper function to get the height of the tree
        int height(TreeNode *node) {
            if (node == NULL)
                return 0;
            return 1 + max(height(node->leftChild), height(node->rightChild));
        }

        // Helper function to get the balance factor of the node
        int getBalance(TreeNode *node) {
            if (node == NULL)
                return 0;
            return height(node->leftChild) - height(node->rightChild);
        }

        // Function to check if the tree is balanced at every node
        bool is_balanced(TreeNode *node) {
            if (node == NULL)
                return true; // A null tree is balanced

            int balanceFactor = getBalance(node);

            // Check if the current node is balanced and recursively check if the left and right subtrees are balanced
            return abs(balanceFactor) <= 1 && is_balanced(node->leftChild) && is_balanced(node->rightChild);
        }

        // Public function to be called on the tree
        bool isBalanced() {
            return is_balanced(this->root); // Assuming 'root' is the root node of the AVL tree
        }


};


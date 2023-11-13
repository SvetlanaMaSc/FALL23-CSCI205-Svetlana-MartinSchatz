#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <iostream>
#include <string>
#include "ClosedHashTable.hpp"
#include "BinaryTree.hpp"
#include "PriorityQueue.hpp"
using namespace std;

/**
 * Huffman node
*/
struct HuffmanNode {
    string item;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(string i, int freq) 
        : item(i), frequency(freq), left(nullptr), right(nullptr) {}

    // Constructor for internal nodes
    HuffmanNode(int freq, HuffmanNode* lChild, HuffmanNode* rChild) 
        : item(""), frequency(freq), left(lChild), right(rChild) {}
};

class Huffman {
    private:

    public:
        ClosedHashTable<int> histogram(string inputString) {
            // 26 for each letter in the alphabet
            ClosedHashTable<int> freqTable(26);
            for (size_t i = 0; i < inputString.length(); i++) {
                char ch = inputString.at(i);
                string letter;
                letter += ch;
                // check if in map
                if (freqTable.contains(letter)) {
                    int freq = freqTable.get(letter);
                    freq++;
                    freqTable.put(letter, freq);
                }
                // add to map
                else {
                    freqTable.put(letter, 1);
                }
            }

            return freqTable;
        }

        BinaryTree<HuffmanNode>* build_tree(ClosedHashTable<int> histogram) {
            // create leaf nodes
            PriorityQueue<HuffmanNode*> queue;
            string letters = "abcdefghijklmnopqrstuvwxyz";
            // add to priority queue
            for (int i = 0; i < 26; i++) {
                // ClosedHashTable<int>::HashNode node = histogram.getTable()[i];
                char ch = letters.at(i);
                string letter;
                letter += ch;
                if (histogram.contains(letter)){
                    HuffmanNode* node = new HuffmanNode(letter, histogram[letter]);
                    queue.insert(node);
                }
            }
            // build tree
            while (queue.getSize() > 1) {
                HuffmanNode* left = queue.extractMin();
                HuffmanNode* right = queue.extractMin();

                int combinedFrequency = left->frequency + right->frequency;
                HuffmanNode* internalNode = new HuffmanNode(combinedFrequency, left, right);

                queue.insert(internalNode);
            }

            HuffmanNode* root = queue.extractMin();
            BinaryTree<HuffmanNode>* tree = new BinaryTree<HuffmanNode>(root);

            return tree;
        }

        void generateHuffmanCodes(HuffmanNode* node, string code, ClosedHashTable<string>& hmcodes) {
            if (node == nullptr) return;

            // When a leaf node is reached
            if (node->left == nullptr && node->right == nullptr) {
                hmcodes.put(node->item, code);
                return;
            }

            // Traverse left
            generateHuffmanCodes(node->left, code + "0", hmcodes);

            // Traverse right
            generateHuffmanCodes(node->right, code + "1", hmcodes);
        }

        string compress(string inputString) {
            ClosedHashTable<int> freqs = histogram(inputString);
            BinaryTree<HuffmanNode>* tree = build_tree(freqs);
            ClosedHashTable<string> hmcodes(26);

            HuffmanNode* root = tree->getRootVal();
            generateHuffmanCodes(root, "", hmcodes);

            // Your code for compression using the hmcodes hash table...
            string compressedString;
            for (auto ch : inputString) {
                string letter(1, ch); // Convert char to string to use as a key in hmcodes
                if (hmcodes.contains(letter)) {
                    compressedString += hmcodes.get(letter);
                } 
                else {
                    cerr << "Error: Character " << ch << " not found in Huffman codes table." << endl;
                    // Handle the error appropriately, perhaps by returning an empty string or throwing an exception
                    delete tree; // Don't forget to free the memory
                    return "";
                }
            }

            delete tree; // Don't forget to free the memory
            return compressedString;
        }

        string inflate(string encodedString, BinaryTree<HuffmanNode> huffmanTree) {
            string originalString;
            HuffmanNode* currentNode = huffmanTree.getRootVal();

            for (char bit : encodedString) {
                if (bit == '0') {
                    currentNode = currentNode->left;
                } else { // bit is '1'
                    currentNode = currentNode->right;
                }

                if (currentNode->left == nullptr && currentNode->right == nullptr) {
                    originalString += currentNode->item;
                    currentNode = huffmanTree.getRootVal();
                }
            }

            return originalString;
        }
};
#endif

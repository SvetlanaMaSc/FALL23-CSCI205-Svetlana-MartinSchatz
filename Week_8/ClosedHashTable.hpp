#ifndef Closed_HASH_TABLE_HPP
#define Closed_HASH_TABLE_HPP

#include <iostream>
#include <string>
#include <cmath>
#include "LinkedList.hpp"	// Use YOUR LinkedList class to implement the buckets

template<typename V>
class ClosedHashTable {
	private:
		int comparisons = 0;
		// Each element in the hash table is a HashNode
		// Each HashNode contains a key-value pair
		// The key is a string, and the value is of type V
		// The key is also stored along with the value in the HashNode. Why?
		// Why do we not need to track nodes as deleted?
			/**
			 * ANSWER:
			 * 
			 * Because we aren't going to skip a slot if there's something there; we add to it. So it's never actually deleted.
			*/
		struct HashNode {
			std::string key;
			V value;
			HashNode() : key(""), value() {} // For an empty string key and default-constructed value
			HashNode(const std::string& k, const V& v) : key(k), value(v){}
			// overload the == operator so we can easily compare HashNodes
			// This is for linked list comparisons. Why do we need this?
			/**
			 * ANSWER:
			 * 
			 * If an element already exists in the list then there's no reason to add it again
			*/
			bool operator==(const HashNode& rhs) {return key == rhs.key;}
			// overload the << operator so we can easily print HashNodes
			friend std::ostream& operator<<(std::ostream& os, const HashNode& node) {
				os << node.key << ": " << node.value;
				// comparisons++;
				return os;
			}
		};

		// The Closed hash tables are collections of lists of HashNodes
		LinkedList<HashNode>* table;	// dynamically allocated array of LinkedLists
		int size;						// number of key-value pairs in the hash table
		int capacity;					// number of slots in the hash table

		// helper function to compute hash value
		int hash_div(std::string key, int prime) {
			// You will be experimenting here with various hashing approaches
			// You will be asked to report on your findings
			// Feel free to create separate functions for each hash implementation
			int hash = 0;
			int m = prime;
			for (std::string::size_type i = 0; i < key.length(); i++) {
				if (i % 2 != 0) {
					hash += abs(static_cast<int>(key[i])) % m;
				}
			}
			return hash % m;
		}

		/**
		 * Midsquare Method
		*/
		int hash_midsquare(std::string key, int limit) {
			int numValue = 0;
			for(char c : key) {
				numValue += static_cast<int>(c);
			}
			int squared = pow(numValue, 2);
			
			// Count digits of squared
			int digits = 0;
			int temp = squared;
			while (temp) {
				digits++;
				temp /= 10;
			}

			// Error handling if there aren't enough digits to extract middle three
			if (digits < 5) {
				return squared % limit;
			}

			// Extract the middle three digits
			int offset = (digits - 3) / 2;
			int divisor = pow(10, offset);
			int hash = (squared / divisor) % 1000;

			return hash % limit;
		}

		/**
		 * Digit Analysis
		 * 
		 * TODO: analysis will be done somewhere else
		*/
		int hash_digit(std::string key, int limit) {
			int numValue = 0;
			for(char c : key) {
				numValue += static_cast<int>(c);
			}
			
			int digit3 = (numValue / 10000) % 10; // Extract the 5th digit from the right
			int digit4 = (numValue / 1000) % 10;  // Extract the 4th digit from the right
			int digit5 = (numValue / 100) % 10;   // Extract the 3rd digit from the right
			int digit6 = (numValue / 10) % 10;    // Extract the 2nd digit from the right

			// Form the hash by reversing the order of the extracted digits
			int hash = digit6 * 1000 + digit5 * 100 + digit4 * 10 + digit3;

			return hash % limit;
		}

		/**
		 * Length Dependence
		*/
		int hash_length(std::string key, int limit) {
			int start = key[0];
			int end = key[key.length() - 1];
			int hash = start + end + (key.length() << 4);
			hash /= limit;
			hash %= limit;
			return hash;
		}

		// TODO: detrermine uniforminity

		// helper function to determine load factor
		float loadFactor() {
			// You will be experimenting here with varous load factors
			// You will be asked to report on your findings
			float load = static_cast<float>(size) / capacity;
			return load;
		}

		// helper function to determine if we should resize
		bool should_resize(float threshold) {
			return (loadFactor() >= threshold);
		}

		void resize() {
			// TODO
			// resize capacity to 50% larger, then find next prime number
			// rehash and put all key-value pairs. Why is this necessary?
			// clean up memory from old table
			int newSize = capacity + (capacity / 2);
			int newPrime = find_next_prime(newSize);
			int newHash = 0;
			LinkedList<HashNode>* newTable = new LinkedList<HashNode>[newPrime];
			for (int i = 0; i < capacity; i++) {
				// iterate through array
				// check if bucket contains a list
				if (table[i].length() != 0) {
					// can safely grab key
					string tkey = table[i].getHead()->item.key;
					newHash = hash_midsquare(tkey, newPrime);
					Node<HashNode>* node = table[i].getHead();
					while (node != nullptr) {
						newTable[newHash].append(node->item);
						node = node->next;
						if (node != nullptr) {
							newHash = hash_midsquare(node->item.key, newPrime);
						}
					}

				}

			}

			delete[] table;
			table = newTable;
			capacity = newPrime;
		}

		// helper function to determine if a number is prime
		bool is_prime(int n) {
			if (n <= 1) return false;
			if (n <= 3) return true;
			if (n % 2 == 0 || n % 3 == 0) return false;
			for (int i = 5; i * i <= n; i = i + 6)
				if (n % i == 0 || n % (i + 2) == 0)
					return false;
			return true;
		}


		// helper function to find the next prime number
		int find_next_prime(int n) {
			// Check if n is even
			if (n % 2 == 0) n++;
			// Keep iterating the number until you reach a prime
			while (is_prime(n) == false) {
				// while loop is safe because you will find a prime umb
				n += 2;
			}
			return n;
		}

	public:
		ClosedHashTable(int capacity) : 
					size(0), 
					capacity(capacity)		{
						table = new LinkedList<HashNode>[capacity];
					}	// constructor
		~ClosedHashTable() 					{
			delete[] table;
		}	// destructor

		void put(const std::string& key, const V& value){
			int hash = hash_midsquare(key, capacity);
			// check for resizing
			if (should_resize(.10)) {
				resize();
				hash = hash_midsquare(key, capacity);
			}
			HashNode node(key, value);
			table[hash].append(node);
			size++;
		}	// insert key-value pair

		V get(const std::string& key) 			{
			int hash = hash_midsquare(key, capacity);
			Node<HashNode>* node = table[hash].getHead();
			int j = 0;
			while (node != nullptr) {
				if (node->item.key == key) {
					return node->item.value;
				}
				node = node->next;
				j++;
				comparisons++;
			}

			throw std::out_of_range("Key not found");
		}	// get value associated with key

		bool remove(const std::string& key)		{
			int hash = hash_midsquare(key, capacity);
			Node<HashNode>* node = table[hash].getHead();
			int j = 0;
			while (node != nullptr) {
				if (node->item.key == key) {
					table[hash].remove(j);
					return true;
				}
				node = node->next;
				j++;
				comparisons++;
			}
			return false;
		}	// remove key-value pair from hash table

		bool contains(const std::string& key)		{
			int hash = hash_midsquare(key, capacity);
			// check if linked list is empty
			int i = 0;
			while (i < capacity) {
				if (table[hash].length() > 0) {
					Node<HashNode>* node = table[hash].getHead();
					while (node != nullptr) {
						if (node->item.key == key) {
							return true;
						}
						node = node->next;
						comparisons++;
					}
				}
				hash = (hash + 1) % capacity;
				i++;
			}
			return false;
		}	// check if key is in the hash table

		V& operator[](std::string& key)	{
			return get(key);
		}	// overload the [] operator to access elements in hash table
		
		int arrSize()	{return size;}			// return the number of key-value pairs in the hash table
		bool empty(){return size == 0;}		// check if the hash table is empty


		int getComparisons() {
			int comps = comparisons;
			comparisons = 0;
			return comps;
		}

		// print the contents of the hash table
		// In order to use this your LinkedList class must have a print() and size() function
		void print() {
			for (int i = 0; i < capacity; i++) {
				std::cout << "table[" << i << "]: ";
				if (table[i].length() == 0) std::cout << "EMPTY" << std::endl; // is slot empty? 
				else table[i].print();		// you'll need to implement the print() function for LinkedList
			}
		}
};
#endif
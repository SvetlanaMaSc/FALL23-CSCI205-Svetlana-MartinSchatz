#ifndef Open_HASH_TABLE_HPP
#define Open_HASH_TABLE_HPP

#include <string>
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

template<typename V>
class OpenHashTable{
	private:
		// Each element in the hash table is a HashNode
		// Each HashNode contains a key-value pair and a flag to indicate if it is deleted
		// The key is a string, and the value is of type V
		// TODO:
		// If a HashNode is deleted, it should be skipped during searching. Why?
		// The key is also stored along with the value in the HashNode. Why?
		struct HashNode {
			std::string key;
			V value;
			bool deleted;
			HashNode() : key(""), value(V()), deleted(false) {}
			HashNode(std::string k, V v) : key(k), value(v), deleted(false) {}
		};

		// So that you can focus on the details of hash table implementation, we will
		// implement the hash table using a fixed size array instead of a vector
		// this will allow you to focus on the details of resizing
		HashNode* table;	// dynamically allocated array of HashNodes
		int size;			// number of key-value pairs in the hash table
		int capacity;		// number of slots in the hash table
		int comparisons = 0;

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
		int hash_length(std::string key) {
			int start = key[0];
			int end = key[key.length() - 1];
			int hash = start + end + (key.length() << 4);
			return hash / capacity;
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

		// helper function to resize the table
		void resize() {
			// resize capacity to 50% larger, then find next prime number
			// rehash and put all key-value pairs. Why is this necessary?
			/**
			 * ANSWER:
			 * 
			 * Uniform distribution
			*/
			int newSize = capacity + (capacity / 2);
			int newPrime = find_next_prime(newSize);
			int newHash = 0;
			HashNode* newTable = new HashNode[newPrime];
			for (int i = 0; i < capacity; i++) {
				if (table[i].key != "" && table[i].deleted == false) {
					newHash = hash_midsquare(table[i].key, newPrime);
					newHash = newHash % newPrime;
					while (newTable[newHash].key != "" && newTable[newHash].deleted == false) {
						// iterate through table until we find an open slot
						newHash = (newHash + 1) % newPrime; // % capacity has us wrap around to 0 when we hit capacity
					}
					newTable[newHash] = table[i];
				}

			}

			delete[] table;
			table = newTable;
			capacity = newPrime;
			// clean up memory from old table
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

		// helper function to put key-value pairs into the hash table using linear probing
		void put_with_linear_probe(const std::string& key, const V& value, int threshold)	{
			// check for collision
			int hash = hash_midsquare(key, capacity);

			// check for resizing
			if (should_resize(threshold)) {
				resize();
				hash = hash_midsquare(key, capacity);
			}

			while (table[hash].key != "" && table[hash].deleted == false) {
				// iterate through table until we find an open slot
				hash = (hash + 1) % capacity; // % capacity has us wrap around to 0 when we hit capacity
			}

			table[hash] = HashNode(key, value);
			size++;
		}

		// helper function to put key-value pairs into the hash table using quadratic probing
		void put_with_quadratic_probe(const std::string& key, const V& value, int threshold){
			int hash = hash_midsquare(key, capacity);
			
			// check for resizing
			if (should_resize(threshold)) {
				resize();
				hash = hash_midsquare(key, capacity);
			}

			int i = 1;
			while (table[hash].key != "" && table[hash].deleted == false && i <= capacity) {
				// iterate through table until we find an open slot
				hash = (int) (hash + pow(i, 2)) % capacity; // % capacity has us wrap around to 0 when we hit capacity
				i++;
			}

			table[hash] = HashNode(key, value);
			size++;
		}

	public:
		OpenHashTable(int capacity) : 
						size(0), 
						capacity(capacity)	{
							table = new HashNode[capacity];
							for (int i = 0; i < capacity; i++) {
								table[i] = HashNode();
							}
						}	// constructor
		~OpenHashTable()					{
			delete[] table;
		}	// destructor

		void put(const std::string& key, const V& value){
			// linear probe
			put_with_linear_probe(key, value, .10);

			// quadratic probe
			// put_with_quadratic_probe(key, value);
		}	// insert key-value pair into the hash table using a put-helper
		bool remove(const std::string& key)		{
			int hash = hash_midsquare(key, capacity);
			
			int i = 0;
			// iterate through table looking for 
			while (i < capacity) {
				comparisons++;
				if (table[hash].key == key && !table[hash].deleted) {
					table[hash].deleted = true;
					return true;
				}

				// Move to the next slot and wrap around if at the end
				hash = (hash + 1) % capacity;
				i++;
			}
			return false;
		}	// remove key-value pair from the hash table
		V get(const std::string& key) {
			int hash = hash_midsquare(key, capacity);
			int i = 0;

			while (i < capacity) {
				comparisons++;
				if (table[hash].key == key && !table[hash].deleted) {
					return table[hash].value;
				}

				// Move to the next slot and wrap around if at the end
				hash = (hash + 1) % capacity;
				i++;
			}

			throw std::runtime_error("Key not found.");
		}
		bool contains(const std::string& key)		{
			int hash = hash_midsquare(key, capacity);
			
			int i = 0;
			while (i < capacity) {
				comparisons++;
				if (table[hash].key == key && !table[hash].deleted) {
					return true;
				}

				// Move to the next slot and wrap around if at the end
				hash = (hash + 1) % capacity;
				i++;
			}

			return false;
		}	// check if key is in the hash table
		V& operator[](const std::string& key)	{
			return get(key);
		}	// overload the [] operator to access elements in hash table

		int arrSize()	{return size;}			// return the number of key-value pairs in the hash table
		bool empty(){return size == 0;}		// check if the hash table is empty

		int getComparisons() {
			int comps = comparisons;
			comparisons = 0;
			return comps;
		}

		// print out all the key-value pairs in the hash table
		// use this function to help you debug your code
		void print() {
			for (int i = 0; i < capacity; i++) {
				std::cout << "table[ ";
				if (table[i].deleted)
					std::cout << i << " ]\t= DELETED" << std::endl; 
				else if (table[i].key != "")
					std::cout << table[i].key << " ]\t= " << table[i].value << std::endl;
				else 
				 	std::cout << i << " ]\t= EMPTY" << std::endl;
			}
		}
	};

#endif

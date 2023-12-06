#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <map>
#include <iostream>

template <class T>
class Vertex {
	private:
		int id;									// vertex key
		std::map<int, int> connectedTo;			// list of neighbors ids and edge weights
		T payload;								// add payload here
		bool visited;

	public:
		Vertex() { this->id = 0; }				// default constructor

		Vertex(int key, T pl) {					// constructor with key and payload
			this->id 	  = key;				// set key
			this->payload = pl;					// set payload
		}

		Vertex(const Vertex&) = delete;			// Delete copy constructor

		T getPayload(){ return this->payload; }	// get payload

		void addNeighbor(int nbr, int weight = 0) {						// adds neighbor
			connectedTo[nbr] = weight;									// if neighbor exists the weight will be updated
																		// if not, the neighbor will be added
		}

		std::vector<int> getConnections() {
			std::vector<int> keys;										// will return a vector containing all neighbors
			for (std::map<int, int>::iterator it = connectedTo.begin();	// Use iterator to find all keys
									it != connectedTo.end(); ++it)
				keys.push_back(it->first);								// add to vector
			return keys;												// return vector
		}

		int getId() { return this->id; }								// return this vector's id

		int getWeight(int nbr) { return this->connectedTo[nbr]; }		// get weight of single edge from this vertex to nbr

		void visit() {
			visited = true;
		}

		bool isVisited() {
			return visited;
		}

		friend std::ostream &operator<<(std::ostream &stream, Vertex<T> &vert) {
			std::vector<int> connects = vert.getConnections();			// get all neighbors
			for (unsigned int i = 0; i < connects.size(); i++)			// iterate through neighbors
				stream	<< "( " << vert.id << " , " 					// print this vertex's id
						<< connects[i] << " ) \n";						// print neighbor's id
			return stream;												// return stream
		}
};
#endif
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>	// to provide a list of vertex keys
#include <map>		// to store the collection of vertices
#include "Vertex.hpp"

template <class T>
class Graph {
	private:
		std::map<int, Vertex<T>> vertList;					// the adjacancy list key -> Vertex
		int numVertices;									// size of graph

	public:
		Graph(){ numVertices = 0; };						// default constructor

		void addVertex(int key, T payload){					// add isolated vertex by specifying key
			numVertices++;									// increase count
			Vertex<T> newVertex = Vertex<T>(key, payload);	// create the vertex
			this->vertList[key] = newVertex;				// put the vertex in the adjacancy list
		}

		Vertex<T>* getVertex(int key){						// get pointer to vertex with key
			if (this->contains( key )){						// does key exits?
				Vertex<T> *vpntr = &vertList[ key ];		// yes, return pointer
				return vpntr;
			}
			return NULL;									// return NULL if not found, don't want to add new key
		}

		int size(){ return this->numVertices; }				// return number of vertices

		bool contains(int key){								// does key exist in this graph?
			for (typename std::map<int, Vertex<T>>::iterator it = vertList.begin();// search for key using an iterator
										it != vertList.end(); ++it){
				if (it->first == key) return true;
			}
			return false;
		}

		void addEdge(int from, int to, int cost = 0) {						// add the edge from key -> to key
			if (!this->contains(from)) {									// the source vertext does not exist yet
				std::cout << from << " was not found, adding!" << std::endl;// helpful message
				this->addVertex(from, "placeholder");						// add it
			}
			if (!this->contains(to))										// destination vertex does not exist yet
				std::cout << to << " was not found, adding!" << std::endl;	// helpful message
			vertList[from].addNeighbor(to, cost);							// add the destination as neighbor to "source"
		}
		
		std::vector<int> getVertices() {									// returns a vector of all keys
			std::vector<int> verts;											// vector to hold keys
			for (typename std::map<int, Vertex<T>>::iterator it = vertList.begin();// iterate through adjacancy list
									it != vertList.end();  ++it)	
				verts.push_back(it->first);									// add to vector
			return verts;													// return vector
		}

		friend std::ostream &operator<<(std::ostream &stream, Graph<T> &grph) {
			for (unsigned int i = 0; i < grph.vertList.size(); i++)
				stream << grph.vertList[i];
			return stream;
		}
};
#endif
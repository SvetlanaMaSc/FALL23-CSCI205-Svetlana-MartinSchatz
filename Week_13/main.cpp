#include <iostream>
#include <queue> 	// for breadth first traversal
#include <stack>	// for depth first traversal
#include "Graph.hpp"

using namespace std;

void bfs(Graph<string>&, Vertex<string>*);
void dfs(Graph<string>&, Vertex<string>*);

int main() {
	Graph<string> g;				// create graph object

	for (int i = 1; i <= 10; i++) 	// create ten vertex objects
		g.addVertex(i, "payload");	// keys will be 1 - 10

	// add edges
	//        F   T   W		(F)rom, (T)o, (W)eight . . . not (F)or (T)he (W)in
	// g.addEdge(1, 2);
	// g.addEdge(1, 5);
	// g.addEdge(2, 1);
	// g.addEdge(2, 3);
	// g.addEdge(2, 4);
	// g.addEdge(2, 5);
	// g.addEdge(3, 2);
	// g.addEdge(3, 4);
	// g.addEdge(4, 2);
	// g.addEdge(4, 3);
	// g.addEdge(4, 5);
	// g.addEdge(5, 1);
	// g.addEdge(5, 2);
	// g.addEdge(5, 4);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 4);
	g.addEdge(2, 5);
	g.addEdge(3, 6);
	g.addEdge(3, 7);

	// g.addEdge(9,  11, 3);	// this call to add edge will add the new vertex with key = 11
	// g.addEdge(11, 10, 2);

	// print graph
	cout 	<< "\nGraph has " 
			<< g.size() << " vertices"	// print number of vertices
			<< g << endl;				// print using overloaded graph stream insertion

	cout << "Breadth First Traversal" << endl;
	bfs(g, g.getVertex(1));

	cout << "\nDepth First Traversal" << endl;
	dfs(g, g.getVertex(1));

	return 0;

	// Exercise 2
	queue<Vertex<string>*> q;
	Vertex source(0, 0);
	source.visit();
}
/*
Breadth-First Search (BFS) is an algorithm used for traversing or searching tree or graph data structures.
It starts at the tree root (or some arbitrary node of a graph) and explores the neighbor nodes at the current
depth prior to moving on to nodes at the next depth level. BFS is often used to find the shortest path
from the source node to all other nodes in an unweighted graph.

Start at the Source Node:
=========================
   - Begin with the source node (or starting node) and enqueue it. If you're working with a graph,
   - the source node is typically the node from which you want to start the traversal.

Visit Neighbors at the Current Depth:
=====================================
   - Dequeue a node from the front of the queue (starting with the source node).
   - Visit all the neighbors (adjacent nodes) of the dequeued node that haven't been visited yet.
   - Enqueue each of these neighbors.

Move to the Next Depth Level:
=============================
   - After visiting all neighbors at the current depth, move to the next depth level by
   - repeating step 2 with the nodes that are now at the front of the queue.

Repeat Until All Nodes Are Visited:
===================================
   - Continue this process until the queue is empty, meaning that all nodes have been visited.

BFS is typically implemented using a queue data structure to keep track of the nodes to be visited.
The queue follows the First-In-First-Out (FIFO) principle, ensuring that nodes are processed in the order they are discovered.

Applications of BFS include finding the shortest path in an unweighted graph, analyzing network connectivity,
and solving puzzles with multiple states. 

The time complexity of BFS is generally O(V + E), where V is the number of vertices and E is the number of edges in the graph.
*/
void bfs(Graph<string>& g, Vertex<string>* v) {
	bool* seen = new bool[ g.size()+1 ]();			// boolean array to track visited nodes. +1 for 1-based indexing
	queue<Vertex<string>*> q;						// queue of Vertex pointers
	q.push(v);										// enqueue the starting node
	seen[ v->getId() ] = true;						// mark the starting node as being "seen"
	
	while ( !q.empty() ) {							// as long as the queue is not empty
		Vertex<string>* vert = q.front();			// dequeue the front vertex
		q.pop();									// remove it from the queue
		cout 	<< "Vertex " << vert->getId();		// print the vertex
		for (int v : vert->getConnections()){		// get all of the edges from the current vertex
			cout << "-->" 							// illustrate connection
				 << g.getVertex( v )->getId();		// print the key of the connected vertex
			if ( !seen[v] ) {						// if the current key has not been "seen"
				Vertex<string>* _v = g.getVertex(v);// get the vertex
				q.push( _v );						// enqueue the vertext
				seen[ v ] = true;					// mark it as seen
			}
		}
		cout << endl;								// just for nice printing
	}
	delete[] seen;									// free up dynamic memory
}

/*
Depth-First Search (DFS) is an algorithm used for traversing or searching tree or graph data structures.
Unlike Breadth-First Search (BFS), DFS explores as far as possible along each branch before backtracking.
It starts at the root node (or an arbitrary node in the case of a graph) and explores as deeply 
as possible along each branch before backtracking.

Start at the Source Node:
=========================
   - Begin with the source node (or starting node). If you're working with a graph, the source node is
   - typically the node from which you want to start the traversal.

Explore as Far as Possible:
===========================
   - Move to an adjacent unvisited node and repeat the process. If there are multiple adjacent nodes,
   - choose one and proceed. This creates a recursive call or a stack-based approach to remember the path.

Backtrack When Necessary:
=========================
   - If there are no more unvisited nodes from the current position, backtrack to the previous node 
   - and continue exploring other unvisited branches.

Repeat Until All Nodes Are Visited:
===================================
   - Continue this process until stack is empty meaning all nodes are visited.

DFS can be implemented using recursion or an explicit stack data structure. In the recursive approach,
the function calls act as the stack, and in the stack-based approach, an actual stack is used to keep track of nodes to be visited.

Applications of DFS include topological sorting, finding connected components in a graph,
solving puzzles (like mazes or Sudoku), and pathfinding algorithms. 

The time complexity of DFS is generally O(V + E), where V is the number of vertices and E is the number of edges in the graph.
*/
void dfs(Graph<string>& g, Vertex<string>* r) {		// iterative depth first search using explicit stack
	char* c = new char[ g.size()+1 ]();				// array to store "visited" status. +1 for 1-based indexing
	stack< Vertex<string>* > s;						// stack of Vertex pointers to store edges
	s.push(r);										// push starting vertex

	while( s.size() > 0 ) {							// as long as the stack is not empty
		Vertex< string >* vert = s.top();			// get current Vertex
		int key = vert->getId();					// get the key of the current vertex
		cout << key << endl;						// print so we can see
		s.pop();									// pop current Vertex from Stack
		if( c[ key ] != 'v' ){						// has this vertex been visited?
			c[ key ]  = 'v';						// It has not. Mark it as visited
			vector<int> edges = g.getVertices();	// edges connected to i
			for (int key : vert->getConnections())	// loop through edges stemming from current vertex
				s.push( g.getVertex( key ) );		// push each vertext on to stack
		}
	}
	delete[] c;										// free up dynamic memory
}
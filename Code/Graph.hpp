#include <algorithm>
#include <stdexcept>
#include <omp.h>
#include "GraphAlgorithms.cpp"
using namespace std;

/**
 * This class handles the graph data structure and the algorithms applied to it.
 */

class Graph
{

	public:
	
	/**PRE: -
	  *POST: creates and initializes a graph.*/
	Graph();


	/**PRE: numnodes => 0.
	  *POST: creates and initializes a graph of numNodes nodes.*/
	Graph(int numNodes);


	/**PRE: number => 0.
	  *POST: adds number nodes to the graph */
	void add_nodes(int number);


	/**PRE: id1 and id2 are two valid node identifiers.
	  *POST: adds an edge between the nodes with identifiers id1 and id2*/
	void add_link(int id1, int id2);


	/**PRE: -
	  *POST: returns true if exists an edge between the nodes with identifiers id1 and id2.
	  *Else return false*/
	bool connected(int id1, int id2);


	/**PRE: -
	  *POST: returns the number of nodes of the graph */
	int get_num_links();


	/**PRE: -
	  *POST: returns the number of edges to the graph */
	int get_num_nodes();


	/**PRE: id is a valid node identifier
	  *POST: returns the neighbours of the node with id = id */
	vector<int> get_neighbours(int id);


	vector<vector<int> > adjacenciesList;
	
	private:

	int numLinks;

};
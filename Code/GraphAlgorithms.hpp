#include <queue>
#include <set>
#include <random>
#include <algorithm>
#include <vector>
#include <iostream>
#include <list>
#include <omp.h>
using namespace std;

/**
 * This class handles the algorithms applied to the graph.
 */

class GraphAlgorithms
{
	public:
		
	/**PRE: startingNode and endingNode are valid ids. 0 <= minLenght < maxLenght. maxNumPaths <0.
	  * adjacenciesList is a valid graph adjacency list.
	  *POST: Returns the set of the shortest paths between the startingNode and the endingNode. The BFS search stops when there
	  * aren't more paths or maxNumPaths have been found. */	
	vector<vector<int> > cropped_paths_BFS(const int & startingNode, const int & endingNode,
	const int & minLenght, const int & maxLenght, const int & maxNumPaths,const vector<vector<int> > & adjacenciesList);

	/**PRE: startingNode and endingNode are valid ids. 0 <= minLenght < maxLenght. maxNumPaths <0.
	  * adjacenciesList is a valid graph adjacency list.
	  *POST: Returns the set of the shortest paths between the startingNode and the endingNode. The DFS search stops when there
	  * aren't more paths or maxNumPaths have been found. */
	vector<vector<int> > rnd_cropped_paths_DFS(const int & startingNode, const int & endingNode,
	const int & minLenght, const int & maxLenght, int maxNumPaths,const vector<vector<int> > & adjacenciesList);

	/**PRE: -
	  *POST: returns the degree of every node of the graph represented in the adjacency list.*/
    vector<int> compute_degrees(const vector<vector<int> > & adjacenciesList);
    

    /**PRE: -
	  *POST: returns the closeness centrality index of every node of the graph represented in the adjacency list.*/
    vector<double> compute_closeness(const vector<vector<pair<int,int> > >& v);


    /**PRE: -
	  *POST: returns the betweenness centrality index of every node of the graph represented in the adjacency list. 
	  AproxRate defines the percentage of the computing done*/
    vector<double> compute_betweenness(const vector<vector<pair<int,int> > > & v, double aproxRate);


    /**PRE: -
	  *POST: returns.a matrix that stores for each node of the graph how many minimum paths betwween all the nodes of the graph 
	  * pass thorugh the node*/
    vector<vector<pair<int,int> > > 
	gen_min_path_ocurrences_matrix(const vector<vector<int> > & adjacenciesList);


	/**PRE: start is a valid id. v is a valid min path ocurrences matrix.
	  *POST: Updates the min path ocurrences matrix with all the min paths that originate from the start node.*/
	void BFS_min_path_num(const int &start, vector <bool> & explored, vector < vector<pair<int,int> > >& v,const vector<vector<int> > & adjacenciesList);
	
	
	private:

	double compute_betweenness_node(const int& currentNode,const vector<vector<pair<int,int> > >& v, const double aproxRate);

	void cropped_DFS_recursion(const int & currentNode, const int & endingNode,
	const int & minLenght, const int & maxLenght, int & foundPathsCounter,
	list<int> & currentPath, const vector<vector<int> > & adjacenciesList, list<vector<int> > & pathList);
	
};

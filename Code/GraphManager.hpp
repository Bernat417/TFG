#include <iostream>
#include <vector>
#include <string> 
#include "Graph.cpp"

using namespace std;

/**
 * This class handles the management of the graph data structure and the algorithms applied to it.
 */

class GraphManager
{
	public:

	/**PRE: -
	  *POST: creates and initializes a PathsManager.*/
	GraphManager();


	/**PRE: -
	  *POST: creates and initializes a GraphManager and a graph data structure with 
	  * number nodes.*/
    GraphManager(int number);


    /**PRE: -
	  *POST: creates and initializes a GraphManager and a graph data structure with 
	  * the links in the graphLinksList.*/
    GraphManager(int number,const vector<pair<int,int> > & graphLinksList);


    /**PRE: -
	  *POST: returns a summary of different indicators (num nodes, num links, mean rank, max rank, min rank)of the 
	  graph data structure.*/
    vector<pair<string,double> > get_summary();

    /**PRE: -
	  *POST: returns the degree of every node of the graph represented in the graph data structure.*/
    vector<int>	 get_indicator_degree();


    /**PRE: -
	  *POST: returns the closeness centrality index of every node of the graph represented in the graph data structure.*/
    vector<double>	 get_indicator_closeness();


    /**PRE: -
	  *POST: returns the betweennes centrality index of every node of the graph represented in the graph data structure.*/
    vector<double>	 get_indicator_betweenness();
    
    /**PRE: startingNode and endingNode are valid ids. 0 <= minLenght < maxLenght. maxNumPaths <0.
	  * adjacenciesList is a valid graph adjacency list.
	  *POST: Returns the set of the shortest paths between the startingNode and the endingNode. The search stops when there
	  * aren't more paths or maxNumPaths have been found. */
    vector<vector<int> > get_cropped_paths(const int & startingNode, const int & endingNode,
		const int & minLenght, const int & maxLenght, const int & maxNumPaths);

    vector<vector<int> > get_adjacency_list();

	private:

	Graph graph;
	GraphAlgorithms algorithms;
	
	//indicators
	bool updatedIndicatorDegree;
	bool updatedIndicatorCloseness;
	bool updatedIndicatorBetweenness;

	vector<int> indicatorDegree;
	vector<double> indicatorCloseness;
	vector<double> indicatorBetweenness;

	//inner functions
	void compute_indicator_degree();	
	void compute_indicator_closeness();
	void compute_indicator_betweenness();


};
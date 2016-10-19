#include "GraphManager.hpp"

GraphManager::GraphManager()
{
	Graph graph;
	algorithms = GraphAlgorithms ();

	updatedIndicatorDegree = false;
	updatedIndicatorCloseness = false;
	updatedIndicatorBetweenness = false;
}


GraphManager::GraphManager(const int number)
{
	graph = Graph (number);
	algorithms = GraphAlgorithms ();

	updatedIndicatorDegree = false;
	updatedIndicatorCloseness = false;
	updatedIndicatorBetweenness = false;
}


GraphManager::GraphManager(const int number,const vector<pair<int,int> > & graphLinksList)
{
	graph = Graph (number);
	algorithms = GraphAlgorithms ();

	updatedIndicatorDegree = false;
	updatedIndicatorCloseness = false;
	updatedIndicatorBetweenness = false;

	for(int i = 0; i < graphLinksList.size(); ++i)
		graph.add_link(graphLinksList[i].first, graphLinksList[i].second);
}


vector<pair<string,double> > GraphManager::get_summary()
{
	vector<pair<string,double> > summary;

	pair<string,double> numNodes ("Number of nodes:",graph.get_num_nodes());
	summary.push_back(numNodes);
	
	pair<string,double> numLinks ("Number of undirected links:",graph.get_num_links()/2);
	summary.push_back(numLinks);

	if(numNodes.second > 0)
	{
		double meanRankValue = graph.get_num_links()/graph.get_num_nodes();
		pair<string,double> meanRank ("Mean of the Rank:",meanRankValue);
		summary.push_back(meanRank);

		int size;
		int min = (graph.get_neighbours(0)).size();
		int max = 0;

		for(int i = 1; i < numNodes.second; ++i)
		{
			size = (graph.get_neighbours(i)).size();
			if(size > max)
				max = size;
			else if(size < min)
				min = size;
		}

		pair<string,double> maxRank ("Max Rank:",max);
		summary.push_back(maxRank);

		pair<string,double> minRank ("Min Rank:",min);
		summary.push_back(minRank);
	}

	return summary;
}


vector<int> GraphManager::get_indicator_degree()
{
	if(not updatedIndicatorDegree)
	{
		compute_indicator_degree();
		updatedIndicatorDegree = true;
	}

	return vector<int> (indicatorDegree);
}

vector<double> GraphManager::get_indicator_closeness()
{
	if(not updatedIndicatorCloseness)
	{
		compute_indicator_closeness();
		updatedIndicatorCloseness = true;
	}

	return vector<double> (indicatorCloseness);
}

vector<double> GraphManager::get_indicator_betweenness()
{
	if(not updatedIndicatorBetweenness)
	{
		compute_indicator_betweenness();
		updatedIndicatorBetweenness = true;
	}

	return vector<double> (indicatorBetweenness);
}

vector<vector<int> > GraphManager::get_cropped_paths(const int & startingNode, const int & endingNode,
	const int & minLenght, const int & maxLenght, const int & maxNumPaths)
{
	vector<int> neighbours = graph.adjacenciesList[startingNode];

	random_shuffle(neighbours.begin(),neighbours.end());

	return algorithms.rnd_cropped_paths_DFS(startingNode,endingNode,minLenght,maxLenght,maxNumPaths,graph.adjacenciesList);
}

void GraphManager::compute_indicator_degree()
{
	indicatorDegree = algorithms.compute_degrees(graph.adjacenciesList);
}


void GraphManager::compute_indicator_closeness()
{
	indicatorCloseness = algorithms.compute_closeness(algorithms.gen_min_path_ocurrences_matrix(graph.adjacenciesList));
}


void GraphManager::compute_indicator_betweenness()
{
	indicatorBetweenness = algorithms.compute_betweenness(algorithms.gen_min_path_ocurrences_matrix(graph.adjacenciesList),1.0);
}


vector<vector<int> > GraphManager::get_adjacency_list()
{
	return graph.adjacenciesList;
}

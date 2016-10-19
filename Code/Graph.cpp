#include "Graph.hpp"

Graph::Graph()
{
	vector<vector<int> > adjacenciesList;
}


Graph::Graph(int numNodes)
{
	if (numNodes < 0)
		throw invalid_argument("Negative number of nodes");

	numLinks = 0;
	adjacenciesList = vector<vector<int> >  (numNodes,vector<int>(0));
}


void Graph::add_nodes(int number)
{
	if (number < 0)
		throw invalid_argument("Negative number");

	for(int i = 0; i < number; ++i)
		adjacenciesList.push_back(vector<int>() );
}


void Graph::add_link(int id1, int id2)
{
	if (id1 >= adjacenciesList.size() or id1 < 0)
	{
		throw invalid_argument("Invalid identifier");
	}

	if (id1 >= adjacenciesList.size() or id2 < 0)
	{
		throw invalid_argument("Invalid identifier");
	}

	bool alreadyNeighbour = false;

	for(int i = 0; i < adjacenciesList[id1].size() and not alreadyNeighbour; ++i)
		if(adjacenciesList[id1][i] == id2) alreadyNeighbour = true;

	if(not alreadyNeighbour)
	{
		adjacenciesList[id1].push_back(id2);
		adjacenciesList[id2].push_back(id1);
		++numLinks;
	}
}


bool Graph::connected(int id1, int id2)
{
	if (id1 >= adjacenciesList.size() or id1 < 0)
		throw invalid_argument("Invalid identifier");

	if (id1 >= adjacenciesList.size() or id2 < 0)
		throw invalid_argument("Invalid identifier");
	
	int origin, neighbour;
	if(adjacenciesList[id1].size() <= adjacenciesList[id2].size())
	{
		origin = id1;
		neighbour = id2;
	}
	else
	{
		origin = id2;
		neighbour = id1;
	}

	bool found = false;
	for(int i = 0; i < adjacenciesList[origin].size() and not found; ++i)
		if(adjacenciesList[origin][i] == neighbour) 
			found = true;

	return found;
}


int Graph::get_num_nodes()
{
	return adjacenciesList.size();
}


int Graph::get_num_links()
{
	return numLinks;
}


vector<int> Graph::get_neighbours(int id)
{
	if (id >= adjacenciesList.size() or id < 0)
		throw invalid_argument("Invalid identifier");

	return vector<int> (adjacenciesList[id]);
}









	

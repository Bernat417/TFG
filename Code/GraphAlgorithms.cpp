#include "GraphAlgorithms.hpp"

bool present(const int & elem, const list<int> & container)
{
	list<int>::const_iterator it;
	for(it = container.begin(); it != container.end(); ++it)
		if(*it == elem)return true;

	return false;
}

vector<int> list_to_vector(const list<int> & l)
{
	vector<int> v(l.size());
	int index = 0;
	list<int>::const_iterator it;

	for(it = l.begin(); it != l.end(); ++it, ++index)
		v[index] = *it;

	return v;
}

vector<vector<int> > list_to_vector(const list<vector<int> >& l)
{
	vector<vector<int> > v(l.size());
	int index = 0;
	list<vector<int> >::const_iterator it;

	for(it = l.begin(); it != l.end(); ++it, ++index)
		v[index] = *it;

	return v;
}



vector<vector<int> > GraphAlgorithms::rnd_cropped_paths_DFS(const int & startingNode, const int & endingNode,
	const int & minLenght, const int & maxLenght, int maxNumPaths,const vector<vector<int> > & adjacenciesList)
/* This function executes a randomized DFS search with minimum amb maximum length and returns all the viable paths*/
{
	list<vector<int> > pathList;
	
	vector<int> neighbours = adjacenciesList[startingNode];

	random_shuffle(neighbours.begin(),neighbours.end());

	#pragma omp parallel for shared(neighbours, endingNode, minLenght, maxLenght, maxNumPaths,\
			adjacenciesList,pathList) 
	for(int i = 0; i < neighbours.size(); ++i)
	{

		list<int> currentPath;
		currentPath.push_back(startingNode);
		cropped_DFS_recursion(neighbours[i], endingNode, minLenght, maxLenght, maxNumPaths,
			currentPath, adjacenciesList,pathList);
	}

	return list_to_vector(pathList);
}


void GraphAlgorithms::cropped_DFS_recursion(const int & currentNode, const int & endingNode,
	const int & minLenght, const int & maxLenght, int & foundPathsCounter,
	list<int> & currentPath, const vector<vector<int> > & adjacenciesList, list<vector<int> > & pathList)
{
	if(foundPathsCounter > 0)
	{
		currentPath.push_back(currentNode);

		if(currentNode == endingNode)
		{
			#pragma omp critical
			if(foundPathsCounter > 0 and (currentPath.size()-1) >= minLenght)
			{
				pathList.push_back(list_to_vector(currentPath));
				#pragma omp atomic
				--foundPathsCounter;
			}


		}
		else 
		{
			//Init
			vector<int> neighbours(adjacenciesList[currentNode].size());
			for(int i = 0; i < neighbours.size(); ++i) 
			{ 
				if(not present(adjacenciesList[currentNode][i], currentPath))
					neighbours[i] = adjacenciesList[currentNode][i];
				else
					neighbours[i] = -1;
			}

			random_shuffle(neighbours.begin(),neighbours.end());

			if(maxLenght >= currentPath.size())
			{
				for(int i = 0; i < neighbours.size(); ++i)
					if(neighbours[i] != -1)
					cropped_DFS_recursion(neighbours[i], endingNode, minLenght, maxLenght, foundPathsCounter,
						currentPath, adjacenciesList,pathList);
			}
		}

		currentPath.pop_back();
	}
	
}




vector<vector<int> > GraphAlgorithms::cropped_paths_BFS(const int & startingNode, const int & endingNode,
	const int & minLenght, const int & maxLenght, const int & maxNumPaths,const vector<vector<int> > & adjacenciesList)
/* This function executes a regular BFS search with minimum amb maximum length and returns all the viable paths*/
	{
		vector<vector<int> > validPaths;
		pair<int,list<int> > current;
		set<int>::const_iterator it;
		list<int>::const_iterator itList;
		int distance = 0;
		int pathsLeft = maxNumPaths;
		
		queue <pair<int,list<int> > > Q;
		Q.push(pair<int,list<int> >(startingNode,list<int>()));
		Q.push(pair<int,list<int> >(-1,list<int>()));

		while (!Q.empty() and pathsLeft>0) 
		{
			current = Q.front();
			Q.pop();

			if(current.first==-1)
			{
				++distance;
				if(!Q.empty())Q.push(pair<int,list<int> >(-1,list<int>()));
			}
			else
			{
				if(current.first == endingNode and ((current.second).size() >= minLenght))
				{
					vector<int> validPath(1 + (current.second).size());
					int position = 0;

					for(itList = (current.second).begin(); itList != (current.second).end(); ++itList)
					{
						validPath[position] = *itList;
						++position;
					}
					validPath[position] = current.first;

					--pathsLeft;
					validPaths.push_back(validPath);
				}
				else if(((current.second).size()+1) <= maxLenght)
				{
					for (int i = 0; i < adjacenciesList[current.first].size(); ++i)
            	    {
            	    	bool found = (std::find((current.second).begin(), (current.second).end(),
            	    		 adjacenciesList[current.first][i]) != (current.second).end());
            	    	
            	    	if(not found)
            	    	{
            	    		list<int> previousNodes(current.second);
            	    		previousNodes.push_back(current.first);
            	    		Q.push(pair<int,list<int> >(adjacenciesList[current.first][i],previousNodes));
            	    	}
            	    }
            	}
        	}
    		
		}

		return validPaths;
	}


vector<int> GraphAlgorithms::compute_degrees(const vector<vector<int> > & adjacenciesList)
/*This function calculates the degree indicator for each node of the graph*/
{	
	vector<int> degrees(adjacenciesList.size());

	#pragma omp parallel shared(degrees)
	for(int i = 0; i < adjacenciesList.size(); ++i)
		degrees[i] =  (adjacenciesList[i]).size();

	return degrees;
}


vector<vector<pair<int,int> > > 
GraphAlgorithms::gen_min_path_ocurrences_matrix(const vector<vector<int> > & adjacenciesList)
/* This function computes for each pair of nodes the min path length and the numer of paths with that
length between the two nodes*/
{
	cout << "Generating min path graph..." << endl;

	int graphNodes =  adjacenciesList.size();
	vector<vector<pair<int,int> > > 
	v(graphNodes, vector<pair<int, int> > (graphNodes, pair<int,int> (0,0))); //Matrix of distances and repetitions

	#pragma omp parallel for shared(v)
	for(int i = 0; i <graphNodes ; ++i)
	{			
		vector<bool> explored(graphNodes,false);
		explored[i] = true;
		BFS_min_path_num(i, explored, v,adjacenciesList);
	}

	cout << "> Done" << endl << endl;

	return v;
}



void GraphAlgorithms::BFS_min_path_num(const int &start, vector <bool> & explored, 
	vector < vector<pair<int,int> > > & v,const vector<vector<int> > & adjacenciesList)
/* This function computes from one node to all the other nodes the min path length and the numer of paths with that
length between the two nodes*/
{
	queue <pair<int,int> > Q;
	int distance = 1;
	pair<int,int> current;
	v[start][start].second = 1;

	for (int i = 0; i < adjacenciesList[start].size(); ++i)
        if(!explored[adjacenciesList[start][i]])Q.push(pair<int,int>(adjacenciesList[start][i], start));

	Q.push(pair<int,int>(-1,-1));

	while (!Q.empty()) 
	{
		current = Q.front();
		Q.pop();

		if(current.first==-1)
		{
			++distance;
			if(!Q.empty())Q.push(pair<int,int>(-1,-1));		
		}
		else {
			if(v[start][current.first].first == 0) 
			{
				v[start][current.first].first = distance;
				v[start][current.first].second = v[start][current.second].second;
			}	
			else if(v[start][current.first].first == distance)
			{
				v[start][current.first].second += v[start][current.second].second;	
			}

			if(!explored[current.first])
			{				
				explored[current.first] = true;
				for (int i = 0; i < adjacenciesList[current.first].size(); ++i)
                	if(!explored[adjacenciesList[current.first][i]])Q.push(pair<int,int>(adjacenciesList[current.first][i], current.first));
        	}
		}
	}
}


vector<double> GraphAlgorithms::compute_closeness(const vector<vector<pair<int,int> > >& v)
/*This function calculates the closeness indicators for each node of the graph*/
{

	int graphNodes = v.size();
	vector<double> closeness(graphNodes);
	
	cout << "Computing closeness..." << endl;

	//#pragma omp parallel for shared(v, closeness)
	for(int i = 0; i < graphNodes; ++i)
	{
		int distances = 0;
		for(int j = 0; j < graphNodes; ++j)
			distances += v[i][j].first;
		closeness[i] = distances;
	}

	cout << "> Done" << endl << endl;

	return closeness;
}


vector<double> GraphAlgorithms::compute_betweenness(const vector<vector<pair<int,int> > > & v,double aproxRate)
/*This function calculates the betweeness indicator for each node of the graph*/
{
	int graphNodes = v.size();
	if(aproxRate <= 0.0) aproxRate = 0.01;
	else if(aproxRate > 1.0) aproxRate = 1.0;

	vector<double> betweenness(graphNodes);

	cout << "Computing betweennes..." << endl;
	
	#pragma omp parallel for shared(v)
	for(int i = 0; i < graphNodes; ++i)
	{
		betweenness[i] = compute_betweenness_node(i, v, aproxRate);
		#pragma omp critical 
		cout << "Protein number " << i << " ready with a betweenness of: " << betweenness[i] << endl;
	}

	return betweenness;
}	


double GraphAlgorithms::compute_betweenness_node(const int& currentNode,const vector<vector<pair<int,int> > >& v,const double aproxRate)
/*This function calculates the betweenness of a single node of the graph*/
{
	int graphNodes = v.size();
	int numNodesToExplore =  ((int) ((double) graphNodes)/ aproxRate);

	set <int> nodeList;

	if(aproxRate > 0.6)
	{
		set <int> invertedNodeList;

		for(int i = 0; i < (graphNodes-numNodesToExplore);++i)
		{
			int id = rand()%graphNodes;

			while(invertedNodeList.find(id)!=invertedNodeList.end())
			{
				id = rand()%graphNodes;
			}

			invertedNodeList.insert(id);
		}

		for (int i = 0; i < numNodesToExplore; ++i)
			if(invertedNodeList.find(i)==invertedNodeList.end())
				nodeList.insert(i);

	}
	else
	{
		for(int i = 0; i < numNodesToExplore;++i)
		{
			int id = rand()%graphNodes;

			while(nodeList.find(id)!=nodeList.end())
				id = rand()%graphNodes;

			nodeList.insert(id);
		}
	}

	double betweennes = 0;
	
	set<int>::iterator it;

	for(int i = 0; i < graphNodes; ++i)
	{
		if(currentNode != i)
			for(int j = i+1; j < graphNodes; ++j)
			{
				if((currentNode != j) and (j !=i))
					if(v[i][j].first == (v[i][currentNode].first + v[currentNode][j].first))
						if((v[i][j].second != 0) and (v[i][currentNode].first !=0) and (v[currentNode][j].first !=0))
							betweennes +=  double(v[i][currentNode].second * v[currentNode][j].second) / double(v[i][j].second);
			}
						
			
	}
	
	
	
	return betweennes;
}


#include "PredictionModule.hpp"

vector<pair<double,vector<int> > > PredictionModule::predict(GraphManager graphM, 
	PathsManager pathsM, const int & startingNode, const int & endingNode,
	const int & minLenght, const int & maxLenght, const int & maxNumPaths)
/* This function executes the prediction algorithm*/
{
	/* We generate the candidate paths randomly*/
	vector<vector<int> > validPaths= graphM.get_cropped_paths(startingNode, endingNode,
	minLenght, maxLenght, maxNumPaths);

	/* We compute the fitness for each of them while we keep them ordered in 
	decreasing order by fitness*/
	priority_queue< pair<double,vector<int> > > pathsOrderedByFitness;
	for(int i = 0; i < validPaths.size(); ++i)
	{
		double simIndex = pathsM.similarity_index(validPaths[i]);
		pathsOrderedByFitness.push(pair<double,vector<int> >(simIndex,validPaths[i]));
	}

	/* We change the result to a vector format and return it*/
	vector<pair<double,vector<int> > > pathsOrdered(validPaths.size());
	for(int i = 0; i < validPaths.size(); ++i)
	{
		pathsOrdered[i] = (pathsOrderedByFitness.top());
		pathsOrderedByFitness.pop();
	}
	
	if(validPaths.size() == 0) return vector<pair<double,vector<int> > >();
	return pathsOrdered;
}


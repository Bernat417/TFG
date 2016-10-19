#include <iostream>
#include <vector>
#include "GraphManager.cpp" 
#include "PathsManager.cpp" 

using namespace std;

/**
 * This class handles the prediction.
 */

class PredictionModule
{
	public:

	/**PRE: startingNode and endingNode are valid identifiers
	  *POST: returns the paths ordered by its likelyhood of appearence.*/
	vector<pair<double,vector<int> > > predict(GraphManager graphM, PathsManager pathsM, const int & startingNode, const int & endingNode,
	const int & minLenght, const int & maxLenght, const int & maxNumPaths);
    
	private:
};
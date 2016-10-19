#include <iostream>
#include <vector>
#include <string> 
#include "Paths.cpp"
#include "PathsAlgorithms.cpp"

using namespace std;

/**
 * This class handles the management of the paths data structure and algorithms.
 */

class PathsManager
{
	public:

	/**PRE: -
	  *POST: creates and initializes a PathsManager.*/
	PathsManager();

	/**PRE: -
	  *POST: creates and initializes a PathsManager and a paths data structure with 
	  * the paths in the pathList.*/
	PathsManager(const vector<list<list<int> > > & pathList);

	/**PRE: -
	  *POST: returns the similarity index of the path.*/
	double similarity_index(const vector<int> & path);

	double num_paths();
    
	private:
	Paths paths;
	PathsAlgorithms pathsAlgorithms;
};
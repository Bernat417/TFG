#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream> 
#include <iterator>
#include <omp.h>

using namespace std;

/**
 * This class handles the paths data structure and the algorithms applied to it.
 */

class Paths
{
	public:

	/**PRE: -
	  *POST: creates and initializes a paths data structure.*/
	Paths();


	/**PRE: -
	  *POST: creates and initializes a paths data structure using the pathList.*/
	Paths(const vector<list<list<int> > > & pathList);


	/**PRE: numPath is a valid path identifier. 0 <= Index << paths[numIndex] size. 
	  *POST: returns the nodes of the stage index of the path with the numPath id.*/
	vector<int> stage_nodes(int numPath, int index);


	/**PRE: numPath is a valid path identifier. 
	  *POST: returns the lenght of the path with the numPath id.*/
	int path_lenght(int numPath);
	
	/**PRE: -
	  *POST: returns the number of existing paths.*/
	int num_paths();


	/**PRE: -
	  *POST: returns the maximum lenght of any existing paths.*/
	int max_lenght();


	/**PRE: -
	  *POST: adds all the paths in the path list to the data structure.*/
	void add_path(const list< list <int> > & path);


	/**PRE: i is a valid path identifier. 
	  *POST: returns the path with the i id.*/
	vector<vector<int> > get_path(int i);


	/**PRE: -
	  *POST: returns the all the existing paths */	
	vector<vector<vector<int> > > get_paths();

	/**PRE: -
	  *POST: returns the lenght of all the existing paths */
	vector<int> get_path_lenght();

	/**PRE: -
	  *POST: returns all the existing paths that contain the id element*/
	list<int> find_path_with_element(int id);

	vector<vector<vector<int> > > paths; //Paths
	
	private:
	
	
};
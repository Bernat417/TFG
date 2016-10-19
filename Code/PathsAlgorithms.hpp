#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

/**
 * This class handles the algorithms applied to the paths.
 */
 
class PathsAlgorithms
{
	public:

	/**PRE: -
	  *POST: returns the similarity index of the path.*/	
	double similarity_index_calc(const vector<int> & pathA, const vector< vector<int> > & pathB);

	/**PRE: -
	  *POST: returns the similarity index of the path.*/
	double similarity_index(const vector<int> & path,const vector<vector<vector<int> > >& paths);


	private:

	bool isPresent(int x, vector<int> v);
	

};

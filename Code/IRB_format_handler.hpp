#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

/**
 * This class handles the IO operations of the files with the format the IRB provided.
 */
 
class IRB_format_handler
{
	public:

	/**PRE: a file with the name = name exists with the IRB format for edges.
	  *POST: returns the content of the file in a vector of pairs format.*/
	vector<pair<string,string> > read_graph_link_list(string name);


	/**PRE: a file with the name = name exists with the IRB format for paths.
	  *POST: returns the content of the file in a vector of list of lists format.*/
	vector<list<list<string> > > read_path_list(string name);
    
	private:

};
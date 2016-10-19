#include "CSV_handler.cpp"
#include "IRB_format_handler.cpp"

/**
 * This class handles the data layer.
 */
 
class DataController
{
	public:

	/**PRE: -
	  *POST: creates and initializes a DataController.*/
	DataController();

	/**PRE: a file with the name = name exists with the IRB format for edges.
	  *POST: returns the content of the file in a vector of pairs format.*/
	vector<pair<string,string> > read_graph_link_list(string name);
	

	/**PRE: -
	  *POST: print in the standart exit the content of the vector of pairs v.*/
	void print_vector_of_pairs (string title, vector<pair<string,double> > v);

	/**PRE: -
	  *POST: stores the vector of pairs v into a file with the name = filename parameter. */
	void save_vector_of_pair(string filename, vector<pair<string,vector<string> > > vPair);
	

	/**PRE: a file with the name = name exists with the IRB format for paths.
	  *POST: returns the content of the file in a vector of list of lists format.*/
	vector<list<list<string> > > read_path_list(string name);

	/**PRE: -
	  *POST: stores the names vector of vectors content into a file with the name = filename parameter.
	  * in CSV format */
	void save_csv_file(string filename, vector<vector<string> > lines);
	
	private:
    CSV_handler CSV;
    IRB_format_handler IRB_format;
};

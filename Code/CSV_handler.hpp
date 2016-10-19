#include <iostream>
#include <vector>
#include <string> 
#include <fstream>

using namespace std;

/**
 * This class handles the IO operations of the files with the CSV format.
 */

class CSV_handler
{
	public:

	/**PRE: -
	  *POST: stores the names vector of vectors content into a file with the name = filename parameter.
	  * in CSV format */
    void save_csv_file(string filename, vector<vector<string> > lines);
    
	private:
		
};

#include "CSV_handler.hpp"


void CSV_handler::save_csv_file(string filename, vector<vector<string> > lines)
{
    ofstream File (filename);         //Opening file to print info to

    if(lines.size() >= 1)
    	for(int j = 0; j < lines[0].size(); ++ j)
    	{
	    	for(int i = 0; i < (lines.size()-1); ++i)
	    		File << lines[i][j] << ",";

	    	File << lines[(lines.size()-1)][j] << endl;
			
	    }

    File.close();
}

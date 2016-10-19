#include "DataController.hpp"

DataController::DataController()
{
    CSV = CSV_handler();
    IRB_format = IRB_format_handler();
}

vector<pair<string,string> > DataController::read_graph_link_list(string name)
{
    return IRB_format.read_graph_link_list(name);
}


vector<list<list<string> > > DataController::read_path_list(string name)
{
    return IRB_format.read_path_list(name);
}


void DataController::print_vector_of_pairs (string title, vector<pair<string,double> > v)
{
  cout << title << endl;
  
  for(int i = 0; i < v.size(); ++i)
    cout << v[i].first << ' ' << v[i].second << endl;

  cout << endl;
}

void DataController::save_csv_file(string filename, vector<vector<string> > lines)
{
	CSV.save_csv_file(filename,lines);
}

void DataController::save_vector_of_pair(string filename, vector<pair<string,vector<string> > > vPair)
{
	ofstream File (filename);         //Opening file to print info to
	File << "Fitness_Measure \t Path" << endl;
    for(int i = 0; i < vPair.size(); ++i)
    {
    	File << vPair[i].first << '\t';
	   	for(int j = 0; j < ((vPair[i].second).size()-1); ++j)
	   		File << (vPair[i].second)[j] << "-";

	   	File << (vPair[i].second)[(vPair[i].second).size()-1] << endl;		
	}

    File.close();
}
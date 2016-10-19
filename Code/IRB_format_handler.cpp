#include "IRB_format_handler.hpp"

vector<pair<string,string> > IRB_format_handler::read_graph_link_list(string name)
{
	vector<pair<string,string> > graphLinks;

    string line;
	ifstream myfile;
    myfile.open (name.c_str()); 

    while(getline(myfile,line))
    {
        vector<string> strs;
        istringstream iss(line);
        copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter<vector<string> >(strs));
        //Load codes and structures for elements if new
        
        graphLinks.push_back(pair<string,string> (strs[0],strs[1]));
    }

    myfile.close();

    return graphLinks;
}


vector<list<list<string> > > IRB_format_handler::read_path_list(string name)
{
    int count = 0;
    string line;
    ifstream myfile;
    myfile.open (name.c_str()); 
    vector<list< list<string> >> paths;

    while(getline(myfile,line))
    {
        list< list<string> > path;
        for (int i=1;i<(line.length());++i) 
        {
            while(line[i] != ']')
            {
                if(line[i] == '[')
                {
                    ++i;
                    string current;
                    list<string> s;
                    while(line[i] != ']')
                    {
                        if(line[i] == ',')
                        {
                            s.push_back(current);
                            current = *new string;
                        }
                        else
                        {
                            if((line[i] != ' ') and (line[i] != '\''))
                                current.push_back(line[i]);
                        }
                        ++i;
                    }
                    s.push_back(current);
                    current = *new string;
                    if(s.size() > 0) path.push_back(s);
                }
                ++i;
            }
        }
        paths.push_back(path);
    }
    myfile.close();
    return paths;
}

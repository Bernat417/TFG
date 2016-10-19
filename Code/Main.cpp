#include "LogicController.cpp"

string inputString(const string & message)
{
	string input;
	cout << message << endl;
	cin >> input;
	cout << endl;
	return input;
}

void usage()
{
	cout << "Usage:" << endl
	<< "In order to use this software you need to"  
	<< " add a parameter to the call depending on the function you want to use." << endl
 	<< "Command guide:" << endl
 	<< "> Use \"./program graph_summary\" to get general data of the graph from the standard exit"
 	<<endl
 	<< "> Use \"./program graph_indicators\" to compute and save several graph node centrality indicators"
 	<< " (Degree, Closeness and Betweenness)  in csv format to a file you specify"
 	<<endl
 	<< "> Use  \"./program predict\" to predict and save to a file you specify the most likely"
 	<< " paths between two proteins"
 	<< endl;
}

int main(int argc, char* argv[])
{
	LogicController logic;

	if(argc ==2)
	{
		string functionCode = "graph_summary";
		if(!functionCode.compare(argv[1]))
		{
			logic.set_graph(inputString(string("Introduce graph file name")));
			logic.graph_summary();
		}

		functionCode = "graph_indicators";
		if(!functionCode.compare(argv[1]))
		{
			logic.set_graph(inputString(string("Introduce graph file name (With file extension)")));
			logic.graph_indicators(inputString(string("Introduce output file name (With file extension)")));
		}

		functionCode = "predict";
		if(!functionCode.compare(argv[1]))
		{
			logic.set_graph(inputString(string("Introduce graph file name (With file extension)")));
			logic.set_paths(inputString(string("Introduce path file name (With file extension)")));

			string filename = inputString(string("Introduce output file name (With file extension)"));
			string startProtein = inputString(string("Introduce the starting protein"));
			string endProtein = inputString(string("Introduce the ending protein"));

			cout << "Introduce the maximum number of paths you want to produce" << endl;
			int numMaxPaths;
			cin >> numMaxPaths;
			cout << endl;

			cout << "Introduce the minimum length for the paths you want to produce" << endl;
			int minLength;
			cin >> minLength;
			cout << endl;

			cout << "Introduce the maximum length for the paths you want to produce" << endl;
			int maxLength;
			cin >> maxLength;
			cout << endl;

			logic.predict(filename, startProtein, endProtein, minLength, maxLength, numMaxPaths);
		}
	}
	else
		usage();

}

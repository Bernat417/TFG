#include "DataController.cpp"
#include "Translator.cpp"
#include "AnalisisModule.cpp"
#include "PredictionModule.cpp"
#include <sstream>

/**
 * This class handles the management of the logic layer.
 */

class LogicController
{
	public:

	/**PRE: -
	  *POST: creates and initializes a LogicController.*/
	LogicController();


	/**PRE: it exists a file with name = name
	  *POST: creates and initializes a GraphManager using the data in the file with the 
	  name = filename paramenter.*/
	void set_graph(const string & filename);


	/**PRE: it exists a file with name = name
	  *POST: creates and initializes a PathsManager using the data in the file with the 
	  name = filename paramenter.*/
	void set_paths(const string &  filename);
	

	/**PRE: -
	  *POST: prints in the standart exit different indicators of the graph data structure.*/
	void graph_summary();

	/**PRE: -
	  *POST: saves the graph indicator in a file with name = filename paramenter.*/
	void graph_indicators(const string & filename);
	

	/**PRE: startingNode and endingNode are valid identifiers
	  *POST: returns the paths ordered by its likelyhood of appearence.*/
	void predict(const string & filename, const string & startingNode, const string & endingNode,
		const int & minLenght, const int & maxLenght, const int & maxNumPaths);

	private:
	DataController data;
	Translator translator;
	GraphManager graphM;
	PathsManager pathsM;
	PredictionModule PredictM;

	vector<pair<string,vector<string> > > prediction_out_translation(const vector<pair<double,vector<int> > > &v);
	vector<string> vector_to_vstring(const vector<double>  &v);
	vector<string> vector_to_vstring(const vector<int>  &v);

};

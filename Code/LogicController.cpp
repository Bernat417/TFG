#include "LogicController.hpp" 

vector<string> LogicController::vector_to_vstring(const vector<double>  &v)
{
	vector<string> strV(v.size());

	for(int i = 0; i < v.size(); ++i)
	{
		ostringstream strs;
		strs << v[i];
		strV[i] = strs.str();
	}

	return strV;
}

vector<string> LogicController::vector_to_vstring(const vector<int>  &v)
{
	vector<string> strV(v.size());

	for(int i = 0; i < v.size(); ++i)
	{
		ostringstream strs;
		strs << v[i];
		strV[i] = strs.str();
	}

	return strV;
}

vector<pair<string,vector<string> > > LogicController::prediction_out_translation(const vector<pair<double,vector<int> > > &v)
{
	vector<pair<string,vector<string> > > strV(v.size());

	for(int i = 0; i < v.size(); ++i)
	{
		ostringstream strs;
		strs << v[i].first;
		strV[i].first = strs.str();

		strV[i].second = vector<string>((v[i].second).size());
		for(int j = 0; j < (v[i].second).size(); ++j)
		{
			(strV[i].second)[j] = string(translator.translate((v[i].second)[j]));
		}
	}

	return strV;
}

LogicController::LogicController()
{
	DataController data;
	Translator translator;
	GraphManager graphM;
	PathsManager pathsM;
	PredictionModule PredictM;
}

void LogicController::set_graph(const string & filename)
{
	vector<pair<string,string> > graphLinksList;
	graphLinksList = data.read_graph_link_list(filename);

	for(int i = 0; i < graphLinksList.size();++i)
	{
		translator.add(graphLinksList[i].first);
		translator.add(graphLinksList[i].second);
	}		
	
	graphM = GraphManager (translator.get_num_ids(),translator.translate(graphLinksList));
}


void LogicController::set_paths(const string & filename)
{
	vector<list<list<string> > > pathList;
	pathList = data.read_path_list(filename);
	
	list<list<string>>::iterator it;

	for(int i = 0; i < pathList.size();++i)
		for(it = pathList[i].begin(); it != pathList[i].end(); ++it)
				translator.add(*it);

	pathsM = PathsManager(translator.translate(pathList));
}


void LogicController::graph_summary()
{
	data.print_vector_of_pairs("> Graph Summary",graphM.get_summary());
}


void LogicController::graph_indicators(const string &  filename)
{
	vector<vector<string> > indicators;

	vector<string> strNames(1,"Name");
	vector<string> contentNames = translator.get_names();
	strNames.insert(strNames.end(),contentNames.begin(),contentNames.end());
	indicators.push_back(strNames);

	vector<string> strDegrees(1,"Degree");
	vector<string> contentDegrees = vector_to_vstring(graphM.get_indicator_degree());
	strDegrees.insert(strDegrees.end(),contentDegrees.begin(),contentDegrees.end());
	indicators.push_back(strDegrees);

	
	vector<string> strCloseness(1,"Closeness");
	vector<string> contentCloseness = vector_to_vstring(graphM.get_indicator_closeness());
	strCloseness.insert(strCloseness.end(),contentCloseness.begin(),contentCloseness.end());
	indicators.push_back(strCloseness);

	// Slow computation
	/*
	vector<string> strBetweenness(1,"Betweenness");
	vector<string> contentBetweenness = vector_to_vstring(graphM.get_indicator_betweenness());
	strBetweenness.insert(strBetweenness.end(),contentBetweenness.begin(),contentBetweenness.end());
	indicators.push_back(strBetweenness);
	*/

	data.save_csv_file(filename, indicators);
}



void LogicController::predict(const string & filename, const string & startingNode, const string & endingNode,
	const int & minLenght, const int & maxLenght, const int & maxNumPaths)
{
	int startingNodeId = translator.translate(startingNode);
	int endingNodeId = translator.translate(endingNode);

	vector<pair<double,vector<int> > > answer = PredictM.predict(graphM, pathsM,startingNodeId,endingNodeId,minLenght,maxLenght,maxNumPaths);
	
	data.save_vector_of_pair(filename,prediction_out_translation(answer));
}


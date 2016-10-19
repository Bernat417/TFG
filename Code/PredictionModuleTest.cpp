#include "PredictionModule.cpp"
#include "Translator.cpp"
#include "DataController.cpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

double failureCount,failureNOTEXISTSPROT,REcallCount,PRINTCOUNT,Outer,Inner,OuterTheory,InnerTheory;

void printPaths(vector<pair<double,vector<int> > > solution)
{
	for(int i = 0; i < solution.size(); ++i)
	{
		cout << "Fit:" <<  solution[i].first << " Path:";

		for(int j = 0; j < (solution[i].second).size(); ++j)
			cout << "-" << (solution[i].second)[j];

		cout << endl;
	}
}

void printPath(list<int> solution)
{
	for(list<int>::iterator it = solution.begin(); it != solution.end(); ++it)
		cout << "-" << *it;

	cout << endl;	
}

bool equal(vector<pair<double,vector<int> > > solA,vector<pair<double,vector<int> > > solB)
{
	bool equality = true;

	int minSize = min(solA.size(), solB.size());
	for(int i = 0; i < minSize and equality; ++i)
		if(solA[i].second != solB[i].second) equality = false;

	return equality;
}

bool is_present(const int & x, const list<int> & l)
{
	bool found = false;

	list<int>::const_iterator it;
	for(it = l.begin(); it != l.end() and not found; ++it)
		if(x==*it) found = true;

	return found;
}

bool is_present(const int & x, const vector<int> & v)
{
	bool found = false;

	for(int i = 0; i < v.size() and not found; ++i)
		if(x==v[i]) found = true;

	return found;
}

bool is_present(const vector<int> & v, const list<list<int> >& ll)
{
	bool found = false;

	list<int> l;

	for(int i = 0; i < v.size(); ++i)
		l.push_back(v[i]);

	list<list<int> >::const_iterator it;
	for(it = ll.begin(); it != ll.end() and not found; ++it)
		if(l==*it) found = true;

	return found;
}

bool contained(const vector<int> & elem, const list<list<int> > & path)
{
	bool present = false;
	if(elem.size() != path.size())
	{
		present = true;
		list<list<int> >::const_iterator it = path.begin();
		for(int i = 0; i < elem.size(); ++i, ++it)
			if(not is_present(elem[i],*it))
				present = false;
	}

	return present;
}

void basic_test(PredictionModule PredictM)
{
	vector<pair<int,int> > graph =
	{
		{0,1},
		{0,2},
		{0,3},
		{1,4},
		{2,4},
		{3,4}
	};

	vector<list<list<int> > > linkList =
	{
		{{0},{1},{4}},
		{{1},{4}},
		{{0},{2},{4}}
	};

	GraphManager graphM(graph.size(),graph);
	PathsManager pathsM(linkList);

	vector<pair<double,vector<int> > >  output= PredictM.predict(graphM,pathsM,0,4,1,3,5);

	vector<pair<double,vector<int> > > sol ={
		{(20.0/3.0 + 10.0 + 5.0)/3.0,{0,1,4}},
		{(20.0/3.0 + 10.0 + 10.0/3.0)/3.0,{0,2,4}},
		{(40.0/3.0 + 10.0/3.0)/3.0,{0,3,4}}
	};

	if(equal(output,sol))
		cout << "Test 1-1 Cleared" << endl;
	else
		cout << "Test 1-1 Failed" << endl;
	printPaths(output);

	output= PredictM.predict(graphM,pathsM,0,2,1,3,5);

	sol ={
		{(10.0/3.0+15.0/3.0)/3.0,{0,2}},
		{(10.0/3.0+5.0)/3.0,{0,1,4,2}},
		{(20.0/3.0)/3.0,{0,3,4,2}}		
	};

	if(equal(output,sol))
		cout << "Test 1-2 Cleared" << endl;
	else
		cout << "Test 1-2 Failed" << endl;
	
	

}


bool isPresent(int elem, vector<int> v)
{
	bool present = false;

	for(int i = 0; i < v.size() and not present; ++i)
		if(v[i] == elem) present = true;

	return present;
}	

list<list<int> > testPathPossibility(const int & idProt, list<list<int> >::iterator it,const int & currentSize, const int & size, list<int> currentPath,
	const vector<vector<int> > & adjList, const int & maxValidValue)
{
	currentPath.push_back(idProt);

	list<list<int> > validPaths;
	
	if(currentSize == size)
		validPaths.push_back(list<int>(currentPath));
	else if(idProt < maxValidValue)
	{	
		list<list<int> >::iterator itCopy = it;
		++itCopy;
		list<int>::iterator it2;
		 
		for(it2 = (*itCopy).begin(); it2 != (*itCopy).end(); ++it2)
		{
			if(is_present(*it2, adjList[idProt]))
			{
				list<list<int> > expanded = testPathPossibility(*it2,itCopy,currentSize+1,size,currentPath,adjList,maxValidValue);
				validPaths.merge(expanded);
			}
		}
	}

	currentPath.pop_back();
	return validPaths;
}
/*

void analysis_test(PredictionModule PredictM)
{
	PathsManager pathsM;
	GraphManager graphM;
	DataController data;
	Translator translator;

	//// Graph GEN
	string name = "network_binary_9606_2015_02.txt";
	vector<pair<string,string> > graphLinksList;
	graphLinksList = data.read_graph_link_list(name);

	for(int i = 0; i < graphLinksList.size();++i)
	{
		translator.add(graphLinksList[i].first);
		translator.add(graphLinksList[i].second);
	}		
	
	graphM = GraphManager (translator.get_num_ids(),translator.translate(graphLinksList));

	int graphValidIdMax = translator.get_num_ids();

	//// Path GEN
	name = "CMapDirectedconnected_paths.txt";
	vector<list<list<string> > > pathList;
	pathList = data.read_path_list(name);
	
	list<list<string>>::iterator it;

	for(int i = 0; i < pathList.size();++i)
		for(it = pathList[i].begin(); it != pathList[i].end(); ++it)
				translator.add(*it);

	vector<list<list<int> > > transPathList = translator.translate(pathList);

	cout << "SIZE1 " << transPathList.size() << endl;

	int totalPaths = pathList.size();
	int numTestPaths= totalPaths/1000.0;
	int numReducedPaths = totalPaths- numTestPaths;
	vector<int> testPathsSel;


	for(int i = 0; i < numTestPaths; ++i)
	{
		int chosenPath = rand()%totalPaths;
		
		while(isPresent(chosenPath, testPathsSel))
			chosenPath = rand()%totalPaths;

		testPathsSel.push_back(chosenPath);
	}

	//Subset
	vector<list<list<int> > > reducedPathsList;
	vector<list<list<int> > > testPathsList;

	for(int i = 0; i < transPathList.size();++i)
	{
		if(isPresent(i, testPathsSel))
			testPathsList.push_back(transPathList[i]);
		else
			reducedPathsList.push_back(transPathList[i]);
	}
	numTestPaths= totalPaths/1000.0;
	
	pathsM = PathsManager(reducedPathsList);



	//Bucle TEST

	vector<pair<pair<int,int>,pair<double,bool> > > presentList;
	vector<vector<int> > adjList = graphM.get_adjacency_list();
	int allPresentCounter = 0;
	int notAllPresentCounter = 0;

	int allLinkPresentCounter = 0;
	int notLinkAllPresentCounter = 0;
	int possiblePathCounter = 0;
	int possiblePaths = 0;
	int singlePathPossible = 0;

	int searchSize = 100;

	int foundCounter = 0;
	int notfoundMaxSizeCounter = 0;

	int topTenPercentCounter = 0;
	int topTwentyFivePercentCounter = 0;
	int topFiftyPercentCounter = 0;

	int lessThanTenCounter = 0;

	int TopTenCounter = 0;
	int foundCounterBigger = 0;

	double upperAccPosition = 0;
	double lowerAccPosition = 0;

	int fitnessValueZeroFifty = 0;
	int fitnessValueZeroBelowFifty = 0;


	list<list<int> > l;

	cout << pathsM.num_paths() << endl;

	for(int i = 0; i < testPathsList.size(); ++i)
	{
		list<list<int> >::iterator it,it2;
		list<int>::iterator it3,it4;


		//All proteins present?
		bool allPresent = true;
		for(it = testPathsList[i].begin(); it != testPathsList[i].end(); ++it)
			for(it3 = (*it).begin(); it3 != (*it).end(); ++it3)
				if(graphValidIdMax <= *it3) ++notAllPresentCounter;
				else ++allPresentCounter;


		//Links Present?		
		for(it = testPathsList[i].begin(), it2 = it, ++it2; it2 != testPathsList[i].end(); ++it,++it2)
			for(it3 = (*it).begin(); it3 != (*it).end(); ++it3)
				for(it4 = (*it2).begin(); it4 != (*it2).end(); ++it4)
				{
					if(*it3 >= graphValidIdMax or *it4 >= graphValidIdMax)
						++notLinkAllPresentCounter;
					else if(not is_present(*it4, adjList[*it3]))
						++notLinkAllPresentCounter;
					else
						++++allLinkPresentCounter;
				}

		it = testPathsList[i].begin();

		//Test Prediction Validity 
		int numPathsPossibleA = 0;

		set<pair<int,int> > pairIniciFiPossible;
		list<list<int> > validUncompressedPaths;
		for(it3 = (*it).begin(); it3 != (*it).end(); ++it3)
		{
			it2 = it;
			validUncompressedPaths.merge(testPathPossibility(*it3, it2, 0, testPathsList[i].size()-1, list<int>() , adjList,graphValidIdMax));
			numPathsPossibleA += (validUncompressedPaths).size();
			

			for(it2 = validUncompressedPaths.begin(); it2 != validUncompressedPaths.end(); ++it2)
				pairIniciFiPossible.insert(make_pair((*it2).front(), (*it2).back()));
		}
		possiblePathCounter += numPathsPossibleA;

		if(numPathsPossibleA > 0)
		{

			list<int> startingProt = testPathsList[i].front();
			list<int> endingProt =  testPathsList[i].back();

			list<int>::iterator itStart;
			list<int>::iterator itEnd;

			for(itStart = startingProt.begin(); itStart != startingProt.end(); ++itStart)
				for(itEnd = endingProt.begin(); itEnd != endingProt.end(); ++itEnd)
					if(pairIniciFiPossible.find(make_pair(*itStart,*itEnd)) != pairIniciFiPossible.end())
					{
						cout << "Path "<< i << '/' << (testPathsList.size()-1) << " - predicting " << *itStart << " - > " << *itEnd << endl;
						vector<pair<double,vector<int> > > answer = PredictM.predict(graphM,pathsM,*itStart,*itEnd,
							(testPathsList[i].size()-1),(testPathsList[i].size()-1),searchSize);
						bool presence = false;
						double diffLenght = 0;

						for(int j = 0; j < answer.size() and not presence; ++j)
						{
							if(is_present(answer[j].second, validUncompressedPaths))
							{
								cout << "Found in position: " << j << " out of " << answer.size() << endl;
								double upperPercent = double(j)/double(answer.size());
								upperAccPosition += upperPercent;
								double lowerPercent = double(j+1)/double(answer.size());
								lowerAccPosition += lowerPercent;
								
								
								cout << "POSITION = " << upperPercent << endl;
								presence = true;
								++foundCounter;
								if(answer.size() >= 0)
								{
									++foundCounterBigger;
									if(upperPercent <= 0.10)
										++topTenPercentCounter;
									else if(upperPercent <= 0.25)
										++topTwentyFivePercentCounter;
									else if(upperPercent <= 0.50)
									{
										if(answer[j].first == 0)
											++fitnessValueZeroFifty;			

										++topFiftyPercentCounter;
									}
									else if(answer[j].first == 0)
										++fitnessValueZeroBelowFifty;
								}

								if(j < 10)
									++TopTenCounter;
							}
						}
						if(presence)
						{
							
							cout << "FOUND "<< answer.size() << " Possible Paths: "<< pairIniciFiPossible.size()<<endl;
							cout << fitnessValueZeroFifty << " - "<< fitnessValueZeroBelowFifty << endl;
						}
						else	
						{
							cout << "NOT FOUND " <<  answer.size() << " Possible Paths: "<< pairIniciFiPossible.size()<<endl;
							if(answer.size() == searchSize)++notfoundMaxSizeCounter;
						}
						
						presentList.push_back({{*itStart,*itEnd},{diffLenght/* /double(answer.size()) */ /* ,presence}});
					}

		}
		

		
	}
	

	double upperMeanPosition = upperAccPosition/double(foundCounterBigger);
	double lowerMeanPosition = 1.0 - lowerAccPosition/double(foundCounterBigger);
	double foundPercentage = double(foundCounter)/double(possiblePathCounter);
	double notFoundTooManyPercentage = double(notfoundMaxSizeCounter)/double(testPathsList.size());

	cout << "Present " << allPresentCounter << " Not present " << notAllPresentCounter << endl;
	cout << "LINK Present " << allLinkPresentCounter << " LINK Not present " << notLinkAllPresentCounter << endl;
	cout << "Possible Paths " << possiblePathCounter << endl;

	cout << "Found Percentage: " << foundPercentage<<endl;
	cout << "Not Found Too Many Percentage: " << notFoundTooManyPercentage<<endl;
	cout << "Upper Mean Possition: " << upperMeanPosition<<endl;
	cout << "Lower Mean Possition: " << lowerMeanPosition<<endl;

	cout << "Top Ten Percent Ocurrences: " << topTenPercentCounter<< endl;
	cout << "Top Twenty Five Percent Ocurrence: " << topTwentyFivePercentCounter<< endl;	
	cout << "Top Fifity Percent Ocurrences: " << topFiftyPercentCounter << endl;

	cout << "Top Ten Percent Percentage: " << double(topTenPercentCounter)/ double(foundCounter) << endl;
	cout << "Top Twenty Five Percent Percentage: " << double(topTwentyFivePercentCounter)/ double(foundCounter) << endl;	
	cout << "Top Fifity Percent Percentage: " << double(topFiftyPercentCounter)/ double(foundCounter) << endl;

	cout << "fitness Value Zero Fifty: " <<fitnessValueZeroFifty << endl;
	cout << "fitness Value Zero Below Fifty: " <<fitnessValueZeroBelowFifty << endl;

	cout << "Total Ocurrences: " << foundCounter << endl;
	cout << "LessThanTen Ocurrences: "<<lessThanTenCounter << endl;
	cout << "Between the First Ten: " << TopTenCounter << endl;

}
*/

void testPathPossibilityTest(PredictionModule PredictM)
{
		vector<vector<int> > graphTestP =
	{
		{},
		{2,3,4},
		{1,3,4},
		{1,2,4,5},
		{1,2,3},
		{3,6,7,8},
		{5,9},
		{5,11},
		{5,10},
		{6,11},
		{8,11},
		{7,9,10}

	};

	list <list <int> > pathTestP =
	{
		{1},
		{2,3,4,9},
		{3,5,6},
		{5,6,7},
		{9,11,8}
	};

	list<list<int> > answerPT;
	list<list<int> >::iterator itPT = pathTestP.begin();

	answerPT= testPathPossibility(1, itPT, 1, pathTestP.size(), list<int>() , graphTestP,2000);

	for(list<list<int> >::iterator itprint1 = answerPT.begin(); itprint1 != answerPT.end(); ++itprint1)
	{
		for(list<int>::iterator itprint2 = (*itprint1).begin();itprint2 != (*itprint1).end();++itprint2)
			cout << *itprint2 << ' ';
		cout << endl;
	}	

}



int main()
{
	PredictionModule PredictM;

	basic_test(PredictM);
	//analysis_test(PredictM);
}
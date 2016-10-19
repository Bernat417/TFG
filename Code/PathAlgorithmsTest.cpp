#include "PathsAlgorithms.cpp"
#include <iostream>
using namespace std;

bool double_equals(double a, double b, double epsilon = 0.001)
{
    return std::abs(a - b) < epsilon;
}

void basicTests(PathsAlgorithms pAlg)
{
	cout << "Basic Tests Batery" << endl;
	
	vector<vector<int> > paths_1 =
	{
		{1,2},
		{3,4},
		{5,6},
		{7,8}
	};


	//Basic Test 1
	vector<int> path = {1,2,3,5,7};

	if(double_equals(pAlg.similarity_index_calc(path, paths_1), 7.0))
		cout << "Basic Test 1 Cleared" << endl;
	else
		cout << "Basic Test 1 Failed" << endl;
	
	//Basic Test 2
	path = {1,2,3,4};

	if(double_equals(pAlg.similarity_index_calc(path, paths_1),2.5))
		cout << "Basic Test 2 Cleared" << endl;
	else
		cout << "Basic Test 2 Failed" << endl;


	//Basic Test 3
	path = {0,0,0,0};

	if(double_equals(pAlg.similarity_index_calc(path, paths_1),0.0))
		cout << "Basic Test 3 Cleared" << endl;
	else
		cout << "Basic Test 3 Failed" << endl;


	//Basic Test 4
	path = {1,2};

	if(double_equals(pAlg.similarity_index_calc(path, paths_1),2.5))
		cout << "Basic Test 4 Cleared" << endl;
	else
		cout << "Basic Test 4 Failed" << endl;


		vector<vector<int> > paths_2 =
	{
		{1,2},
		{3,4},
		{5,6},
		{7,8},
		{9,10},
		{11,12},
		{13,14},
		{15,16}
	};


	//Basic Test 5
	path = {1,7,11,16};

	if(double_equals(pAlg.similarity_index_calc(path, paths_2),5.0))
		cout << "Basic Test 5 Cleared" << endl;
	else
		cout << "Basic Test 5 Failed" << endl;


	//Basic Test 6
	path = {0,0,0};

	if(double_equals(pAlg.similarity_index_calc(path, paths_2),0.0))
		cout << "Basic Test 6 Cleared" << endl;
	else
		cout << "Basic Test 6 Failed" << endl;

		vector<vector<int> > paths_3 =
	{
		{1,2},
		{3,4,1},
		{5,6},
		{7,8},
		{9,10},
		{11,12},
		{13,14},
		{15,16},
		{17,18},
		{20}
	};


	//Basic Test 7
	path = {1,2,3};

	if(double_equals(pAlg.similarity_index_calc(path, paths_3),2.0))
		cout << "Basic Test 7 Cleared" << endl;
	else
		cout << "Basic Test 7 Failed" << endl;


	


}



int main()
{
	PathsAlgorithms pAlg;

	basicTests(pAlg);
	
}
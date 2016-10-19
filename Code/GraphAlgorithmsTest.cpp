#include "GraphAlgorithms.cpp"
#include <iostream>

using namespace std;

bool printSolutions;


bool present(const vector<int> & elem, const vector<vector<int> > & container)
{
	for(int i = 0; i < container.size(); ++i)
		if(container[i] == elem)return true;
	
	return false;
}

void printPaths(vector<vector<int> > solution)
{
	for(int i = 0; i < solution.size(); ++i)
	{
		for(int j = 0; j < solution[i].size(); ++j)
			cout << "-" << solution[i][j];

		cout << endl;
	}
}

bool same_elements(const vector<vector<int> > & a,const vector<vector<int> > & b)
{
	for(int i = 0; i < a.size(); ++i)
		if(not present(a[i],b)) return false;

	for(int i = 0; i < b.size(); ++i)
		if(not present(b[i],a)) return false;

	return true;
}

void test1(GraphAlgorithms & gAlg)
{
	vector<vector<int> > graph =
	{
		{1},
		{0,2},
		{1}
	};

	vector<vector<int> > sol =
	{
		{0,1,2}
	};

	if(printSolutions)
	{
	  cout << "Answer: "<< endl;
	  printPaths(gAlg.rnd_cropped_paths_DFS(0,2,2,2,1,graph));
	  cout << "Sol: "<< endl;
	  printPaths(sol);
	}
	
	if(same_elements(gAlg.rnd_cropped_paths_DFS(0,2,2,2,1,graph),sol))
		cout << "Test 1 Cleared" << endl;
	else
		cout << "Test 1 Failed" << endl;
}

void test2(GraphAlgorithms & gAlg)
{
	vector<vector<int> > graph =
	{
		{1,2,3},
		{0,4},
		{0,4},
		{0,4},
		{1,2,3}
	};


	vector<vector<int> > sol1 =
	{
		{0,1},
		{0,2,4,1},
		{0,3,4,1}
	};
	
	if(printSolutions)
	{
	  cout << "Answer: "<< endl;
	  printPaths(gAlg.rnd_cropped_paths_DFS(0,1,1,3,10,graph));
	  cout << "Sol: "<< endl;
	  printPaths(sol1);
	}
	
	if(same_elements(gAlg.rnd_cropped_paths_DFS(0,1,1,3,10,graph),sol1))
		cout << "Test 2-1 Cleared" << endl;
	else
		cout << "Test 2-1 Failed" << endl;

	vector<vector<int> > sol2 =
	{
		{0,2},
		{0,1,4,2},
		{0,3,4,2}
	};
	if(printSolutions)
	{
	  cout << "Answer: "<< endl;
	  printPaths(gAlg.rnd_cropped_paths_DFS(0,2,1,3,10,graph));
	  cout << "Sol: "<< endl;
	  printPaths(sol2);
	}
	  

	if(same_elements(gAlg.rnd_cropped_paths_DFS(0,2,1,3,10,graph),sol2))
		cout << "Test 2-2 Cleared" << endl;
	else
		cout << "Test 2-2 Failed" << endl;


	vector<vector<int> > sol3 =
	{
		{0,3},
		{0,1,4,3},
		{0,2,4,3}
	};

	if(printSolutions)
	{
	  cout << "Answer: "<< endl;
	  printPaths(gAlg.rnd_cropped_paths_DFS(0,3,1,3,10,graph));
	  cout << "Sol: "<< endl;
	  printPaths(sol3);
	}
	
	if(same_elements(gAlg.rnd_cropped_paths_DFS(0,3,1,3,10,graph),sol3))
		cout << "Test 2-3 Cleared" << endl;
	else
		cout << "Test 2-3 Failed" << endl;


	vector<vector<int> > sol4 =
	{
		{0,1,4},
		{0,2,4},
		{0,3,4}
	};

	if(printSolutions)
	{
	  cout << "Answer: "<< endl;
	  printPaths(gAlg.rnd_cropped_paths_DFS(0,4,2,2,10,graph));
	  cout << "Sol: "<< endl;
	  printPaths(sol4);
	}
	
	if(same_elements(gAlg.rnd_cropped_paths_DFS(0,4,2,2,10,graph),sol4))
		cout << "Test 2-4 Cleared" << endl;
	else
		cout << "Test 2-4 Failed" << endl;

}


void test3(GraphAlgorithms & gAlg)
{
	vector<vector<int> > graph =
	{
		{1,2},
		{0,3},
		{0,3},
		{1,2,4,5},
		{3,6},
		{3,6},
		{4,5}
	};

	vector<vector<int> > sol1 =
	{
		{0,1,3},
		{0,2,3}
	};

	if(printSolutions)
	{
	  cout << "Answer: "<< endl;
	  printPaths(gAlg.rnd_cropped_paths_DFS(0,3,1,5,10,graph));
	  cout << "Sol: "<< endl;
	  printPaths(sol1);
	}
	
	if(same_elements(gAlg.rnd_cropped_paths_DFS(0,3,1,5,10,graph),sol1))
		cout << "Test 3-1 Cleared" << endl;
	else
		cout << "Test 3-1 Failed" << endl;

	vector<vector<int> > sol2 =
	{
		{0,1,3,4,6},
		{0,1,3,5,6},
		{0,2,3,4,6},
		{0,2,3,5,6}
	};

	if(printSolutions)
	{
	  cout << "Answer: "<< endl;
	  printPaths(gAlg.rnd_cropped_paths_DFS(0,6,1,5,10,graph));
	  cout << "Sol: "<< endl;
	  printPaths(sol2);
	}
	
	if(same_elements(gAlg.rnd_cropped_paths_DFS(0,6,1,5,10,graph),sol2))
		cout << "Test 3-2 Cleared" << endl;
	else
		cout << "Test 3-2 Failed" << endl;

}


void randomTests(GraphAlgorithms gAlg)
{
	vector<vector<int> > graph =
	{
		{1},
		{0,2},
		{1}
	};

}


int main()
{
	printSolutions = false;
	
	GraphAlgorithms gAlg;

	test1(gAlg);	
	test2(gAlg);
	test3(gAlg);
	randomTests(gAlg);
}
#include "PathsAlgorithms.hpp"

bool PathsAlgorithms::isPresent(int x, vector<int> v)
{
	bool found = false;

	for(int i = 0; i < v.size() and not found; ++i)
		if(x==v[i]) found = true;

	return found;
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

void printPaths(vector<int > solution)
{
	for(int i = 0; i < solution.size(); ++i)
	{
		cout << "-" << solution[i];

		cout << endl;
	}
}


double PathsAlgorithms::similarity_index(const vector<int> & path,
	const vector<vector<vector<int> > > & paths)
/* This function computes a similarity index between a path and a vector of compressed paths */
{
	double score = 0.0;

	for(int i = 0; i < paths.size(); ++i)
	{
		if(abs(int(path.size()) - int(paths[i].size())) < 2)
		{
			score += similarity_index_calc(path, paths[i]);
		}

	}

    return score;
}

double PathsAlgorithms::similarity_index_calc(const vector<int> & pathA, 
	const vector< vector<int> > & pathB)
/* This function computes a similarity index between two paths. 
The more they overlap, the higher the score*/
{
	double score = 0.0;
	int i,j;
	i = 1;
	j = 0;
	double divSizeA = 1.0/pathA.size();
	double divSizeB = 1.0/pathB.size();
	bool advA, adbB = false;

	while(i < pathA.size() or j < pathB.size())
	{
		if(i*divSizeA >= j*divSizeB)
		{
			if(isPresent(pathA[i-1],pathB[j]))
			{	
				if(i*divSizeA >= (j+1)*divSizeB)
					score += 1;
				else if(isPresent(pathA[i-1],pathB[j]))
					score += (i*divSizeA - j*divSizeB)/divSizeB;
			}
			++j;		
			
		}
		else 
		{
			if(isPresent(pathA[i],pathB[j-1]))
			{
				if((i+1)*divSizeA >= j*divSizeB)
					score += (j*divSizeB - i*divSizeA)/divSizeB;
				else if(isPresent(pathA[i],pathB[j]))
					score += ((i+1)*divSizeA - i*divSizeA)/divSizeB;
			}
			++i;
			
		}
	}

	score= score*10 / pathB.size();

	return score;
}


#include "PathsManager.hpp"

/**
 * This class handles the management of the paths data structure and algorithms.
 */

PathsManager::PathsManager()
{
	paths = Paths();
	PathsAlgorithms pathsAlgorithms();
}


PathsManager::PathsManager(const vector<list<list<int> > > & pathList)
{
	paths = Paths(pathList);
	PathsAlgorithms pathsAlgorithms();
}

double PathsManager::num_paths()
{
	return paths.num_paths();
}

double PathsManager::similarity_index(const vector<int> & path)
{
	return pathsAlgorithms.similarity_index(path,paths.paths);
}
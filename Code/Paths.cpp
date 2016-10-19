#include "Paths.hpp"


Paths::Paths()
{
    paths = vector<vector<vector<int> > >();
}

Paths::Paths(const vector<list<list<int> > > & pathList)
{
    paths= vector<vector<vector<int> > >(pathList.size());

    list<list<int>>::const_iterator it;
    list<int>::const_iterator it2;

    for(int i = 0; i < pathList.size();++i)
    {
        int pos = 0;
        vector<vector<int> > path(pathList[i].size());

        for(it = pathList[i].begin(); it != pathList[i].end(); ++it)
        {
            int pos2 = 0;
            vector<int> stepElements( (*it).size() );

            for(it2 = (*it).begin(); it2 != (*it).end(); ++it2)
            {
                stepElements[pos2++] = *it2;
            }

            path[pos++]=stepElements;
        }
        paths[i] = path;
    }

}   


vector<int> Paths::stage_nodes(int numPath, int index)
{
    vector<int> nodes(paths[numPath][index].size());
    
    for( int i = 0; i <paths[numPath][index].size(); ++i)
        nodes.push_back(paths[numPath][index][i]);
    
    return nodes;
}

int Paths::path_lenght(int numPath)
{
    return paths[numPath].size();
}


int Paths::num_paths()
{
    return paths.size();
}


void Paths::add_path(const list< list <int> > & path)
{
    vector<vector<int> > newPath(path.size());

    list<list<int>>::const_iterator it;
    list<int>::const_iterator it2;
    int pos = 0;

    for(it = path.begin(); it != path.end(); ++it)
    {
        int pos2 = 0;
        vector<int> stepElements( (*it).size() );

        for(it2 = (*it).begin(); it2 != (*it).end(); ++it2)
            stepElements[pos2++] = *it2;

        newPath[pos++]=stepElements;
    }

    paths.push_back(newPath);
}

list<int> Paths::find_path_with_element(int id)
{
    list<int> l;
     for(int i = 0; i < paths.size(); ++i)
        for(int j = 0; j < paths[i].size(); ++j)
        {
            bool found = false;
            for(int k = 0; (k < paths[i][j].size()) && (not found); ++k)
                if(paths[i][j][k] == id) found = true;
            if(found) l.push_back(j);
        }

    return l;
}

vector<vector<int> > Paths::get_path(int i)
{
    vector<vector<int> > pathC(paths[i].size());
    
    for(int j = 0; j < paths[i].size(); ++j)
    {
        vector<int> v(paths[i][j].size());
        
        for(int k = 0; k < paths[i][j].size(); ++k)
            v[k] = paths[i][j][k];

        pathC[j] = v;
    }

    return pathC;
}

//canviar per getters

vector<int> Paths::get_path_lenght()
{
    vector<int> v(paths.size());

    for(int i = 0; i < paths.size(); ++i)
        v[i] = path_lenght(i);

    return v;
}

vector<vector<vector<int> > > Paths::get_paths()
/*PRE: */
/*POST:*/
{
    vector<vector<vector<int> > > pathsCopy (paths.size());
    for(int i = 0; i < paths.size(); ++i)
        pathsCopy[i] = get_path(i);
        
}
                            
#include "Translator.hpp" 
#include <stdexcept>


Translator::Translator()
{
	nameToId = map<string,int>();
	idToName = vector<string>();
}


void Translator::add(string name)
{
	if(name.empty())
		throw invalid_argument("void name");

	if(nameToId.find(name)==nameToId.end())
    {
        string s(name);
        nameToId.insert(pair<string,int> (s,nameToId.size()));
        idToName.push_back(s);
    }
}


void Translator::add(const vector<string> & name_vector)
{	
	for(int i = 0; i < name_vector.size(); ++i)
		add(name_vector[i]);
}

void Translator::add(const list<string> & name_list)
{	
	list<string>::const_iterator it;

	for(it = name_list.begin(); it != name_list.end(); ++it)
		add(*it);
}

int Translator::get_num_ids()
{
	return idToName.size();
}


bool Translator::present_name(string name)
{
	if(name.empty())
		throw invalid_argument("void name");

	return not (nameToId.find(name)==nameToId.end());
}


bool Translator::all_present_names(const vector<string> & name_vector)
{
	bool allPresent;

	for(int i = 0; (i < name_vector.size()) and allPresent; ++i)
		allPresent = allPresent and present_name(name_vector[i]);

	return allPresent;
}


int Translator::translate(const string name)
{
	if(nameToId.find(name)==nameToId.end()) 
		throw invalid_argument("key not found");

	return nameToId[name];
}


vector<int> Translator::translate(const vector<string> & name_vector)
{
	vector<int> translation(name_vector.size());

	for(int i = 0; i < name_vector.size(); ++i)
		translation[i] =  translate(name_vector[i]);
	
	return translation;
}


string Translator::translate(const int id)
{
	if(id >= idToName.size())
		throw invalid_argument("id not found");

	return string(idToName[id]);
}


vector<string> Translator::translate(const vector<int> & id_vector)
{
	vector<string> translation(id_vector.size());

	for(int i = 0; i < id_vector.size(); ++i)
		translation[i] =  translate(id_vector[i]); 

	return translation;
}


vector<pair<int,int> > 
Translator::translate(const vector<pair<string,string> > & name_vector_pair)
{
	vector<pair<int,int> >  translation(name_vector_pair.size(), pair<int,int>());

	for(int i = 0; i < name_vector_pair.size(); ++i)
	{
		translation[i].first =  translate(name_vector_pair[i].first); 
		translation[i].second =  translate(name_vector_pair[i].second);
	}

	return translation;
}


vector<list<list<int > > >
Translator::translate(const vector<list<list<string > > > & name_vector_ll)
{
	vector<list<list<int > > >  translation(name_vector_ll.size());
	list<list<string> >::const_iterator it;
	list<string>::const_iterator it2;
	
	for(int i = 0; i < name_vector_ll.size(); ++i)
	{
		
		list<list<int > > partialTranslation; 
		

		for(it = name_vector_ll[i].begin(); it != name_vector_ll[i].end(); ++it)
		{
			list<int > currentList;

			for(it2 = (*it).begin(); it2 != (*it).end(); ++it2)
				currentList.push_back(translate(*it2));

			partialTranslation.push_back(currentList);
		}

		translation[i] =partialTranslation;
	}

	return translation;
}

vector<string> 
Translator::get_names()
{
	vector <string> nameList(idToName.size());

	for(int i =0; i < idToName.size(); ++i)
		nameList[i] = string(idToName[i]);

	return nameList;
}



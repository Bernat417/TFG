#include <map>
#include <list>
#include <iostream>

using namespace std;

/**
 * This class handles the translation between the protein names and the system ids.
 */

class Translator
{
	public:

	/**PRE: -
	  *POST: Returns a translator instance with the internal structures 
	  * initialized.*/		
	Translator();
	

	/**PRE: -
	  *POST: Adds an entry to the translation table for the name if it's not 
	  * present yet.*/
	void add(string name);

	/**PRE: -
	  *POST: Adds an entry to the translation table for every name in the vector
	  * if it's not present yet.*/
	void add(const vector<string> & name_vector);
	
	/**PRE: -
	  *POST: Adds an entry to the translation table for every name in the list
	  * if it's not present yet.*/
	void add(const list<string> & name_list);

	/**PRE: -
	  *POST: Returns the number of ids.*/
	int get_num_ids();

	
	/**PRE: -
	  *POST: Returns true if the name is present in the translation table,
	  * else false.*/
	bool present_name(string name);
	

	/**PRE: -
	  *POST: Returns true if every name in the name_vector is present in the
	  * translation table, else false.*/
	bool all_present_names(const vector<string> & name_vector);
	

	/**PRE: The name is present in the translation table
	  *POST: Returns the id of the name.*/
	int translate(const string name);
	
	
	/**PRE: The names are present in the translation table
	  *POST: Returns the id of the names in the vector.*/
	vector<int> translate(const vector<string> & name_vector);
	

	/**PRE: The identifier is present in the translation table
	  *POST: Returns the name of the id.*/
	string translate(const int id);
	

	/**PRE: The identifiers are present in the translation table
	  *POST: Returns the names of the ids in the vector.*/
	vector<string> translate(const vector<int> & id_vector);
	

	/**PRE: The identifiers are present in the translation table
	  *POST: Returns the names of the ids in the pair vector.*/
	vector<pair<int,int> > translate(const vector<pair<string,string> > & name_vector_pair);

	/**PRE: The identifiers are present in the translation table
	  *POST: Returns the names of the ids in the vector of lists of lists.*/
	vector<list<list<int > > > translate(const vector<list<list<string > > > & name_vector_ll);

	/**PRE: 
	  *POST: Returns the names of all the elements int the translator.*/
	vector<string> get_names();

	private:

	///We use this structure to translate from name to id	
	map<string,int> nameToId;
	
	///We use this structure to translate from id to name
	vector<string> idToName;
	
};

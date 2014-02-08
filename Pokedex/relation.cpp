/*File description: relation.cpp defines all member functions
declared in relation.h*/

#include "relation.h"

Relation Relation::natural_join(Relation table)
{
	
}

Relation Relation::cross_product(string new_table_name, Relation other_table)
{
	vector<string> new_attr_names;
	vector<string> new_attr_types;
	vector<int> new_key_pos;

	//Get key positions from the two tables being worked on and put them all into vector new_key_pos
	new_key_pos = key_pos;
	new_key_pos.insert(new_key_pos.end(), other_table.key_pos.begin(), other_table.key_pos.end());

	//Add names and types of attributes from the first table to the new table's names and types vectors
	for (int i = 0; i < attr_names.size(); i++)
	{
		new_attr_names.push_back(attr_names[i]);
		new_attr_types.push_back(attr_types[i]);
	}

	//Add names and types of attributes from the second table to the new table's names and types vectors
	for (int i = 0; i < other_table.attr_names.size(); i++)
	{
		new_attr_names.push_back(other_table.attr_names[i]);
		new_attr_types.push_back(other_table.attr_types[i]);
	}

	//Create new table that will hold the cross product of the two old tables
	Relation cp_table(new_table_name, new_attr_names, new_attr_types, new_key_pos);

	//Populate new cross product table
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < other_table.table.size(); j++)
		{
			vector<string> temp;
			temp = table[i];
			temp.insert(temp.end(), other_table.table[j].begin(), other_table.table[j].end());
			insert_row(temp);
		}
	}
}
/*File description: relation.cpp defines all member functions
declared in relation.h*/

#include "relation.h"

Relation Relation::natural_join(string new_table_name, Relation other_table)
{
	vector<string> new_attr_names;
	vector<string> new_attr_types;
	vector<int> new_key_pos;
	string repeat = " ";
	int orig_repeated_pos;
	int repeat_pos = -1;

	if (table.size >= other_table.table.size())
	{

		//Find that attribute that is repeated
		for (int i = 0; i < attr_names.size(); i++)
		{
			for (int j = 0; j < other_table.attr_names.size(); j++)
			{
				if ((attr_names[i].compare(other_table.attr_names[j]) == 0))
				{
					repeat = attr_names[i];
					repeat_pos = j;
					orig_repeated_pos = i;
					break;
				}
			}
			if (repeat_pos != -1)
				break;
		}


		//Find the key locations for the new Relation
		new_key_pos = key_pos;

		vector<int> temp_keys = other_table.key_pos;

		for (int i = 0; i < other_table.key_pos.size(); i++)
		{

			if (other_table.key_pos[i] == repeat_pos)
			{
				temp_keys.erase(temp_keys.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < temp_keys.size(); i++)
			temp_keys[i] += key_pos.size();

		new_key_pos.insert(new_key_pos.end(), temp_keys.begin(), temp_keys.end());

		//Add names and types of attributes from the first table to the new table's names and types vectors
		new_attr_names = attr_names;
		new_attr_types = attr_types;

		//Add names and types of attributes from the second table to the new table's names and types vectors
		vector<string> temp_names = other_table.attr_names;
		vector<string> temp_types = other_table.attr_types;

		temp_names.erase(temp_names.begin() + repeat_pos);
		temp_types.erase(temp_types.begin() + repeat_pos);

		new_attr_names.insert(new_attr_names.end(), temp_names.begin(), temp_names.end());
		new_attr_types.insert(new_attr_types.end(), temp_types.begin(), temp_types.end());


		//Create new Relation to hold the natural join of the two old Relations 
		Relation nj_table(new_table_name, new_attr_names, new_attr_types, new_key_pos);


		//Create and insert the new rows of the Relation
		for (int i = 0; i < table.size(); i++)
		{
			vector<string> temp_row;
			vector<string> temp_second;
			temp_row = table[i];
			for (int j = 0; j < other_table.table.size(); j++)
			{
				if (table[i][orig_repeated_pos].compare(other_table.table[j][repeat_pos]) == 0)
				{
					temp_second = other_table.table[j];
					temp_second.erase(temp_second.begin() + repeat_pos);
					temp_row.insert(temp_row.end(), temp_second.begin(), temp_second.end());
					nj_table.insert_row(temp_row);
				}
			}
		}
	}
	else
	{
		//Find that attribute that is repeated
		for (int i = 0; i < other_table.attr_names.size(); i++)
		{
			for (int j = 0; j < attr_names.size(); j++)
			{
				if ((other_table.attr_names[i].compare(attr_names[j]) == 0))
				{
					repeat = other_table.attr_names[i];
					repeat_pos = j;
					orig_repeated_pos = i;
					break;
				}
			}
			if (repeat_pos != -1)
				break;
		}


		//Find the key locations for the new Relation
		new_key_pos = other_table.key_pos;

		vector<int> temp_keys = key_pos;

		for (int i = 0; i < key_pos.size(); i++)
		{

			if (key_pos[i] == repeat_pos)
			{
				temp_keys.erase(temp_keys.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < temp_keys.size(); i++)
			temp_keys[i] += key_pos.size();

		new_key_pos.insert(new_key_pos.end(), temp_keys.begin(), temp_keys.end());

		//Add names and types of attributes from the first table to the new table's names and types vectors
		new_attr_names = other_table.attr_names;
		new_attr_types = other_table.attr_types;

		//Add names and types of attributes from the second table to the new table's names and types vectors
		vector<string> temp_names = attr_names;
		vector<string> temp_types = attr_types;

		temp_names.erase(temp_names.begin() + repeat_pos);
		temp_types.erase(temp_types.begin() + repeat_pos);

		new_attr_names.insert(new_attr_names.end(), temp_names.begin(), temp_names.end());
		new_attr_types.insert(new_attr_types.end(), temp_types.begin(), temp_types.end());


		//Create new Relation to hold the natural join of the two old Relations 
		Relation nj_table(new_table_name, new_attr_names, new_attr_types, new_key_pos);


		//Create and insert the new rows of the Relation
		for (int i = 0; i < other_table.table.size(); i++)
		{
			vector<string> temp_row;
			vector<string> temp_second;
			temp_row = other_table.table[i];
			for (int j = 0; j < table.size(); j++)
			{
				if (other_table.table[i][orig_repeated_pos].compare(table[j][repeat_pos]) == 0)
				{
					temp_second = table[j];
					temp_second.erase(temp_second.begin() + repeat_pos);
					temp_row.insert(temp_row.end(), temp_second.begin(), temp_second.end());
					nj_table.insert_row(temp_row);
				}
			}
		}
	}



	
}

Relation Relation::cross_product(string new_table_name, Relation other_table)
{
	vector<string> new_attr_names;
	vector<string> new_attr_types;
	vector<int> new_key_pos;

	//Get key positions from the two tables being worked on and put them all into vector new_key_pos
	new_key_pos = key_pos;
	vector<int> temp_keys = other_table.key_pos;
	for (int i = 0; i < temp_keys.size(); i++)
		temp_keys[i] += key_pos.size();

	new_key_pos.insert(new_key_pos.end(), temp_keys.begin(), temp_keys.end());

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

	//Create new Relation that will hold the cross product of the two old Relaions
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
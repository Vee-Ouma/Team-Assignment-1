/*File description: relation.cpp defines all member functions
declared in relation.h*/

#include "relation.h"

/*------------------- Row Operations -------------------*/

void Relation::insert_row(vector<string> value_list)
{
	table.push_back(value_list);
}

void Relation::delete_row(vector<string> key_list)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (check_row(table[i], key_list))
		{
			table.erase(table.begin() + i);
			break;
		}
	}
}

/*----------------- Column Operations ------------------*/

void Relation::insert_column(vector<string> value_list, string name, string type)
{
	if (table.size() == 0)
	{
		vector<string> temp;
		for (int i = 0; i < value_list.size(); i++)
		{
			temp.clear();
			temp.push_back(value_list[i]);
			table.push_back(temp);
		}
	}
	else
	{
		for (int i = 0; i < table.size(); i++)
		{
			table[i].push_back(value_list[i]);
		}
	}
	attr_names.push_back(name);
	attr_types.push_back(type);
}

vector<string> Relation::select_column(vector<string> cond_list)
{
	vector<string> column;
	int i = 0;
	for (i; i < attr_names.size(); i++)
	{
		if ((cond_list[0] == attr_names[i]) && (cond_list[1] == attr_types[i]))
			break;
	}
	for (int j = 0; j < table.size(); j++)
	{
		column.push_back(table[j][i]);
	}
	return column;
}

void Relation::update_column(vector<string> value_list, vector<string> cond_list)
{
	int i = 0;
	for (i; i < attr_names.size(); i++)
	{
		if ((cond_list[0] == attr_names[i]) && (cond_list[1] == attr_types[i]))
			break;
	}
	for (int j = 0; j < table.size(); j++)
	{
		table[j][i] = value_list[j];
	}
}

/*----------------- Relation Operations ----------------*/

bool Relation::union_compatible(Relation table)
{
	if ((attr_names == table.attr_names) && (attr_types == table.attr_types))
		return true;
	else
		return false;
}

void Relation::delete_from(vector<Conjunction> c_vec)
{
	for (int i = 0; i < c_vec.size(); i++)
		c_vec[i].delete_comparisons(*this);
}

void Relation::update(vector<tuple <string, string>> values, vector<Conjunction> c_vec)
{
	for (int i = 0; i < c_vec.size(); i++)
		c_vec[i].update_comparisons(values, *this);
}

Relation Relation::renaming(string new_table_name, vector<string> attr_list)
{
	Relation rename_table = Relation(new_table_name, attr_list, attr_types, key_pos);
	rename_table.table = table;
	return rename_table;
}

Relation Relation::projection(string new_table_name, vector<string> attr_list)
{
	Relation proj_table(new_table_name);
	vector<string> new_column;
	for (int i = 0; i < attr_list.size(); i++)  //iterate through attr_list passed to the function
	{
		for (int j = 0; j < attr_names.size(); j++)  //iterate through the names of the attributes of the relation being projected upon
		//can get rid of this if attr_list has same length as attr_names
		{
			if (attr_list.at(i) == attr_names.at(j))  //if the name on the attr_list matches the name in attr_names
			{
				new_column.clear();
				for (int k = 0; k < table.size(); k++) //iterate through the rows of the table
				{
					new_column.push_back(table[k][j]);  //add value on row k, column j, to the new column
				}
				proj_table.insert_column(new_column, attr_names.at(j), attr_types.at(j));  //add new column to new Relation
			}
		}
	}
	return proj_table;
}

Relation Relation::selection(string new_table_name, vector<Conjunction> c_vec)
{
	Relation selected_r;
	selected_r.attr_names = (*this).attr_names;
	selected_r.attr_types = (*this).attr_types;
	for (int i = 0; i < c_vec.size(); i++)
	{
		Relation and_comparisons = c_vec[i].select_comparisons(" ", *this);
		//and_comparisons contains the relation acquired from selecting the tuples that meet the requirments of
		//the AND comparisons

		selected_r = selected_r.set_union(" ", and_comparisons);
		//Union the and_comparisons relation and the selected_r relation to account for the OR comparisons
	}
	selected_r.name = new_table_name;
	return selected_r;
}

Relation Relation::set_union(string new_table_name, Relation other_table)
{
	//Check if relations are union compatible
	if ((*this).union_compatible(other_table))
	{
		//Create new relation to be returned at end of function;
		Relation union_table(new_table_name, attr_names, attr_types, key_pos);

		//Contains index of duplicate rows
		vector<int> duplicate_row;

		//Insert all rows from first table into new relation
		for (int i = 0; i < table.size(); i++)
		{
			union_table.insert_row(table[i]);
			for (int j = 0; j < other_table.table.size(); j++)
			{
				//Store index of duplciate rows found in other table
				if (table[i] == other_table.table[j])
				{
					duplicate_row.push_back(j);
				}
			}
		}

		//Insert non-duplicate rows from other table into new relation 
		for (int i = 0; i < other_table.table.size(); i++)
		{
			bool insert = true;
			for (int j = 0; j < duplicate_row.size(); j++)
			{
				if (i == duplicate_row[j])
				{
					insert = false;
					break;
				}
			}

			if (insert)
			{
				union_table.insert_row(other_table.table[i]);
			}
		}

		//Return new relation created from union
		return union_table;
	}
}

Relation Relation::set_difference(string new_table_name, Relation other_table)
{
	//Check if relations are union compatible
	if ((*this).union_compatible(other_table))
	{
		//Create new relation to be returned at end of function;
		Relation diff_table(new_table_name, attr_names, attr_types, key_pos);

		for (int i = 0; i < table.size(); i++) 
		{
			bool insert = true;
			for (int j = 0; j < other_table.table.size(); j++)
			{
				if (table[i] == other_table.table[j])
				{
					insert = false;
					break;
				}
			}

			if (insert)
			{
				diff_table.insert_row(table[i]);
			}
		}

		//Return new relation created from difference
		return diff_table;
	}
}

Relation Relation::set_intersect(Relation other_table)
{
	//Check if relations are union compatible
	if ((*this).union_compatible(other_table))
	{
		//Create new relation to be returned at end of function;
		Relation intersect_table(" ", attr_names, attr_types, key_pos);

		for (int i = 0; i < table.size(); i++)
		{
			bool insert = false;
			for (int j = 0; j < other_table.table.size(); j++)
			{
				if (table[i] == other_table.table[j])
				{
					insert = true;
					break;
				}
			}

			if (insert)
			{
				intersect_table.insert_row(table[i]);
			}
		}

		//Return new relation created from difference
		return intersect_table;
	}
}

Relation Relation::cross_product(string new_table_name, Relation other_table)
{
	vector<string> new_attr_names;
	vector<string> new_attr_types;
	vector<int> new_key_pos;

	//cout << "In cp" << endl;

	//Get key positions from the two tables being worked on and put them all into vector new_key_pos
	new_key_pos = key_pos;
	vector<int> temp_keys = other_table.key_pos;
	for (int i = 0; i < temp_keys.size(); i++)
		temp_keys[i] += key_pos.size();

	new_key_pos.insert(new_key_pos.end(), temp_keys.begin(), temp_keys.end());

	//cout << "Get keys" << endl;

	//Add names and types of attributes from the first table to the new table's names and types vectors
	for (int i = 0; i < attr_names.size(); i++)
	{
		new_attr_names.push_back(attr_names[i]);
		new_attr_types.push_back(attr_types[i]);
	}

	//cout << "Add names and types from first" << endl;

	//Add names and types of attributes from the second table to the new table's names and types vectors
	for (int i = 0; i < other_table.attr_names.size(); i++)
	{
		new_attr_names.push_back(other_table.attr_names[i]);
		new_attr_types.push_back(other_table.attr_types[i]);
	}

	//cout << "Add names and types from second" << endl;

	//Create new Relation that will hold the cross product of the two old Relaions
	Relation cp_table(new_table_name, new_attr_names, new_attr_types, new_key_pos);

	//cout << "Created new table" << endl;

	//Populate new cross product table
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < other_table.table.size(); j++)
		{
			vector<string> temp;
			temp = table[i];
			temp.insert(temp.end(), other_table.table[j].begin(), other_table.table[j].end());
			cp_table.insert_row(temp);
		}
	}


	//cout << "Returning new table" << endl;

	return cp_table;
}

Relation Relation::natural_join(string new_table_name, Relation other_table)
{
	vector<string> new_attr_names;
	vector<string> new_attr_types;
	vector<int> new_key_pos;
	string repeat = " ";
	int orig_repeated_pos;
	int repeat_pos = -1;

	//cout << "In nj" << endl;

	if (table.size() >= other_table.table.size())
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
				break;
			}
		}

		for (int i = 0; i < temp_keys.size(); i++)
			temp_keys[i] += key_pos.size();

		new_key_pos.insert(new_key_pos.end(), temp_keys.begin(), temp_keys.end());

		//cout << "Get keys" << endl;

		//Add names and types of attributes from the first table to the new table's names and types vectors
		new_attr_names = attr_names;
		new_attr_types = attr_types;

		//Add names and types of attributes from the second table to the new table's names and types vectors
		vector<string> temp_names = other_table.attr_names;
		vector<string> temp_types = other_table.attr_types;

		//If both relations cannot join, return an empty Relation
		if (repeat_pos == -1)
		{
			return Relation();
		}

		temp_names.erase(temp_names.begin() + repeat_pos);
		temp_types.erase(temp_types.begin() + repeat_pos);

		new_attr_names.insert(new_attr_names.end(), temp_names.begin(), temp_names.end());
		new_attr_types.insert(new_attr_types.end(), temp_types.begin(), temp_types.end());

		//cout << "Add second table" << endl;


		//Create new Relation to hold the natural join of the two old Relations 
		Relation nj_table(new_table_name, new_attr_names, new_attr_types, new_key_pos);

		//cout << "Create new table" << endl;

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

		//cout << "Returning new table" << endl;

		return nj_table;
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

		return nj_table;
	}
}

/*------------------ Print Operations ------------------*/

void Relation::show()
{
	cout << "\n" << name << "\n";
	cout << "========================================================" << endl;
	for (int i = 0; i < attr_names.size(); i++)
	{
		cout << setw(10) << left << attr_names.at(i);
	}
	//cout << "\n";
	cout << "\n--------------------------------------------------------" << endl;
	//Iterate through the rows of the table
	for (int i = 0; i < table.size(); i++)
	{
		//Iterate through the row
		for (int j = 0; j < (table.at(i)).size(); j++)
		{
			cout << setw(10) << left << (table.at(i)).at(j);
		}
		cout << "\n";
	}
	cout << "========================================================" << endl;

}

/*------------------ Operator Overloaders ------------------*/
 
Relation& Relation::operator=(const Relation& orig)
{
	name = orig.name;
	key_pos = orig.key_pos;
	attr_names = orig.attr_names;
	attr_types = orig.attr_types;
	table = orig.table;

	return *this;
}

bool operator ==(vector<string> a, vector<string> b)
{
	bool verdict = true;
	if (a.size() == b.size())
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i])
				verdict = false;
		}
		if (verdict)
			return true;
		else
			return false;
	}
	else
		return false;
}

/*------------------ Helper Functions ------------------*/

bool is_integer(const string& s) //s is an integer and Is_integer tests if it is an integer
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

bool check_row(vector<string> vec, vector<string> keys) //checks if keys are in row
{
	bool check = true;
	vector<bool> checked;
	for (int i = 0; i < keys.size(); i++)
	{
		checked.push_back(false);
	}

	for (int i = 0; i < keys.size(); i++)
	{
		for (int j = 0; j < vec.size(); j++)
		{
			if (keys[i] == vec[j])
			{
				checked[i] = true;
				//check = true;
				//break;
			}
		}
	}
	for (int i = 0; i < checked.size(); i++)
	{
		if (!checked[i])
			return false;
	}
	return true;
}

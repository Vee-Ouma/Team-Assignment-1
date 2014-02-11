/*File description: relation.cpp defines all member functions
declared in relation.h*/

#include "relation.h"

bool is_integer(const string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
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

bool check_row(vector<string> vec, vector<string> keys)
{
	bool check = false;

	for (int i = 0; i < keys.size(); i++)
	{
		for (int j = 0; j < vec.size(); j++)
		{
			if (keys[i] == vec[j])
			{
				check = true;
				break;
			}
		}
		if (!check)
		{
			return false;
		}
	}
	return true;
}

void Relation::insert_row(vector<string> value_list)
{
	table.push_back(value_list);
}

void Relation::delete_row(vector<string> key_list)
{
	if (table.size() == 0)
	{
		
	}
	else
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
}

void Relation::insert_column(vector<string> value_list, string name, string type)
{
	for (int i = 0; i < table.size(); i++)
	{
		table[i].push_back(value_list[i]); 
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

bool Relation::union_compatible(Relation table)
{
	if ((attr_names == table.attr_names) && (attr_types == table.attr_types))
		return true;
	else
		return false;
}

Relation Relation::renaming(string new_table_name, vector<string> attr_list)
{
	if (attr_names.size() == attr_list.size())
	{
		attr_names = attr_list;
		return (*this);
	}
}

Relation Relation::set_union(string new_table_name, Relation other_table)
{
	//Check if relations are union compatible
	if ((*this).union_compatible(other_table))
	{
		//Create new relation to be returned at end of function;
		Relation union_table("", attr_names, attr_types, key_pos);

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
		Relation diff_table("", attr_names, attr_types, key_pos);

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


void Relation::show()
{
	cout << name << "\n";
	for (int i = 0; i < attr_names.size(); i++)
	{
		cout << setw(10) << left << attr_names.at(i);
	}
	cout << "\n";
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

}

 
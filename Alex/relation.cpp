/*File description: relation.cpp defines all member functions
declared in relation.h*/

#include "relation.h"

bool operator ==(vector<string> a, vector<string> b)
{
	bool verdict = true;
	if(a.size() == b.size())
	{
		for(int i = 0; i < a.size(); i++)
		{
			if(a[i] != b[i])
				verdict = false;
		}		
		if(verdict)
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
	
	for(int i = 0; i < keys.size(); i++)
	{
		for(int j = 0; j < vec.size(); j++)
		{
			if(keys[i] == vec[j])
			{
				check = true;
				break;
			}
		}
		if(!check)
		{
			return false;
		}
	}
	return true;
}

void insert_row(vector<string> value_list)
{
	table.pushback(value_list);
}

void delete_row(vector<string> key_list)
{
	bool check_keys = false;
	for(int i = 0; i < table.size(); i++)
	{
		if(check_row(table[i], key_list))
		{
			key_list.erase(key_list.begin() + i);
			break;
		}
	}
}

void insert_column(vector<string> value_list, string name, string type)
{
	for(int i = 0; i < table.size(); i++)
	{
		table[i].pushback(value_list);
	}
	attr_names.pushback(name);
	attr_types.pushback(type);
}

vector<string> select_column(vector<string> cond_list)
{
	vector<string> column;
	int i = 0;
	for(i; i < attr_names.size(); i++)
	{
		if((cond_list[0] == attr_names[i]) && (cond_list[1] == attr_types[i]))
			break;
	}
	for(int j = 0; j < table.size(); j++)
	{
		column.pushback(table[j][i]);
	}
	return column;

	return column;
}

void update_column(vector<string> attr_list, vector<string> cond_list)
{
	int i = 0;
	for(i; i < attr_names.size(); i++)
	{
		if((cond_list[0] == attr_names[i]) && (cond_list[1] == attr_types[i]))
			break;
	}
	for(int j = 0; j < table.size(); j++)
	{
			table[j][i] = attr_list;
	}
}

bool union_compatible(Relation table)
{
	if((attr_names == table.attr_names) && (attr_types == table.attr_types))
		return true;
	else
		return false;
}
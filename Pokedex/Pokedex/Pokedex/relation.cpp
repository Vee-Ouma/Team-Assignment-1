/*File description: relation.cpp defines all member functions
declared in relation.h*/

#include "relation.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

bool Relation::test_condition(vector<string> attr_list, vector<string> cond_list)
{

}

void Relation::insert_row(vector<string> value_list)
{

}

void Relation::delete_row(vector<string> attr_list, vector<string> cond_list)
{

}

void Relation::insert_column(vector<string> value_list)
{

}

vector<string> Relation::select_column(vector<string> attr_list, vector<string> cond_list)
{

}

void Relation::update_column(vector<string> attr_list, vector<string> cond_list)
{

}

bool Relation::union_compatible(Relation table)
{

}

//Done... I think
void Relation::renaming(vector<string> attr_list)
{
	for (int i = 0; i < attr_list.size(); i++)  //iterate through attr_list passed to the function
	{
		if (attr_list.at(i) != "NULL")  //if the string in the attr_list is a new name
		{
			attr_names.at(i) = attr_list.at(i);  //change the name of the attribute of the relation to the new name
		}
	}
}

//Done... I think
Relation Relation::projection(vector<string> attr_list)
{
	string new_name = name;  //new_name is the same name as the relation being projected upon
	Relation* temp = new Relation;  
	(*temp).set_name(new_name);  //new relation's name is set to new_name
	vector<string> new_column;
	for (int i = 0; i < attr_list.size(); i++)  //iterate through attr_list passed to the function
	{
		for (int j = 0; j < attr_names.size(); j++)  //iterate through the names of the attributes of the relation being projected upon
		//can get rid of this if attr_list has same length as attr_names
		{
			if (attr_list.at(i) == attr_names.at(j))  //if the name on the attr_list matches the name in attr_names
			{
				for (int k = 0; k < table.size(); k++) //iterate through the rows of the table
				{
					new_column.push_back(table[k][j]);  //add value on row k, column j, to the new column
				}
				(*temp).insert_column(new_column);  //add new column to new Relation
				((*temp).attr_names).push_back(attr_names.at(j));  //add name of new attribute to new Relation
				((*temp).attr_types).push_back(attr_types.at(j));  //add type of new attribute to new Relation
			}
		}
	}
	return *temp;
}

Relation Relation::selection(vector<string> attr_list, vector<string> cond_list)
{
	string new_name = name;  //new_name is the same name as the relation being selected from
	Relation* temp = new Relation;
	(*temp).set_name(new_name);  //new relation's name is set to new_name

	return *temp;
}

Relation Relation::set_union(Relation table)
{

}

Relation Relation::set_difference(Relation table)
{

}

Relation Relation::cross_product(Relation table)
{

}

Relation Relation::natural_join(Relation table)
{

}

//Done... I think
void Relation::show()
{
	cout << name << "\n";
	for (int i = 0; i < attr_names.size(); i++)
	{
		cout << setw(10) << left << attr_names.at(i);
	}
	cout << "\n";
	for (int i = 0; i < table.size(); i++)  //iterate through the rows of the table
	{
		for (int j = 0; j < (table.at(i)).size(); j++)  //iterate through the row
		{
			cout << setw(10) << left << (table.at(i)).at(j);
		}
		cout << "\n";
	}
}

 
/*File description: relation.h declares the Relation class. Objects
of this class are tables resembled by a 2-D vector of strings. Each
row of the table signifies a tuple and each column signifies an
attribute. The member functions defined in this header must support
updating and accessing data in the tables.*/

/*What to to think about: Need to declare and define a function that
retuns a boolean value whether an attribute's value satisfies a condition.
Any functions that are passed vector<string> cond_list will need to call
this function.*/

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

struct Relation {
	string name;          //Name of relation
	vector<int> key_pos; //Contains position of columns used as keys

	vector<string> attr_names;	//Name of the attributes
	vector<string> attr_types; //Data type of the attributes

	vector<vector<string>> table; //2-Dimensional table of strings

	Relation() //Default relation constructor
	{
		name = "";
	}

	Relation(string _name)
	{
		name = _name;
	}

	Relation(string _name, vector<string> _attr, vector<string> _attr_type, vector<int> _key_pos)
	{
		name = _name;
		key_pos = _key_pos;
		attr_names = _attr;
		attr_types = _attr_type;
	}

	/*------------------- Row Operations -------------------*/

	//Insert values into a row of a table 
	void insert_row(vector<string> value_list); //Alex

	//Delete rows where attribute satisfies condition 
	//key_list contains the keys to the row that is going to be deleted
	void delete_row(vector<string> key_list); //Alex 

	/*----------------- Column Operations ------------------*/

	//Insert values into a column of a table 
	void insert_column(vector<string> value_list, string name, string type); //Alex

	//Insert values into a column of a table 
	//attr_list has name first, then type second
	//cond_list is the row that's going to be deleted
	void delete_column(vector<string> value_list, string name, string type); //Alex

	//Select values in columns that satisfy conditions 
	//cond_list contains name and then type
	vector<string> select_column(vector<string> cond_list); //Alex

	//Update values in columns that satisfy conditions 
	//cond_list contains name and then type
	void update_column(vector<string> attr_list, vector<string> cond_list); //Alex

	/*----------------- Relation Operations ----------------*/

	//Returns true if two relations are union compatible
	bool union_compatible(Relation table); //Alex

	//Relation test_conditions(Condition table);

	//Return new relation with renamed attributes
	Relation renaming(string new_table_name, vector<string> attr_list); //Jordan

	//Return new relation that contains specified attribute columns
	Relation projection(string new_table_name, vector<string> attr_list); //Jordan

	//Return new relation that satisfies conditions
	Relation selection(string new_table_name, vector<string> attr_list, vector<string> cond_list); //Jordan

	//Return new relation which is the union of two relations
	Relation set_union(string new_table_name, Relation other_table); //Zach

	//Return new relation which is the difference of two relations
	Relation set_difference(string new_table_name, Relation other_table); //Zach

	//Return new relation which is the cross product of two relations
	Relation cross_product(string new_table_name, Relation other_table); //Ian

	//Return new relation which is the natural join of two relations
	Relation natural_join(string new_table_name, Relation other_table); //Ian

	/*------------------ Print Operations ------------------*/

	//Display relation to console 
	void show(); //Jordan

};

    /*------------------ Helper Functions ------------------*/

bool operator ==(vector<string> a, vector<string> b); //Alex

bool check_row(vector<string> vec, vector<string> keys); //Alex

//Return true if attribute's value satisfies condition
bool test_condition(vector<string> attr_list, vector<string> cond_list);

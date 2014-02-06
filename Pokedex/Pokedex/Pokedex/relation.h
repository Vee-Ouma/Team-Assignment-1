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

using namespace std;

struct Relation {
	string name;          //Name of relation
	vector<int> key_pos; //Contains position of columns used as keys
	
	vector<vector<string>> table; //2-Dimensional table of strings
	                             //1st row: attribute name
							    //2nd row: data type of attribute

	Relation() //Default relation constructor
	{
		name = "";
	}

	Relation(string _name, vector<string> _attr, vector<string> _attr_type, vector<int> _key_pos)
	{
		name = _name;
		key_pos = _key_pos;
		table.push_back(_attr);
		table.push_back(_attr_type);
	}
	
	/*------------------- Row Operations -------------------*/
	
	//Insert values into a row of a table TODO
	void insert_row(vector<string> value_list);
	
	//Delete rows where attribute satisfies condition TODO
	void delete_row(vector<string> attr_list, vector<string> cond_list);
	
	/*----------------- Column Operations ------------------*/

    //Insert values into a column of a table TODO
    void insert_column(vector<string> value_list);
		
	//Select values in columns that satisfy conditions TODO
	vector<string> select_column(vector<string> attr_list, vector<string> cond_list);
	
	//Update values in columns that satisfy conditions TODO
	void update_column(vector<string> attr_list, vector<string> cond_list);
	
	/*----------------- Relation Operations ----------------*/
	
	//Returns true if two relations are union compatible
	bool union_compatible(Relation table); //Alex

	//Return new relation with renamed attributes
	Relation renaming(vector<string> attr_list); //Jordan

	//Return new relation that contains speficied attribute columns
	Relation projection(vector<string> attr_list); //Jordan

	//Return new relation that satisfies conditions
	Relation selection(vector<string> attr_list, vector<string> cond_list); //Jordan

	//Return new relation which is the union of two relations
	Relation set_union(Relation table); //Zach

	//Return new relation which is the difference of two relations
	Relation set_difference(Relation table); //Zach

	//Return new relation which is the cross product of two relations
	Relation cross_product(Relation table); //Ian

	//Return new relation which is the natural join of two relations
	Relation natural_join(Relation table); //Ian

	/*------------------ Print Operations ------------------*/

	//Display relation to console 
	void show(); //Jordan
	
};

    /*------------------ Helper Functions ------------------*/

//Return true if attribute's value satisfies condition
bool test_condition(vector<string> attr_list, vector<string> cond_list);

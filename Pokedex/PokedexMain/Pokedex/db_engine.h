/*File description: db_engine.h declares the DB_Engine class. The
purpose of this class is to act as an interface between the parser
and the relations. All relations used by the database are saved in
the tables vector.*/

#pragma once

#include "relation.h"

struct DB_Engine {
	string name;              //Name of database engine
	vector<Relation> tables; //Contains all saved relations

	DB_Engine() //Default db_engine contructor
	{
		name = "";
	}

	DB_Engine(string _name)
	{
		name = _name;
	}

	//Return index of table in tables vector
	int get_table_pos(string table_name);

	Relation get_table(string table_name);

	//Call relation constructor and add it to vector of relations 	
	void create_table(string table_name, vector<string> attr_list, vector<string> attr_type, vector<int> key_pos);

	//Insert values into row of table
	void row_insert(string table_name, vector<string> value_list);

	//Delete a row from a table depending on the values in the key_list
	void row_delete(string table_name, vector<string> key_list);

	//Delete rows from a table depending on the conditions passed to the function
	void delete_conditional(string table_name, vector<Conjunction> c);

	//Update values to a table depending on the conditions passed to the function
	void update_relation(string table_name, vector<tuple <string, string>> values , vector<Conjunction> c);

	//Rename the attributes of a table
	Relation rename(string table_name, string new_table_name, vector<string> attr_names);

	//Return new relation that contains specified attribute columns
	Relation project(string table_name, string new_table_name, vector<string> attr_names);

	//Return new relation that satisfies conditions
	Relation selection(string table_name, string new_table_name, vector<Conjunction> conj);

	//Return new relation which is the union of two relations
	Relation union_set(string table_name, string new_table_name, Relation r);

	//Return new relation which is the difference of two relations
	Relation difference(string table_name, string new_table_name, Relation r);

	//Return new relation which is the cross product of two relations
	Relation cross(string table_name, string new_table_name, Relation r);

	//Return new relation which is the natural join of two relations
	Relation join(string table_name, string new_table_name, Relation r);

	//Remove table from tables vector
	void drop_table(string table_name);

	//Writes relation r's current values to its file
	int write(string table_name);

	//Closes relation r's file
	void close(string table_name);
};



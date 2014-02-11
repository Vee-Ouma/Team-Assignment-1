/*File description: db_engine.h declares the DB_Engine class. The
purpose of this class is to act as an interface between the parser
and the relations. All relations used by the database are saved in
the tables vector.*/

#pragma once

#include "relation.h"

struct DB_Engine {
	string name;               //Name of database engine
	vector<Relation> tables; //Contains all saved relations
	
	DB_Engine() //Default db_engine contructor
	{
		name = "";
	}
	
	DB_Engine(string _name) 
	{
		name = _name; //TODO: is name necessary?
	}
	
	//Return index of table in tables vector
	int get_table_pos(string table_name);

	//Call relation constructor and add it to vector of relations 	
	void create_table(string table_name, vector<string> attr_list, vector<string> attr_type, vector<int> key_pos);

	//Insert values into row of table
	void insert_into(string table_name, vector<string> values);
	
	//Delete a table from the vector of tables
	void drop_table(string table_name);

	//To be continued...
};


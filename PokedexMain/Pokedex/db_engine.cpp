/*File description: db_engine.cpp defines all member functions
declared in db_engine.h*/

#include "db_engine.h"
#include "parser.h"
#include <fstream>

using namespace std;

int DB_Engine::get_table_pos(string table_name)
{
	for (int i = 0; i < tables.size(); i++)
	{
		if (tables[i].name == table_name)
		{
			return i;
		}
	}

	return -1;
}

void DB_Engine::create_table(string table_name, vector<string> attr_list, vector<string> attr_type, vector<int> key_pos)
{
	Relation new_table(table_name, attr_list, attr_type, key_pos);
	tables.push_back(new_table);
}

void DB_Engine::drop_table(string table_name)
{
	string file_name = table_name + ".db";
	if (remove(file_name.c_str()) != 0)
	{
		cout << "Error deleting file";
	}
	else
	{
		int table_pos = get_table_pos(table_name);
		tables.erase(tables.begin() + table_pos);
	}
}

void DB_Engine::insert_into(string table_name, vector<string> value_list)
{
	int table_pos = get_table_pos(table_name);
	tables[table_pos].insert_row(value_list);
}

int DB_Engine::open(string table_name)
{
	string read_line;
	string file_name = table_name + ".db";
	ifstream db_file(file_name);
	if (db_file.is_open())
	{
		while (getline(db_file, read_line))
		{
			//pass read_line to parser
		}
		db_file.close();
		return 0;
	}
	else  //unable to open file
		return -1;
}

int DB_Engine::write(string table_name)
{
	int position = get_table_pos(table_name);
	Relation r = tables.at(position);
	string file_name = table_name + ".db";
	ofstream db_file(file_name, ios::trunc);  //overwrites old file
	if (db_file.is_open())
	{
		db_file << ""; //Command to create table
		for (int i = 0; i < (r.table).size(); i++)
		{
			//need helper function to extract tuples
			db_file << "";//Command to add rows
		}
		db_file.close();
		return 0;
	}
	else  //unable to open file
		return -1;
}

void DB_Engine::close(string table_name)
{
	int table_pos = get_table_pos(table_name);
	tables.erase(tables.begin() + table_pos);
}




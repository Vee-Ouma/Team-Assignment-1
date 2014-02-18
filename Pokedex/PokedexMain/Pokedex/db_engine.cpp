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

Relation DB_Engine::get_table(string table_name)
{
	for (int i = 0; i < tables.size(); i++)
	{
		if (tables[i].name == table_name)
		{
			return tables[i];
		}
	}
}

void DB_Engine::create_table(string table_name, vector<string> attr_list, vector<string> attr_type, vector<int> key_pos)
{
	Relation new_table(table_name, attr_list, attr_type, key_pos);
	tables.push_back(new_table);
}

void DB_Engine::row_insert(string table_name, vector<string> value_list)
{
	int table_pos = get_table_pos(table_name);
	tables[table_pos].insert_row(value_list);
}

void DB_Engine::row_delete(string table_name, vector<string> key_list)
{
	int table_pos = get_table_pos(table_name);
	tables[table_pos].delete_row(key_list);
}

void DB_Engine::delete_conditional(string table_name, vector<Conjunction> c)
{
	int table_pos = get_table_pos(table_name);
	tables[table_pos].delete_from(c);
}

void DB_Engine::update_relation(string table_name, vector<tuple <string, string>> values , vector<Conjunction> c)
{
	int table_pos = get_table_pos(table_name);
	tables[table_pos].update(values, c);
}

Relation DB_Engine::rename(string table_name, string new_table_name, vector<string> attr_names)
{
	int table_pos = get_table_pos(table_name);
	Relation new_relation = tables[table_pos].renaming(new_table_name, attr_names);
	return new_relation;
}

Relation DB_Engine::project(string table_name, string new_table_name, vector<string> attr_names)
{
	int table_pos = get_table_pos(table_name);
	Relation new_relation = tables[table_pos].projection(new_table_name, attr_names);
	return new_relation;
}

Relation DB_Engine::selection(string table_name, string new_table_name, vector<Conjunction> conj)
{
	int table_pos = get_table_pos(table_name);
	Relation new_relation = tables[table_pos].selection(new_table_name, conj);
	return new_relation;
}

Relation DB_Engine::union_set(string table_name, string new_table_name, Relation r)
{
	int table_pos = get_table_pos(table_name);
	Relation new_relation = tables[table_pos].set_union(new_table_name, r);
	return r;
}

Relation DB_Engine::difference(string table_name, string new_table_name, Relation r)
{
	int table_pos = get_table_pos(table_name);
	Relation new_relation = tables[table_pos].set_difference(new_table_name, r);
	return r;
}

Relation DB_Engine::cross(string table_name, string new_table_name, Relation r)
{
	int table_pos = get_table_pos(table_name);
	Relation new_relation = tables[table_pos].cross_product(new_table_name, r);
	return r;
}

Relation DB_Engine::join(string table_name, string new_table_name, Relation r)
{
	int table_pos = get_table_pos(table_name);
	Relation new_relation = tables[table_pos].natural_join(new_table_name, r);
	return r;
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

int DB_Engine::write(string table_name)
{
	int position = get_table_pos(table_name);
	Relation r = tables.at(position);
	string file_name = table_name + ".db";
	ofstream db_file(file_name, ios::trunc);  //overwrites old file
	if (db_file.is_open())
	{

		//insert command into file that creates relation r
		db_file << "CREATE TABLE " << table_name << "(";
		for (int i = 0; i < (r.attr_names).size(); i++)
		{
			db_file << (r.attr_names).at(i) << " ";
			if ((r.attr_types).at(i) == "string")
			{
				db_file << "VARCHAR";
			}
			else if ((r.attr_types).at(i) == "int")
			{
				db_file << "INTEGER";
			}
			if (i != (((r.attr_names).size()) - 1))  //if the attribute name is not the last one of the relation
			{
				db_file << ", ";
			}
		}
		db_file << ") PRIMARY KEY (";
		for (int i = 0; i < (r.key_pos).size(); i++)
		{
			db_file << (r.attr_names).at((r.key_pos).at(i));  //add the name of the attribute referenced by the key int
			if (i != (((r.key_pos).size()) - 1))  //if the key number is not the last one in the vector
			{
				db_file << ", ";
			}
		}
		db_file << ")\n";

		//insert commands into file that will insert the rows of relation r's table
		for (int i = 0; i < (r.table).size(); i++)
		{
			db_file << "INSERT INTO " << table_name << " VALUES FROM (";
			for (int j = 0; j < (r.table[i]).size(); j++)
			{
				if ((r.attr_types).at(j) == "string")
				{
					db_file << """ << (r.table[i]).at(j) << """;
				}
				else if ((r.attr_types).at(j) == "int")
				{
					db_file << (r.table[i]).at(j);
				}
				if (j != ((r.table[i]).size()) - 1)  //if the attribute is not the last one of the row
				{
					db_file << ", ";
				}
			}
			db_file << ")\n";
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





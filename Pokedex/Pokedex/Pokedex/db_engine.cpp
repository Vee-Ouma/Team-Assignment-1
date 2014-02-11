/*File description: db_engine.cpp defines all member functions
declared in db_engine.h*/

#include "db_engine.h"

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
	int table_pos = get_table_pos(table_name);
	tables.erase(tables.begin() + table_pos);
}

void DB_Engine::insert_into(string table_name, vector<string> value_list)
{
	int table_pos = get_table_pos(table_name);
	tables[table_pos].insert_row(value_list);
}



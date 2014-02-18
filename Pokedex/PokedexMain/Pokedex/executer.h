#pragma once

#include "db_engine.h"
#include <regex>
#include <stack>

struct Executer {
	DB_Engine dbms; //Database engine 
	string name; //Name of Executer

	stack<string> query_stack; //Contains strings of parsed query 
	stack<string> cmd_stack; //Contains strings of parsed command

	Executer()
	{
		name = "";
	}

	Executer(string _name)
	{
		name = _name;
	}

	void process_query_stack(stack<string> stack);
	void process_cmd_stack(stack<string> stack);
};


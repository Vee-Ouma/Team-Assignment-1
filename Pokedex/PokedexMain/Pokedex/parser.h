/*File description: paser.h declares the Parser class. The purpose
of this class is to implement functions to parse each possible
SQL command/query.*/

#pragma once

#include "executer.h"
#include <fstream>

struct Parser {
	Executer exec; //Executer to link parser and database engine
	string name; //Name of Parser

	Parser()
	{
		name = "";
	}

	Parser(string _name)
	{
		name = _name;
	}

	void program(string program);
};

void select(string s);
void project(string s);
void rename(string s);
void set_union(string s);
void set_difference(string s);
void product(string s);
void join(string s);

string expression(string expr);
void query(string query);
void cmd(string cmd);

int open(string name);


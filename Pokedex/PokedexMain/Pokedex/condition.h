#pragma once

#include <vector>
#include <tuple>
#include <string>

using namespace std;

struct Condition {
	string name; //Name of relation

	vector<string> attr_names;	//Name of the attributes

	typedef vector<vector<tuple<string, string, string>>> cond_table; //2-Dimensional table of string tuples
														             //First string is operand type
	                                                                //Second string is operator
														           //Third string is operand
	Condition() //Default relation constructor
	{
		name = "";
	}

	Condition(string _name)
	{
		name = _name;
	}

	void insert_comparison(string comparison);

};
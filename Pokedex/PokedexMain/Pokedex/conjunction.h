#pragma once

#include <vector>
#include <string>
#include <tuple>

using namespace std;

struct Relation;

struct Conjunction{
	//0: attribute name; 1: type; 2: op ; 3: value
	typedef vector< tuple<string, string, string, string> > Conj_Type;

	Conj_Type comparisons;
	Conjunction() {} //Default relation constructor

	void insert_comparison(string attr_name, string attr_type, string op, string value);
	Relation select_comparisons(string new_table_name, Relation old_r);
	void delete_comparisons(Relation& r);
	void update_comparisons(string value, Relation& r);
};
/*File description: main.cpp is the future home of the
application. This file will likely be updated during phase II of
development.*/

#include "parser.h"
#include <iostream>

int main () 
{
	
	vector<string> attr = { "names", "age" , "cash" };
	vector<string> attr_type = { "VARCHAR", "VARCHAR" , "VARCHAR" };
	vector<int> key_pos = { 0 };

	vector<string> row1 = { "Bob", "2", "3" };
	vector<string> row2 = { "Larry", "5", "6" };
	vector<string> row3 = { "Bilbo", "8", "9" };
	Relation test_table("Table 1", attr, attr_type, key_pos);
	test_table.insert_row(row1);
	test_table.insert_row(row2);
	test_table.insert_row(row3);
	test_table.show();

	vector<string> row4 = { "1", "2", "3" };
	vector<string> row5 = { "10", "11", "12" };
	vector<string> row6 = { "13", "14", "15" };
	Relation test_table2("Table 2", attr, attr_type, key_pos);
	test_table2.insert_row(row4);
	test_table2.insert_row(row5);
	test_table2.insert_row(row6);
	test_table2.show();

	Conjunction c;

	c.insert_comparison("names", "VARCHAR", "==", "Bob");
	c.insert_comparison("age", "VARCHAR", "<", "6");
	

	Relation test_table3;

	//test_table3 = test_table.selection(c);

	//test_table3.show();

	test_table.delete_from(c);

	//test_table.update("NotBob", c);

	test_table.show();

	

	system("pause");
}

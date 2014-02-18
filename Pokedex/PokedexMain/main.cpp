/*File description: main.cpp is the future home of the
application. This file will likely be updated during phase II of
development.*/

#include "parser.h"
#include <iostream>

int main()
{
	int quit = 0;
	vector<string> attr = { "names", "plays", "age" };
	vector<string> attr2 = { "names", "games", "number" };
	vector<string> attr_type = { "VARCHAR", "VARCHAR", "VARCHAR" };
	vector<int> key_pos = { 0 };

	vector<string> row1 = { "Bob", "2", "3" };
	vector<string> row2 = { "James", "5", "6" };
	vector<string> row3 = { "John", "8", "9" };
	Relation test_table("Table 1", attr, attr_type, key_pos);
	test_table.insert_row(row1);
	test_table.insert_row(row2);
	test_table.insert_row(row3);
	test_table.show();

	vector<string> row4 = { "Bob", "4", "5" };
	vector<string> row5 = { "John", "11", "12" };
	vector<string> row6 = { "James", "14", "15" };
	Relation test_table2("Table 2", attr2, attr_type, key_pos);
	test_table2.insert_row(row4);
	test_table2.insert_row(row5);
	test_table2.insert_row(row6);
	test_table2.show();

	Relation test_table3;

	test_table3 = test_table.cross_product("Table 3", test_table2);

	test_table3.show();

	test_table.cross_product("Table 3", test_table2).show();

	//test_table3 = test_table.cross_product("Table 3", test_table2);

	Conjunction c;

	c.comparisons.push_back(make_tuple("names", "VARCHAR", "==", "James"));

	Relation test_table4;

	//test_table4 = test_table.selection("YAY", c);

	test_table4.show();



	//(test_table2.set_difference("Union Table", test_table)).show();

	system("pause");

}

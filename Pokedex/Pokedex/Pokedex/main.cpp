/*File description: main.cpp is the future home of the
application. This file will likely be updated during phase II of
development.*/

#include "parser.h"
#include <iostream>

int main () 
{
	int quit = 0;
	while (quit != 1) {
		vector<string> attr = { "Column 1", "Column 2" , "Column 3" };
		vector<string> attr_type = { "string", "string" , "string" };
		vector<int> key_pos = { 0 };

		vector<string> row1 = { "1", "2", "3" };
		vector<string> row2 = { "4", "5", "6" };
		vector<string> row3 = { "7", "8", "9" };
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

		(test_table2.set_difference("Union Table", test_table)).show();

		cout << "Quit: ";
		cin >> quit;
	}
	
}

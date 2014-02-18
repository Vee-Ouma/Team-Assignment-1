/*File description: parser.cpp defines all member functions
declared parser.h.*/

#include "parser.h"

stack<string> query_stack; //Contains strings of parsed query 
stack<string> cmd_stack; //Contains strings of parsed command

/*--------------------------- Relational Algebra Functions --------------------------*/

string expression(string expr);

void select(string s)
{
	query_stack.push("end");
	//Remove the word "select" from string s
	query_stack.push("select");
	int pos = s.find("select");
	s.erase(pos, 6);
	//Get condition from string s
	string cond = s.substr(s.find_first_of('(') + 1, s.find_first_of(')') - 1);
	query_stack.push(cond);

	//Remove condition and get atomic expression from string s
	s.erase(s.find_first_of('('), s.find_first_of(')') + 1);
	string atomic_expression = s;
	query_stack.push(expression(atomic_expression));
}

void project(string s)
{
	query_stack.push("end");
	//Remove the word "project" from string s
	query_stack.push("project");
	int pos = s.find("project");
	s.erase(pos, 7);

	//Get attribute list from string s
	string attr_list = s.substr(s.find_first_of('(') + 1, s.find_first_of(')') - 1);
	query_stack.push(attr_list);

	//Remove attribute list and get atomic expression from string s
	s.erase(s.find_first_of('('), s.find_first_of(')') + 1);
	string atomic_expression = s;
	query_stack.push(expression(atomic_expression));
}

void rename(string s)
{
	query_stack.push("end");
	//Remove the word "rename" from string s
	query_stack.push("rename");
	int pos = s.find("rename");
	s.erase(pos, 6);

	//Get attribute list from string s
	string attr_list = s.substr(s.find_first_of('(') + 1, s.find_first_of(')') - 1);
	query_stack.push(attr_list);

	//Remove attribute list and get atomic expression from string s
	s.erase(s.find_first_of('('), s.find_first_of(')') + 1);
	string atomic_expression = s;
	query_stack.push(expression(atomic_expression));
}

void set_union(string s)
{
	query_stack.push("end");
	//Get left atomic expression of union
	string left_atomic_expr;
	regex_replace(back_inserter(left_atomic_expr), s.begin(), s.end(), regex("\\+(.*)"), "$2");
	query_stack.push(expression(left_atomic_expr));
	
	query_stack.push("+");

	//Get right atomic expression of union
	string right_atomic_expr;
	regex_replace(back_inserter(right_atomic_expr), s.begin(), s.end(), regex("(.*)\\+"), "$2");
	query_stack.push(expression(right_atomic_expr));
}

void set_difference(string s)
{
	query_stack.push("end");
	//Get left atomic expression of union
	string left_atomic_expr;
	regex_replace(back_inserter(left_atomic_expr), s.begin(), s.end(), regex("\\-(.*)"), "$2");
	query_stack.push(expression(left_atomic_expr));

	query_stack.push("-");

	//Get right atomic expression of union
	string right_atomic_expr;
	regex_replace(back_inserter(right_atomic_expr), s.begin(), s.end(), regex("(.*)\\-"), "$2");
	query_stack.push(expression(right_atomic_expr));
}

void product(string s)
{
	query_stack.push("end");
	//Get left atomic expression of union
	string left_atomic_expr;
	regex_replace(back_inserter(left_atomic_expr), s.begin(), s.end(), regex("\\*(.*)"), "$2");
	query_stack.push(expression(left_atomic_expr));

	query_stack.push("*");

	//Get right atomic expression of union
	string right_atomic_expr;
	regex_replace(back_inserter(right_atomic_expr), s.begin(), s.end(), regex("(.*)\\*"), "$2");
	query_stack.push(expression(right_atomic_expr));
}

void join(string s)
{
	query_stack.push("end");
	//Get left atomic expression of union
	string left_atomic_expr;
	regex_replace(back_inserter(left_atomic_expr), s.begin(), s.end(), regex("JOIN(.*)"), "$2");
	query_stack.push(expression(left_atomic_expr));

	query_stack.push("JOIN");

	//Get right atomic expression of union
	string right_atomic_expr;
	regex_replace(back_inserter(right_atomic_expr), s.begin(), s.end(), regex("(.*)JOIN"), "$2");
	query_stack.push(expression(right_atomic_expr));
}

/*-----------------------  End of Relational Algebra Functions ----------------------*/

void create_table(string s)
{
	int pos = s.find("CREATETABLE");
	s.erase(pos, 11);

	string relation_name = s.substr(0, s.find_first_of('(') - 1);
	s.erase(0, s.find_first_of('('));
	cmd_stack.push(relation_name);

	string typed_attr_list;
	regex_replace(back_inserter(typed_attr_list), s.begin(), s.end(), regex("PRIMARYKEY(.*)"), "$2");	
	typed_attr_list = typed_attr_list.substr(typed_attr_list.find_first_of('(') + 1, typed_attr_list.find_last_of(')') - 1);
	cmd_stack.push(typed_attr_list);

	string key_list;
	regex_replace(back_inserter(key_list), s.begin(), s.end(), regex("(.*)PRIMARYKEY"), "$2");
	key_list = key_list.substr(key_list.find_first_of('(') + 1, key_list.find_first_of(')') - 1);
	cmd_stack.push(key_list);
}

void update(string s)
{
	int pos = s.find("UPDATE");
	s.erase(pos, 6);

	string relation_name = s.substr(0, s.find("SET"));
	cmd_stack.push(relation_name);
	s.erase(0, s.find("SET") + 3);

	string attr_list;
	regex_replace(back_inserter(attr_list), s.begin(), s.end(), regex("WHERE(.*)"), "$2");
	cmd_stack.push(attr_list);

	string cond;
	regex_replace(back_inserter(cond), s.begin(), s.end(), regex("(.*)WHERE"), "$2");
	cmd_stack.push(cond);
}

void insert_into_1(string s)
{
	int pos = s.find("INSERTINTO");
	s.erase(pos, 10);

	string relation_name;
	regex_replace(back_inserter(relation_name), s.begin(), s.end(), regex("VALUES(.*)"), "$2");
	cmd_stack.push(relation_name);

	string value_list;
	regex_replace(back_inserter(value_list), s.begin(), s.end(), regex("(.*)FROM"), "$2");
	value_list = value_list.substr(value_list.find_first_of('(') + 1, value_list.find_first_of(')') - 1);
	cmd_stack.push(value_list);
}

void delete_from(string s)
{
	int pos = s.find("DELETEFROM");
	s.erase(pos, 10);

	string relation_name;
	regex_replace(back_inserter(relation_name), s.begin(), s.end(), regex("WHERE(.*)"), "$2");
	cmd_stack.push(relation_name);

	string cond;
	regex_replace(back_inserter(cond), s.begin(), s.end(), regex("(.*)WHERE"), "$2");
	cmd_stack.push(cond);
}

/*-------------------------------- Grammar Functions --------------------------------*/

string expression(string expr)
{
	smatch match;
	//atomic expr
	if (expr[0] == '(' && expr[expr.length() - 1] == ')')
	{
		expr.erase(expr.begin() + 0);
		expr.erase(expr.begin() + expr.length() - 1);
		expression(expr);
	}
	//selection
	else if (regex_search(expr.cbegin(), expr.cend(), match, regex("^select(.*)")))
	{
		string result = match[0];
		select(result);
	}
	//projection
	else if (regex_search(expr.cbegin(), expr.cend(), match, regex("^project(.*)")))
	{
		string result = match[0];
		project(result);
	}
	//renaming
	else if (regex_search(expr.cbegin(), expr.cend(), match, regex("^rename(.*)")))
	{
		string result = match[0];
		rename(result);
	}
	//union
	else if (regex_search(expr.cbegin(), expr.cend(), match, regex("(.*)\\+(.*)")))
	{
		string result = match[0];
		set_union(result);
	}
	//difference
	else if (regex_search(expr.cbegin(), expr.cend(), match, regex("(.*)\\-(.*)")))
	{
		string result = match[0];
		set_difference(result);
	}
	//product
	else if (regex_search(expr.cbegin(), expr.cend(), match, regex("(.*)\\*(.*)")))
	{
		string result = match[0];
		product(result);
	}
	//natural join
	else if (regex_search(expr.cbegin(), expr.cend(), match, regex("(.*)JOIN(.*)")))
	{
		string result = match[0];
		join(result);
	}
	else
	{
		return expr;
	}

	return "NULL";
}

void query(string query)
{
	//Expression 
	string expr;
	regex_replace(back_inserter(expr), query.begin(), query.end(), regex("^\\w+(.*\\s?)<-"), "$2");
	expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
	expression(expr);

	//Relation name
	string relation_name;
	regex_replace(back_inserter(relation_name), query.begin(), query.end(), regex("<-(.*)"), "$2");
	query_stack.push(relation_name);
}

int open();

void cmd(string cmd) //TODO: account for no whitespace after keywords
{
	cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());

	smatch match;
	if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(OPEN)\\w+")))
	{
		string result = match[0];
		result.erase(0, 4);
		open(result);
	}
	else if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(CLOSE)\\w+")))
	{
		string result = match[0];
		result.erase(0, 5);
		cmd_stack.push("CLOSE");
		cmd_stack.push(result);
	}
	else if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(WRITE)\\w+")))
	{
		string result = match[0];
		result.erase(0, 5);
		cmd_stack.push("WRITE");
		cmd_stack.push(result);
	}
	else if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(EXIT)")))
	{
		string result = match[0];
		cmd_stack.push(result);
	}
	else if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(SHOW)")))
	{
		//TODO
	}
	else if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(CREATETABLE)")))
	{
		cmd_stack.push("CREATE TABLE");
		create_table(cmd);
	}
	else if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(UPDATE)")))
	{
		cmd_stack.push("UPDATE");
		update(cmd);
	}
	else if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(INSERTINTO)(.*)RELATION")))
	{
		cmd_stack.push("INSERT2");
		//TODO
	}
	else if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(INSERTINTO)")))
	{
		cmd_stack.push("INSERT1");
		insert_into_1(cmd);
	}
	else if (regex_search(cmd.cbegin(), cmd.cend(), match, regex("^(DELETEFROM)")))
	{
		cmd_stack.push("DELETE");
		delete_from(cmd);
	}
	else{
		cmd_stack.push("INVALID");
	}
}

void Parser::program(string program)
{

	//Remove ; from end of string program
	program.erase(program.begin() + program.length() - 1);

	regex regex_cmd("^(OPEN|CLOSE|WRITE|EXIT|SHOW|CREATE(.*\\s?)TABLE|UPDATE|INSERT(.*\\s?)INTO|DELETE(.*\\s?)FROM)(.*)");
	smatch match_cmd;
	smatch match_query;
	//Command
	if (regex_search(program.cbegin(), program.cend(), match_cmd, regex_cmd))
	{
		string result = match_cmd[0];
		cmd(result);
		exec.process_cmd_stack(cmd_stack);
		while (!cmd_stack.empty())
		{
			cmd_stack.pop();
		}
	}
	//Query
	if (regex_search(program.cbegin(), program.cend(), match_query, regex("^\\w+(.*\\s?)<-(.*)")))
	{
		string result = match_query[0];
		query(program);
		exec.process_query_stack(query_stack);
		while (!query_stack.empty())
		{
			query_stack.pop();
		}
	}
}

/*------------------------------ End of Grammar Functions ---------------------------*/

int open(string table_name)
{
	string read_line;
	string file_name = table_name + ".db";
	ifstream db_file(file_name);
	if (db_file.is_open())
	{
		while (getline(db_file, read_line))  //get line from file
		{
			cmd(read_line);  //send command to parser main function
		}
		db_file.close();
		return 0;
	}
	else  //unable to open file
		return -1;
}

/*int main(void)
{
	Parser p;
	vector<string> attr = { "name", "kind", "years"};
	vector<string> attr_type = { "VARCHAR", "VARCHAR", "INTEGER" };
	vector<int> key_pos = {0 , 1};

	Relation test_table("animals", attr, attr_type, key_pos);
	test_table.insert_row({ "Joe", "cat", "4" });
	test_table.insert_row({ "Spot", "dog", "10" });
	test_table.insert_row({ "Snoopy", "dog", "3" });
	test_table.insert_row({ "Tweety", "bird", "1" });
	test_table.insert_row({ "Joe", "cat", "2" });
	dbms.tables.push_back(test_table);

	//string input = "common_names <- project (name) (select (aname == name && akind != kind) (a * animals));";
	//string input = "a <- rename(aname, akind) (project(name, kind) animals);";
	string input = "cats_or_dogs <- dogs + (select(kind == \"cat\") (project(name, kind) animals));";
	//string input = "OPENanimals;";
	//string input = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
	//string input = "UPDATE animals SET  name = \"Spot\", kind = \"Dog\" WHERE age > 1 && trained == yes;";
	//string input = "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);";
	//string input = "DELETE FROM animals WHERE age > 1 && trained == yes;";
	
	p.program(input);

	system("pause");

	return(0);
}*/

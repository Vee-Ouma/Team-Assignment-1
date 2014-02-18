#include "executer.h"

/*--------------------------------- Helper Functions --------------------------------*/

bool is_integer(const string& s) //s is an integer and Is_integer tests if it is an integer
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

bool is_string(string& s)
{
	bool is_string = false;
	if (s.front() == '"') {
		is_string = true;
		s.erase(0, 1); // erase the first character
		s.erase(s.size() - 1); // erase the last character
	}

	return is_string;
}

tuple<string, string, string, string> make_comparison(string left_op, string oper, string right_op)
{
	//0: attribute name; 1: type; 2: op ; 3: value
	string attr_name, attr_type, op, value;
	op = oper;

	if (is_integer(left_op))
	{
		attr_name = right_op;
		attr_type = "INTEGER";
		value = left_op;
	}
	else if (is_string(left_op))
	{
		attr_name = right_op;
		attr_type = "VARCHAR";
		value = left_op;
	}
	else
	{
		if (is_integer(right_op))
		{
			attr_name = left_op;
			attr_type = "INTEGER";
			value = right_op;
		}
		else if (is_string(right_op))
		{
			attr_name = left_op;
			attr_type = "VARCHAR";
			value = right_op;
		}
		else
		{
			attr_name = left_op;
			attr_type = "ATTRIBUTE";
			value = right_op;
		}
	}

	return make_tuple(attr_name, attr_type, op, value);
}

vector<Conjunction> conjunction(vector<string> conjunction)
{
	Conjunction conj;
	vector<Conjunction> conj_list;

	vector <string> tokens;
	string accumulator;
	for (int j = 0; j < conjunction.size(); j++)
	{
		accumulator.clear();
		for (;;)
		{
			if (conjunction[j].size() == 0)
			{
				tokens.push_back(accumulator);
				for (int i = 0; i < tokens.size(); i++)
				{
					tokens[i].erase(remove(tokens[i].begin(), tokens[i].end(), ' '), tokens[i].end());
				}
				break;
			}
			if (conjunction[j][0] == '&' && conjunction[j][1] == '&')
			{
				conjunction[j].erase(0, 2);
				tokens.push_back(accumulator);
				accumulator.clear();
			}
			else
			{
				accumulator += conjunction[j].substr(0, 1);
				conjunction[j].erase(0, 1);
			}
		}
		//Create conjunction object 
		for (int k = 0; k < tokens.size(); k++)
		{
			cout << "tokens " << "[" << k << "] = " << tokens[k] << endl;
			if (regex_search(tokens[k].cbegin(), tokens[k].cend(), regex("(.*)==(.*)")))
			{
				string op = "==";

				string left_operand;
				regex_replace(back_inserter(left_operand), tokens[k].begin(), tokens[k].end(), regex("==(.*)"), "$2");

				string right_operand;
				regex_replace(back_inserter(right_operand), tokens[k].begin(), tokens[k].end(), regex("(.*)=="), "$2");

				tuple<string, string, string, string> p = make_comparison(left_operand, op, right_operand);
				conj.insert_comparison(get<0>(p), get<1>(p), get<2>(p), get<3>(p));

			}
			else if (regex_search(tokens[k].cbegin(), tokens[k].cend(), regex("(.*)!=(.*)")))
			{
				string op = "!=";

				string left_operand;
				regex_replace(back_inserter(left_operand), tokens[k].begin(), tokens[k].end(), regex("!=(.*)"), "$2");

				string right_operand;
				regex_replace(back_inserter(right_operand), tokens[k].begin(), tokens[k].end(), regex("(.*)!="), "$2");

				tuple<string, string, string, string> p = make_comparison(left_operand, op, right_operand);
				conj.insert_comparison(get<0>(p), get<1>(p), get<2>(p), get<3>(p));
			}
			else if (regex_search(tokens[k].cbegin(), tokens[k].cend(), regex("(.*)<(.*)")))
			{
				string op = "<";

				string left_operand;
				regex_replace(back_inserter(left_operand), tokens[k].begin(), tokens[k].end(), regex("<(.*)"), "$2");

				string right_operand;
				regex_replace(back_inserter(right_operand), tokens[k].begin(), tokens[k].end(), regex("(.*)<"), "$2");

				tuple<string, string, string, string> p = make_comparison(left_operand, op, right_operand);
				conj.insert_comparison(get<0>(p), get<1>(p), get<2>(p), get<3>(p));
			}
			else if (regex_search(tokens[k].cbegin(), tokens[k].cend(), regex("(.*)>(.*)")))
			{
				string op = ">";

				string left_operand;
				regex_replace(back_inserter(left_operand), tokens[k].begin(), tokens[k].end(), regex(">(.*)"), "$2");

				string right_operand;
				regex_replace(back_inserter(right_operand), tokens[k].begin(), tokens[k].end(), regex("(.*)>"), "$2");

				tuple<string, string, string, string> p = make_comparison(left_operand, op, right_operand);
				conj.insert_comparison(get<0>(p), get<1>(p), get<2>(p), get<3>(p));
			}
			else if (regex_search(tokens[k].cbegin(), tokens[k].cend(), regex("(.*)<=(.*)")))
			{
				string op = "<=";

				string left_operand;
				regex_replace(back_inserter(left_operand), tokens[k].begin(), tokens[k].end(), regex("<=(.*)"), "$2");

				string right_operand;
				regex_replace(back_inserter(right_operand), tokens[k].begin(), tokens[k].end(), regex("(.*)<="), "$2");

				tuple<string, string, string, string> p = make_comparison(left_operand, op, right_operand);
				conj.insert_comparison(get<0>(p), get<1>(p), get<2>(p), get<3>(p));
			}
			else if (regex_search(tokens[k].cbegin(), tokens[k].cend(), regex("(.*)>=(.*)")))
			{
				string op = ">=";

				string left_operand;
				regex_replace(back_inserter(left_operand), tokens[k].begin(), tokens[k].end(), regex(">=(.*)"), "$2");

				string right_operand;
				regex_replace(back_inserter(right_operand), tokens[k].begin(), tokens[k].end(), regex("(.*)>="), "$2");

				tuple<string, string, string, string> p = make_comparison(left_operand, op, right_operand);
				conj.insert_comparison(get<0>(p), get<1>(p), get<2>(p), get<3>(p));
			}
		}
		conj_list.push_back(conj);
		conj.clear();
		tokens.clear();
	}

	return conj_list;
}

vector<Conjunction> condition(string condition)
{
	vector <string> tokens;
	string accumulator;

	for (;;)
	{
		if (condition.size() == 0)
		{
			tokens.push_back(accumulator);
			for (int i = 0; i < tokens.size(); i++)
			{
				tokens[i].erase(remove(tokens[i].begin(), tokens[i].end(), ' '), tokens[i].end());
			}
			break;
		}
		if (condition[0] == '|' && condition[1] == '|')
		{
			condition.erase(0, 2);
			tokens.push_back(accumulator);
			accumulator.clear();
		}
		else
		{
			accumulator += condition.substr(0, 1);
			condition.erase(0, 1);
		}
	}

	return conjunction(tokens);
}

vector<string> attribute_list(string attr_list)
{
	vector <string> tokens;
	string accumulator;

	for (;;)
	{
		if (attr_list.size() == 0)
		{
			tokens.push_back(accumulator);
			for (int i = 0; i < tokens.size(); i++)
			{
				tokens[i].erase(remove(tokens[i].begin(), tokens[i].end(), ' '), tokens[i].end());
			}
			break;
		}
		if (attr_list[0] == ',')
		{
			attr_list.erase(0, 1);
			tokens.push_back(accumulator);
			accumulator.clear();
		}
		else
		{
			accumulator += attr_list.substr(0, 1);
			attr_list.erase(0, 1);
		}
	}

	return tokens;
}

/*------------------------------ End of Helper Functions ----------------------------*/

Relation process_select(stack<string>& sub_query, Relation relation)
{
	//Get and remove condition from stack
	string cond = sub_query.top();
	sub_query.pop();
	
	return relation.selection("", condition(cond));
}

Relation process_project(stack<string>& sub_query, Relation relation)
{
	//Get and remove condition from stack
	string attr_list = sub_query.top();
	sub_query.pop();
	
	return relation.projection("", attribute_list(attr_list));
}

Relation process_rename(stack<string>& sub_query, Relation relation)
{
	//Get and remove condition from stack
	string attr_list = sub_query.top();
	sub_query.pop();

	return relation.renaming("", attribute_list(attr_list));
}

void Executer::process_query_stack(stack<string> s)
{
	//Copy stack from parser
	query_stack = s;

	//Get name of new relation to be created
	string new_relation_name = query_stack.top();
	query_stack.pop();

	//Remove garbage data from stack
	while (query_stack.top() == "NULL")
	{
		query_stack.pop();
	}

	//Get name of initial relation and get from database engine
	string init_relation_name = query_stack.top();
	query_stack.pop();
	Relation init_relation = dbms.get_table(init_relation_name);

	//Execute first sub-query
	stack<string> sub_query;
	Relation sub_relation;
	while (query_stack.top() != "end")
	{
		smatch match;
		regex regex_query("select|project|rename|\\+|\\-|\\*|JOIN");
		//Get sub query parameters
		if (!regex_search(query_stack.top().cbegin(), query_stack.top().cend(), match, regex_query))
		{
			sub_query.push(query_stack.top());
			query_stack.pop();
		}
		//Get sub query type
		else if (regex_search(query_stack.top().cbegin(), query_stack.top().cend(), match, regex_query))
		{
			if (match[0] == "select")
			{
				query_stack.pop();
				sub_relation = process_select(sub_query, init_relation);
			}
			else if (match[0] == "project")
			{
				query_stack.pop();
				sub_relation= process_project(sub_query, init_relation);
			}
			else if (match[0] == "rename")
			{
				query_stack.pop();
				sub_relation = process_rename(sub_query, init_relation);
			}
			//TODO: INCLUDE + - * JOIN
		}
	}
	query_stack.pop();

	//Execute remaining sub-queries
	while (!query_stack.empty())
	{

	}
}

void Executer::process_cmd_stack(stack<string> stack)
{
	cmd_stack = stack;
}


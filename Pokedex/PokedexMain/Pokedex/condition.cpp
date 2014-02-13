#include "relation.h"

vector<bool> match_op(Relation* table, tuple<string, string, string, string> comparison)
{
	vector<string> column = table->select_column({ get<0>(comparison), get<1>(comparison) });

	vector<bool> test_result;
	if (get<2>(comparison) == "==")
	{
		if (get<1>(comparison) == "VARCHAR")
		{

			for (int i = 0; i < column.size(); i++)
			{
				if (column[i] == get<3>(comparison))
				{
					test_result.push_back(true);
				}
				else
				{
					test_result.push_back(false);
				}
			}
		}
		else
		{
			for (int i = 0; i < column.size(); i++)
			{
				if (stoi(column[i]) == stoi(get<3>(comparison)))
				{
					test_result.push_back(true);
				}
				else
				{
					test_result.push_back(false);
				}
			}
		}
	}
	else if (get<2>(comparison) == "!=")
	{
		if (get<1>(comparison) == "VARCHAR")
		{

			for (int i = 0; i < column.size(); i++)
			{
				if (column[i] != get<3>(comparison))
				{
					test_result.push_back(true);
				}
				else
				{
					test_result.push_back(false);
				}
			}
		}
		else
		{
			for (int i = 0; i < column.size(); i++)
			{
				if (stoi(column[i]) != stoi(get<3>(comparison)))
				{
					test_result.push_back(true);
				}
				else
				{
					test_result.push_back(false);
				}
			}
		}
	}
	else if (get<2>(comparison) == "<")
	{
		for (int i = 0; i < column.size(); i++)
		{
			if (stoi(column[i]) < stoi(get<3>(comparison)))
			{
				test_result.push_back(true);
			}
			else
			{
				test_result.push_back(false);
			}
		}
	}
	else if (get<2>(comparison) == ">")
	{
		for (int i = 0; i < column.size(); i++)
		{
			if (stoi(column[i]) > stoi(get<3>(comparison)))
			{
				test_result.push_back(true);
			}
			else
			{
				test_result.push_back(false);
			}
		}
	}
	else if (get<2>(comparison) == "<=")
	{
		for (int i = 0; i < column.size(); i++)
		{
			if (stoi(column[i]) <= stoi(get<3>(comparison)))
			{
				test_result.push_back(true);
			}
			else
			{
				test_result.push_back(false);
			}
		}
	}
	else if (get<2>(comparison) == ">=")
	{
		for (int i = 0; i < column.size(); i++)
		{
			if (stoi(column[i]) >= stoi(get<3>(comparison)))
			{
				test_result.push_back(true);
			}
			else
			{
				test_result.push_back(false);
			}
		}
	}


	return test_result;
}

void Conjunction::insert_comparison(string attr_name, string attr_type, string op, string value)
{
	comparisons.push_back(make_tuple(attr_name, attr_type, op, value));
}

Relation Conjunction::select_comparisons(Relation r) {

	Relation r_temp1 = r;
	Relation r_temp2;

	vector<bool> test_results;

	
	for (int i = 0; i < comparisons.size() ; ++i)	//Iterate through each comparison
	{
		for (int j = 0; j < r_temp1.attr_names.size(); j++)	//Iterate through all attribute names in the Relation
		{
			if (get<0>(comparisons[i]) == r_temp1.attr_names[j])	//Find the correct attribute name
			{
				r_temp2 = r_temp1;
				test_results = match_op(&r_temp2, comparisons[i]);
				for (int k = r_temp2.table.size() - 1; k > -1; k--)		//Iterate through each row of the Relation
				{
					if (test_results[k] == false)						//Find which comparisons failed
						r_temp1.table.erase(r_temp1.table.begin() + k);
				}
			}
		}
	}

	return r_temp1;
	
}

void Conjunction::delete_comparisons(Relation& r)
{
	int size_of_r;

	vector<bool> test_results;

	for (int i = 0; i < comparisons.size(); ++i)	//Iterate through each comparison
	{
		for (int j = 0; j < r.attr_names.size(); j++)	//Iterate through all attribute names in the Relation
		{
			if (get<0>(comparisons[i]) == r.attr_names[j])	//Find the correct attribute name
			{
				size_of_r = r.table.size();
				test_results = match_op(&r, comparisons[i]);
				for (int k = size_of_r - 1; k > -1; k--)	//Iterate through each row of the Relation
				{
					if (test_results[k] == true)		//Find which comparisons are true
						r.table.erase(r.table.begin() + k);
				}
			}
		}
	}
}

void Conjunction::update_comparisons(string value, Relation& r)
{
	int size_of_r;

	vector<bool> test_results;

	for (int i = 0; i < comparisons.size(); ++i)	//Iterate through each comparison
	{
		for (int j = 0; j < r.attr_names.size(); j++)	//Iterate through all attribute names in the Relation
		{
			if (get<0>(comparisons[i]) == r.attr_names[j])	//Find the correct attribute name
			{
				size_of_r = r.table.size();
				test_results = match_op(&r, comparisons[i]);
				for (int k = size_of_r - 1; k > -1; k--)	//Iterate through each row of the Relation
				{
					if (test_results[k] == true)	//Find which comparisons are true
						r.table[k][j] = value;
				}
			}
		}
	}
}

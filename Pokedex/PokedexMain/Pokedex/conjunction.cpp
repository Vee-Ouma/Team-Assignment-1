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

Relation Conjunction::select_comparisons(string new_table_name, Relation r) {

	vector<bool> test_results;

	for (int i = 0; i < comparisons.size(); ++i)	//Iterate through each comparison
	{
		for (int j = 0; j < r.attr_names.size(); j++)	//Iterate through all attribute names in the Relation
		{
			if (get<0>(comparisons[i]) == r.attr_names[j])	//Find the correct attribute name
			{
				test_results = match_op(&r, comparisons[i]);
				for (int k = r.table.size() - 1; k > -1; k--)		//Iterate through each row of the Relation
				{
					if (test_results[k] == false)						//Find which comparisons failed
						r.table.erase(r.table.begin() + k);
				}
			}
		}
	}

	r.name = new_table_name;

	return r;
}

void Conjunction::delete_comparisons(Relation& r)
{
	vector<bool> overall_results;
	for (int i = 0; i < r.table.size(); i++)	//Initialize overall_results vector to all true
		overall_results.push_back(true);

	for (int i = 0; i < comparisons.size(); ++i)	//Iterate through each comparison
	{
		for (int j = 0; j < r.attr_names.size(); j++)	//Iterate through all attribute names in the Relation
		{
			if (get<0>(comparisons[i]) == r.attr_names[j])	//Find the correct attribute name
			{
				vector<bool> iter_results;
				iter_results = match_op(&r, comparisons[i]);
				for (int k = 0; k < overall_results.size(); k++)	//AND together the overall results and the results of
					// the current comparison iteration
				{
					overall_results[k] = overall_results[k] && iter_results[k];
				}

			}
		}
	}

	for (int i = r.table.size() - 1; i > -1; i--)	//Iterate through each row of the Relation
	{
		if (overall_results[i] == true)		//If the result for the tuple was true for every comparison, delete that tuple
			r.table.erase(r.table.begin() + i);
	}
}

void Conjunction::update_comparisons(vector<tuple <string, string>> values, Relation& r)
{
	vector<bool> overall_results;
	for (int i = 0; i < r.table.size(); i++)	//Initialize overall_results vector to all true
		overall_results.push_back(true);

	for (int i = 0; i < comparisons.size(); ++i)	//Iterate through each comparison
	{
		for (int j = 0; j < r.attr_names.size(); j++)	//Iterate through all attribute names in the Relation
		{
			if (get<0>(comparisons[i]) == r.attr_names[j])	//Find the correct attribute name
			{
				vector<bool> iter_results;
				iter_results = match_op(&r, comparisons[i]);
				for (int k = 0; k < overall_results.size(); k++)	//AND together the overall results and the results of
					// the current comparison iteration
				{
					overall_results[k] = overall_results[k] && iter_results[k];
				}
			}
		}
	}

	for (int i = 0; i < overall_results.size(); i++)	//Iterate through each row of the Relation
	{
		if (overall_results[i] == true)	//Find which comparisons are true
		{
			for (int j = 0; j < values.size(); j++)	//Update the corresponding element for each element in values
			{
				for (int k = 0; k < r.attr_names.size(); k++)	//Find the correct attribute to change
				{
					if (get<0>(values[j]) == r.attr_names[k])
					{
						r.table[i][k] = get<1>(values[j]);
					}
				}
			}
		}
	}
}

void Conjunction::clear()
{
	comparisons.clear();
}

void Conjunction::show()
{
	for (auto i = 0; i < comparisons.size(); i++)
	{
		cout << get<0>(comparisons[i]) << " "
			 << get<1>(comparisons[i]) << " "
			 << get<2>(comparisons[i]) << " "
			 << get<3>(comparisons[i]) << "\n";
	}
}
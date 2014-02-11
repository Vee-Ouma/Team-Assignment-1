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

void Conjunction::insert_conj(string attr_name, string attr_type, string op, string value)
{
	comparisons.push_back(make_tuple(attr_name, attr_type, op, value));
}

Relation r_temp1;

void* Conjunction::match_comparisons(void* v_ptr) {

	
	Relation r_temp2;

	Relation* table = (Relation*)v_ptr;

	r_temp1 = (*table);

	vector<bool> test_results;

	for (int i = 0; i < comparisons.size() ; ++i)
	{
		for (int j = 0; j < table->attr_names.size(); j++)
		{
			//if (get<0>(comparisons[i]) == table->attr_names[j])
			if (get<0>(comparisons[i]) == table->attr_names[j])
			{
				r_temp2 = r_temp1;
				test_results = match_op(&r_temp2, comparisons[i]);
				for (int k = r_temp2.table.size() - 1; k > -1; k--)
				{
					if (test_results[k] == false)
						r_temp1.table.erase(r_temp1.table.begin() + k);
				}
			}
		}
	}

	return &r_temp1;
	
}

void Conjunction::delete_comparisons(void* v_ptr)
{
	Relation r_temp2;

	Relation* table = (Relation*)v_ptr;

	r_temp1 = (*table);

	vector<bool> test_results;

	for (int i = 0; i < comparisons.size(); ++i)
	{
		for (int j = 0; j < table->attr_names.size(); j++)
		{
			//if (get<0>(comparisons[i]) == table->attr_names[j])
			if (get<0>(comparisons[i]) == table->attr_names[j])
			{
				r_temp2 = r_temp1;
				test_results = match_op(&r_temp2, comparisons[i]);
				for (int k = r_temp2.table.size() - 1; k > -1; k--)
				{
					if (test_results[k] == false)
						r_temp1.table.erase(r_temp1.table.begin() + k);
				}
			}
		}
	}

	table = &r_temp1;
}

void Conjunction::update_comparisons(string value, void* v_ptr)
{
	Relation r_temp2;

	Relation* table = (Relation*)v_ptr;

	r_temp1 = (*table);

	vector<bool> test_results;

	for (int i = 0; i < comparisons.size(); ++i)
	{
		for (int j = 0; j < table->attr_names.size(); j++)
		{
			//if (get<0>(comparisons[i]) == table->attr_names[j])
			if (get<0>(comparisons[i]) == table->attr_names[j])
			{
				r_temp2 = r_temp1;
				test_results = match_op(&r_temp2, comparisons[i]);
				for (int k = r_temp2.table.size() - 1; k > -1; k--)
				{
					if (test_results[k] == true)
						r_temp1.table[k][j] = value;
				}
			}
		}
	}

	table = &r_temp1;
}

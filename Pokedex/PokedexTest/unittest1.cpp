#include "stdafx.h"
#include "CppUnitTest.h"
#include "relation.h"
#include <vector>
#include <string>
#include "parser.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PokedexTest
{		
	TEST_CLASS(TestRelationFile)
	{
	public:
		
		TEST_METHOD(TestIsEqualsStringVectorOperator)
		{
			// TODO: Your test code here
			bool test;
			vector<string> a;
			vector<string> b;

			a.push_back("Alex");
			a.push_back("is");
			a.push_back("the");
			a.push_back("BEST");

			b.push_back("Alex");
			b.push_back("is");
			b.push_back("the");
			b.push_back("BEST");

			if (a == b)
				test = true;
			else
				test = false;

			Assert::IsTrue(test);

			a[0] = "No one";

			if (a == b)
				test = true;
			else
				test = false;
			Assert::IsTrue(!test);

		}
		TEST_METHOD(CheckRowTest)
		{
			vector<string> keys;
			keys.push_back("Hydralisk");
			keys.push_back("Zergling");
			//keys.push_back("Hydralisk");

			vector<string> zerg;
			zerg.push_back("Zergling");
			zerg.push_back("Ultralisk");
			zerg.push_back("Roach");
			zerg.push_back("Baneling");
			zerg.push_back("Hydralisk");

			Assert::IsTrue(check_row(zerg, keys));

			zerg[0] = "Mutalisk";
			Assert::IsTrue(!check_row(zerg, keys));
		}

		TEST_METHOD(InsertRowTest)
		{
			Relation r;
			vector<string> vec;
			vector<string> vec2;

			vec.push_back("Zerg");
			vec.push_back("Hydralisk");
			vec.push_back("Mutalisk");

			vec2.push_back("Marine");
			vec2.push_back("Firebat");
			vec2.push_back("Siege Tank");

			r.insert_row(vec);
			r.insert_row(vec2);

			Assert::IsTrue(r.table[0] == vec); //if this test fails, check to see if TestIsEqualsStringVectorOperator passed
			Assert::IsTrue(r.table[1] == vec2);
		}
		TEST_METHOD(DeleteRowTest)
		{
			Relation r;
			vector<string> vec;
			vector<string> vec2;
			vector<string> keylist;

			vec.push_back("Zerg");
			vec.push_back("Hydralisk");
			vec.push_back("Mutalisk");

			vec2.push_back("Marine");
			vec2.push_back("Firebat");
			vec2.push_back("Siege Tank");

			keylist.push_back("Marine");

			r.insert_row(vec);
			r.insert_row(vec2);

			r.delete_row(keylist);

			Assert::IsTrue(r.table[0] == vec); //if this test fails, check to see if TestIsEqualsStringVectorOperator passed
			Assert::IsTrue(r.table.size() == 1);
		}
		TEST_METHOD(InsertColumnTest)
		{
			Relation r;
			vector<string> vec;
			vector<string> vec2;

			vec.push_back("Zerg");
			vec.push_back("Hydralisk");
			vec.push_back("Mutalisk");

			vec2.push_back("Marine");
			vec2.push_back("Firebat");
			vec2.push_back("Siege Tank");

			r.insert_column(vec, "Zerg", "string");
			r.insert_column(vec2, "Terran", "string");

			Assert::IsTrue(r.table[0][0] == vec[0]); //if this test fails, check to see if TestIsEqualsStringVectorOperator passed
			Assert::IsTrue(r.table[1][0] == vec[1]);
			Assert::IsTrue(r.table[2][0] == vec[2]);
			Assert::IsTrue(r.table[0][1] == vec2[0]);
			Assert::IsTrue(r.table[1][1] == vec2[1]);
			Assert::IsTrue(r.table[2][1] == vec2[2]);
		}

		TEST_METHOD(SelectColumnTest)
		{
			Relation r;
			vector<string> vec;
			vector<string> vec2;
			vector<string> vecback;
			vector<string> vec2back;
			vector<string> cond;
			vector<string> cond2;

			vec.push_back("Zerg");
			vec.push_back("Hydralisk");
			vec.push_back("Mutalisk");

			vec2.push_back("Marine");
			vec2.push_back("Firebat");
			vec2.push_back("Siege Tank");

			r.insert_column(vec, "Zerg", "string");
			r.insert_column(vec2, "Terran", "string");

			cond.push_back("Zerg");
			cond.push_back("string");

			cond2.push_back("Terran");
			cond2.push_back("string");

			vecback = r.select_column(cond);
			vec2back = r.select_column(cond2);

			Assert::IsTrue(vecback == vec); //if this test fails, check to see if TestIsEqualsStringVectorOperator passed
			Assert::IsTrue(vec2back == vec2);
		}
		TEST_METHOD(UpdateColumnTest)
		{
			Relation r;
			vector<string> vec;
			vector<string> vec2;
			vector<string> vecback;
			vector<string> vec2back;
			vector<string> updatevec2;
			vector<string> cond;
			vector<string> cond2;

			vec.push_back("Zerg");
			vec.push_back("Hydralisk");
			vec.push_back("Mutalisk");

			vec2.push_back("Marine");
			vec2.push_back("Firebat");
			vec2.push_back("Siege Tank");

			updatevec2.push_back("Ghost");
			updatevec2.push_back("Spider Mine");
			updatevec2.push_back("Medivac");

			r.insert_column(vec, "Zerg", "string");
			r.insert_column(vec2, "Terran", "string");

			cond.push_back("Zerg");
			cond.push_back("string");

			cond2.push_back("Terran");
			cond2.push_back("string");

			r.update_column(updatevec2, cond2);

			vecback = r.select_column(cond);
			vec2back = r.select_column(cond2);

			Assert::IsTrue(vecback == vec); //if this test fails, check to see if TestIsEqualsStringVectorOperator passed
			Assert::IsTrue(vec2back == updatevec2);
		}
		TEST_METHOD(UnionCompatibleTest)
		{
			Relation r;
			vector<string> col, col2, row, row2;

			col.push_back("Zerg");
			col.push_back("Hydralisk");
			col.push_back("Mutalisk");

			col2.push_back("Marine");
			col2.push_back("Firebat");
			col2.push_back("Siege Tank");

			r.insert_row(row);
			r.insert_row(row2);
			r.insert_column(col, "Zerg", "string");
			r.insert_column(col2, "Terran", "string");

			Relation r2;
			vector<string> colr2, col2r2, rowr2, row2r2;

			colr2.push_back("Roach");
			colr2.push_back("Ultralisk");
			colr2.push_back("Drone");

			col2r2.push_back("Ghost");
			col2r2.push_back("Medic");
			col2r2.push_back("Thor");

			r2.insert_row(rowr2);
			r2.insert_row(row2r2);
			r2.insert_column(colr2, "Zerg", "string");
			r2.insert_column(col2r2, "Terran", "string");

			Assert::IsTrue(r.union_compatible(r2)); 

			Relation r3;
			vector<string> colr3, col2r3, rowr3, row2r3;

			colr3.push_back("Zealot");
			colr3.push_back("Stalker");
			colr3.push_back("Carrier");

			col2r3.push_back("Ghost");
			col2r3.push_back("Medic");
			col2r3.push_back("Thor");

			r3.insert_row(rowr3);
			r3.insert_row(row2r3);
			r3.insert_column(colr3, "Protoss", "string");
			r3.insert_column(col2r3, "Terran", "string");

			Assert::IsTrue(!r.union_compatible(r3));
		}
		TEST_METHOD(RelationRenameTest)
		{
			Relation r;
			vector<string> col, col2, row, row2, attr;

			col.push_back("Zerg");
			col.push_back("Hydralisk");
			col.push_back("Mutalisk");

			col2.push_back("Marine");
			col2.push_back("Firebat");
			col2.push_back("Siege Tank");

			r.insert_row(row);
			r.insert_row(row2);
			r.insert_column(col, "Zerg", "string");
			r.insert_column(col2, "Terran", "string");

			Assert::IsTrue("" == r.name);

			attr.push_back("Zerg");
			attr.push_back("Terran");

			Relation r2 = r.renaming("Alex is AWESOME", attr);

			Assert::IsTrue("Alex is AWESOME" == r2.name);
		}
		TEST_METHOD(ProjectionTest)
		{
			Relation r;
			vector<string> col, col2, col3, row, row2, attr;

			col.push_back("Zergling");
			col.push_back("Hydralisk");
			col.push_back("Mutalisk");

			col2.push_back("Marine");
			col2.push_back("Firebat");
			col2.push_back("Siege Tank");

			col3.push_back("Archon");
			col3.push_back("Dark Archon");
			col3.push_back("Immortal");

			r.insert_column(col, "Zerg", "string");
			r.insert_column(col2, "Terran", "string");
			r.insert_column(col3, "Protoss", "string");

			attr.push_back("Zerg");
			attr.push_back("Protoss");

			Relation r2 = r.projection("Alex", attr);

			Assert::IsTrue(r.table[0][0] == "Zergling");
			Assert::IsTrue(r.table[1][0] == "Hydralisk");
			Assert::IsTrue(r.table[2][0] == "Mutalisk");

			Assert::IsTrue(r2.table[0][0] == "Zergling");
			Assert::IsTrue(r2.table[1][0] == "Hydralisk");
			Assert::IsTrue(r2.table[2][0] == "Mutalisk");
			Assert::IsTrue(r2.table[0][1] == "Archon");
			Assert::IsTrue(r2.table[1][1] == "Dark Archon");
			Assert::IsTrue(r2.table[2][1] == "Immortal");
		}

		TEST_METHOD(SetUnionTest)
		{
			Relation r;
			vector<string> col, col2, col3, row, row2, attr;

			col.push_back("Zergling");
			col.push_back("Hydralisk");
			col.push_back("Mutalisk");

			col2.push_back("Marine");
			col2.push_back("Firebat");
			col2.push_back("Siege Tank");

			col3.push_back("Archon");
			col3.push_back("Dark Archon");
			col3.push_back("Immortal");

			r.insert_column(col, "Zerg", "string");
			r.insert_column(col2, "Terran", "string");
			r.insert_column(col3, "Protoss", "string");

			Relation r2;
			vector<string> colr2, col2r2, col3r2, rowr2, row2r2, attrr2;

			colr2.push_back("Larva");
			colr2.push_back("Overlord");
			colr2.push_back("Queen");

			col2r2.push_back("Ghost");
			col2r2.push_back("Thor");
			col2r2.push_back("Medic");

			col3r2.push_back("Zealot");
			col3r2.push_back("Carrier");
			col3r2.push_back("Observer");

			r2.insert_column(colr2, "Zerg", "string");
			r2.insert_column(col2r2, "Terran", "string");
			r2.insert_column(col3r2, "Protoss", "string");

			Relation r3 = r.set_union("New Starcraft", r2);

			Assert::IsTrue(r3.table[0][0] == "Zergling");
			Assert::IsTrue(r3.table[1][0] == "Hydralisk");
			Assert::IsTrue(r3.table[2][0] == "Mutalisk");
			Assert::IsTrue(r3.table[0][1] == "Marine");
			Assert::IsTrue(r3.table[1][1] == "Firebat");
			Assert::IsTrue(r3.table[2][1] == "Siege Tank");
			Assert::IsTrue(r3.table[0][2] == "Archon");
			Assert::IsTrue(r3.table[1][2] == "Dark Archon");
			Assert::IsTrue(r3.table[2][2] == "Immortal");

			Assert::IsTrue(r3.table[3][0] == "Larva");
			Assert::IsTrue(r3.table[4][0] == "Overlord");
			Assert::IsTrue(r3.table[5][0] == "Queen");
			Assert::IsTrue(r3.table[3][1] == "Ghost");
			Assert::IsTrue(r3.table[4][1] == "Thor");
			Assert::IsTrue(r3.table[5][1] == "Medic");
			Assert::IsTrue(r3.table[3][2] == "Zealot");
			Assert::IsTrue(r3.table[4][2] == "Carrier");
			Assert::IsTrue(r3.table[5][2] == "Observer");
		}

		TEST_METHOD(SetDifferenceTest)
		{
			Relation r;
			vector<string> col, col2, col3, row, row2, attr;

			col.push_back("Zergling");
			col.push_back("Hydralisk");
			col.push_back("Mutalisk");
			//col.push_back("Larva");

			col2.push_back("Marine");
			col2.push_back("Firebat");
			col2.push_back("Siege Tank");

			col3.push_back("Archon");
			col3.push_back("Dark Archon");
			col3.push_back("Immortal");

			r.insert_column(col, "Zerg", "string");
			r.insert_column(col2, "Terran", "string");
			r.insert_column(col3, "Protoss", "string");

			Relation r2;
			vector<string> colr2, col2r2, col3r2, rowr2, row2r2, attrr2;

			colr2.push_back("Zergling");
			colr2.push_back("Hydralisk");
			colr2.push_back("Queen");

			col2r2.push_back("Marine");
			col2r2.push_back("Thor");
			col2r2.push_back("Medic");

			col3r2.push_back("Archon");
			col3r2.push_back("Carrier");
			col3r2.push_back("Observer");

			r2.insert_column(colr2, "Zerg", "string");
			r2.insert_column(col2r2, "Terran", "string");
			r2.insert_column(col3r2, "Protoss", "string");

			Relation r3 = r.set_difference("New Starcraft", r2);

			//Assert::IsTrue(r3.table[0][0] == "Zergling");
			Assert::IsTrue(r3.table[0][0] == "Hydralisk");
			Assert::IsTrue(r3.table[1][0] == "Mutalisk");
			//Assert::IsTrue(r3.table[0][1] == "Marine");
			Assert::IsTrue(r3.table[0][1] == "Firebat");
			Assert::IsTrue(r3.table[1][1] == "Siege Tank");
			//Assert::IsTrue(r3.table[0][2] == "Archon");
			Assert::IsTrue(r3.table[0][2] == "Dark Archon");
			Assert::IsTrue(r3.table[1][2] == "Immortal");


		}

		TEST_METHOD(CrossProductTest)
		{
			Relation r;
			vector<string> col, col2, col3, row, row2, attr;

			col.push_back("Zergling");
			col.push_back("Hydralisk");
			col.push_back("Mutalisk");

			col2.push_back("Marine");
			col2.push_back("Firebat");
			col2.push_back("Siege Tank");

			col3.push_back("Archon");
			col3.push_back("Dark Archon");
			col3.push_back("Immortal");

			r.insert_column(col, "Zerg", "string");
			r.insert_column(col2, "Terran", "string");
			r.insert_column(col3, "Protoss", "string");

			Relation r2;
			vector<string> colr2, col2r2, col3r2, rowr2, row2r2, attrr2;

			colr2.push_back("Larva");
			colr2.push_back("Overlord");
			colr2.push_back("Queen");

			col2r2.push_back("Ghost");
			col2r2.push_back("Thor");
			col2r2.push_back("Medic");

			col3r2.push_back("Zealot");
			col3r2.push_back("Carrier");
			col3r2.push_back("Observer");

			r2.insert_column(colr2, "Zerg1", "string");
			r2.insert_column(col2r2, "Terran1", "string");
			r2.insert_column(col3r2, "Protoss1", "string");

			Relation r3 = r.cross_product("New Starcraft", r2);

			Assert::IsTrue(r3.table[0][0] == "Zergling");
			Assert::IsTrue(r3.table[0][1] == "Marine");
			Assert::IsTrue(r3.table[0][2] == "Archon");
			Assert::IsTrue(r3.table[0][3] == "Larva");
			Assert::IsTrue(r3.table[0][4] == "Ghost");
			Assert::IsTrue(r3.table[0][5] == "Zealot");

			Assert::IsTrue(r3.table[3][0] == "Hydralisk");
			Assert::IsTrue(r3.table[3][1] == "Firebat");
			Assert::IsTrue(r3.table[3][2] == "Dark Archon");
			Assert::IsTrue(r3.table[3][3] == "Larva");
			Assert::IsTrue(r3.table[3][4] == "Ghost");
			Assert::IsTrue(r3.table[3][5] == "Zealot");	
		}
		TEST_METHOD(NaturalJoinTest)
		{
			Relation r;
			vector<string> col, col2, col3, row, row2, attr;

			col.push_back("Zergling");
			col.push_back("Hydralisk");
			col.push_back("Mutalisk");

			col2.push_back("Marine");
			col2.push_back("Firebat");
			col2.push_back("Siege Tank");

			col3.push_back("Archon");
			col3.push_back("Dark Archon");
			col3.push_back("Immortal");

			r.insert_column(col, "Zerg", "string");
			r.insert_column(col2, "Terran", "string");
			r.insert_column(col3, "Protoss", "string");

			Relation r2;
			vector<string> colr2, col2r2, col3r2, rowr2, row2r2, attrr2;

			colr2.push_back("Zergling");
			colr2.push_back("Hydralisk");
			colr2.push_back("Mutalisk");
			//colr2.push_back("Larva");
			//colr2.push_back("Overlord");
			//colr2.push_back("Queen");

			col2r2.push_back("Ghost");
			col2r2.push_back("Thor");
			col2r2.push_back("Medic");

			col3r2.push_back("Zealot");
			col3r2.push_back("Carrier");
			col3r2.push_back("Observer");

			r2.insert_column(colr2, "Zerg1", "string");
			r2.insert_column(col2r2, "Terran1", "string");
			r2.insert_column(col3r2, "Protoss1", "string");

			Relation r3 = r.natural_join("New Starcraft", r2);

			Assert::IsTrue(r3.table.size() == 0); //empty table

			Relation r4;
			vector<string> colr4, col2r4, col3r4, rowr4, row2r4, attrr4;

			colr4.push_back("Zergling");
			colr4.push_back("Infestor");
			colr4.push_back("Mutalisk");

			col2r4.push_back("Ghost");
			col2r4.push_back("Thor");
			col2r4.push_back("Medic");

			col3r4.push_back("Zealot");
			col3r4.push_back("Carrier");
			col3r4.push_back("Observer");

			r4.insert_column(colr2, "Zerg", "string");
			r4.insert_column(col2r2, "Terra1", "string");
			r4.insert_column(col3r2, "Protoss1", "string");

			Relation r5 = r.natural_join("New Starcraft", r4);

			Assert::IsTrue(r5.table.size() != 0);
			Assert::IsTrue(r5.table[0][0] == "Zergling");
			Assert::IsTrue(r5.table[0][1] == "Marine");
			Assert::IsTrue(r5.table[0][2] == "Archon");
			Assert::IsTrue(r5.table[0][3] == "Ghost");
			Assert::IsTrue(r5.table[0][4] == "Zealot");

			Assert::IsTrue(r5.table[1][0] == "Hydralisk");
			Assert::IsTrue(r5.table[1][1] == "Firebat");
			Assert::IsTrue(r5.table[1][2] == "Dark Archon");
			Assert::IsTrue(r5.table[1][3] == "Thor");
			Assert::IsTrue(r5.table[1][4] == "Carrier");

			Assert::IsTrue(r5.table[2][0] == "Mutalisk");
			Assert::IsTrue(r5.table[2][1] == "Siege Tank");
			Assert::IsTrue(r5.table[2][2] == "Immortal");
			Assert::IsTrue(r5.table[2][3] == "Medic");
			Assert::IsTrue(r5.table[2][4] == "Observer");
		}

		TEST_METHOD(ShowTest) //checks if show crashes
		{
			Relation r;
			vector<string> col, col2, col3, row, row2, attr;

			col.push_back("Zergling");
			col.push_back("Hydralisk");
			col.push_back("Mutalisk");

			col2.push_back("Marine");
			col2.push_back("Firebat");
			col2.push_back("Siege Tank");

			col3.push_back("Archon");
			col3.push_back("Dark Archon");
			col3.push_back("Immortal");

			r.insert_column(col, "Zerg", "string");
			r.insert_column(col2, "Terran", "string");
			r.insert_column(col3, "Protoss", "string");

			r.show();
		}
	};
	TEST_CLASS(TestParserFile)
	{
	public:

		TEST_METHOD(ProgramTest)
		{
			string s = "cats_or_dogs <- dogs + (select (kind == \"cat\") animals";

			stack<string> s_test;
			s_test.push("cats_or_dogs");
			s_test.push("NULL");
			s_test.push("animals");
			s_test.push("kind = cat");
			s_test.push("select");
			s_test.push("end");
			s_test.push("+");
			s_test.push("dogs");
			s_test.push("end");

			Parser p;
			p.program_test(s);
			while(!s_test.empty())
			{	
				Assert::IsTrue(s_test.top() == query_stack.top());
				s_test.pop();
				query_stack.pop();
			}
		}

	};
}
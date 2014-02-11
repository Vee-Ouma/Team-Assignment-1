#include "stdafx.h"
#include "CppUnitTest.h"
#include "relation.h"
#include <vector>
#include <string>


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

	};
}
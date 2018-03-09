#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "../lib/Dictionary.h"
#include "TestLoader.h"
#include "TestPrinter.h"

using namespace std;
using namespace lib;

namespace dictionaryTests
{
	auto printer = TestPrinter();
	const string dummyPath = "/path/to/somefile.txt";

    SCENARIO("Dictionary loads valid file")
    {
        GIVEN("A file containing valid dictionary entries")
        {
	        const string testFile = "first [adj]\nThis is the first definition.\n\nsecond [adv]\nThis is the second definition.\n\n";

            WHEN("The file is loaded")
            {
				auto loader = TestLoader();
				loader.setTestFile(testFile);
				auto dictionary = Dictionary(loader, printer);

				auto first = Word("first", "adj", "This is the first definition.", printer);
				auto second = Word("second", "adv", "This is the second definition.", printer);
				auto expected = map<string, Word>();
				expected.insert(pair<string, Word>("first", first));
				expected.insert(pair<string, Word>("second", second));

				auto actual = dictionary.loadDictionary(dummyPath);

                THEN("A corresponding collection of Words is created")
                {
					REQUIRE(expected == actual);
                }
            }
        }
    }

	SCENARIO("Dictionary loads file with missing word")
    {
	    GIVEN("A file containing a dictionary entry with missing word")
	    {
			const string testFile = "[adj]\nThis is the first definition.\n\n";

			WHEN("The file is loaded")
			{
				auto loader = TestLoader();
				loader.setTestFile(testFile);
				auto dictionary = Dictionary(loader, printer);
				map<string, Word> actual;

				try
				{
					actual = dictionary.loadDictionary(dummyPath);
				}
				catch (invalid_argument&)
				{
				}

				THEN("The collection of words should be empty")
				{
					REQUIRE(actual.empty());
				}
			}
	    }
    }

	SCENARIO("Dictionary loads file with missing type")
	{
		GIVEN("A file containing a dictionary entry with missing type")
		{
			const string testFile = "first []\nThis is the first definition.\n\n";

			WHEN("The file is loaded")
			{
				auto loader = TestLoader();
				loader.setTestFile(testFile);
				auto dictionary = Dictionary(loader, printer);
				auto actual = map<string, Word>();

				try
				{
					actual = dictionary.loadDictionary(dummyPath);
				}
				catch (invalid_argument&)
				{
				}

				THEN("The collection of words should be empty")
				{
					REQUIRE(actual.empty());
				}
			}
		}
	}

	SCENARIO("Dictionary loads file with missing definition")
	{
		GIVEN("A file containing a dictionary entry with missing definition")
		{
			const string testFile = "first [adj]\n\n\n";

			WHEN("The file is loaded")
			{
				auto loader = TestLoader();
				loader.setTestFile(testFile);
				auto dictionary = Dictionary(loader, printer);
				auto actual = map<string, Word>();

				try
				{
					actual = dictionary.loadDictionary(dummyPath);
				}
				catch (invalid_argument&)
				{
				}

				THEN("The collection of words should be empty")
				{
					REQUIRE(actual.empty());
				}
			}
		}
	}
}
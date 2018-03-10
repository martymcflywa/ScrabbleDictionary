#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "../lib/Dictionary.h"
#include "../lib/TextFileExtractor.h"
#include "TestLoader.h"
#include "TestPrinter.h"
#include "../lib/DefinitionFormatter.h"

using namespace std;
using namespace lib;

namespace dictionaryTests
{
    auto formatter = DefinitionFormatter();
    auto printer = TestPrinter(formatter);
    auto extractor = TextFileExtractor(printer);

    SCENARIO("Dictionary loads valid file")
    {
        GIVEN("A file containing valid dictionary entries")
        {
            string testFile = "first [adj]\nThis is the first definition.\n\nsecond [adv]\nThis is the second definition.\n\n";

            WHEN("The file is loaded")
            {
                auto loader = TestLoader();
                loader.setTestFile(testFile);
                auto dictionary = Dictionary(loader, extractor);

                auto first = Word("first", "adj", "This is the first definition.", printer);
                auto second = Word("second", "adv", "This is the second definition.", printer);
                auto expected = map<string, Word>();
                expected.insert(pair<string, Word>("first", first));
                expected.insert(pair<string, Word>("second", second));

                auto actual = dictionary.loadDictionary();

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
            string testFile = "[adj]\nThis is the first definition.\n\n";

            WHEN("The file is loaded")
            {
                auto loader = TestLoader();
                loader.setTestFile(testFile);
                auto dictionary = Dictionary(loader, extractor);
                map<string, Word> actual;

                try
                {
                    actual = dictionary.loadDictionary();
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
            string testFile = "first []\nThis is the first definition.\n\n";

            WHEN("The file is loaded")
            {
                auto loader = TestLoader();
                loader.setTestFile(testFile);
                auto dictionary = Dictionary(loader, extractor);
                auto actual = map<string, Word>();

                try
                {
                    actual = dictionary.loadDictionary();
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
            string testFile = "first [adj]\n\n\n";

            WHEN("The file is loaded")
            {
                auto loader = TestLoader();
                loader.setTestFile(testFile);
                auto dictionary = Dictionary(loader, extractor);
                auto actual = map<string, Word>();

                try
                {
                    actual = dictionary.loadDictionary();
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
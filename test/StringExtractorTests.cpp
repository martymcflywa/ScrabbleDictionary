#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "TestLoader.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/EmptyStringException.h"
#include "../lib/StringExtractor.h"
#include "../lib/DictionaryTask.h"


using namespace std;
using namespace lib;

namespace stringExtractorTests
{
    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);
    auto task = DictionaryTask();
    auto extractor = StringExtractor(printer, task);

    SCENARIO("String extractor reads valid file")
    {
        GIVEN("A file containing valid dictionary entries")
        {
            const string testFile = "first [adj]\nThis is the first definition.\n\nsecond [adv]\nThis is the second definition.\n\n";

            WHEN("The extractor reads the file")
            {
                auto loader = TestLoader();
                loader.setTestFile(testFile);

                auto& content = loader.load();
                auto actual = extractor.extract(content);

                THEN("A corresponding collection of Words is created")
                {
                    auto first = Word("first", "adj", "This is the first definition.", printer);
                    auto second = Word("second", "adv", "This is the second definition.", printer);
                    auto expected = map<string, Word>();
                    expected.insert(pair<string, Word>("first", first));
                    expected.insert(pair<string, Word>("second", second));

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("String extractor reads file with missing word")
    {
        GIVEN("A file containing a dictionary entry with missing word")
        {
            const string testFile = "[adj]\nThis is the first definition.\n\n";

            WHEN("The extracor reads the file")
            {
                auto loader = TestLoader();
                loader.setTestFile(testFile);

                auto& content = loader.load();
                map<string, Word> actual;

                try
                {
                    actual = extractor.extract(content);
                }
                catch (EmptyStringException&) {}

                THEN("Nothing is extracted")
                {
                    REQUIRE(actual.empty());
                }
            }
        }
    }

    SCENARIO("String extractor reads file with missing type")
    {
        GIVEN("A file containing a dictionary entry with missing type")
        {
            const string testFile = "first []\nThis is the first definition.\n\n";

            WHEN("The extractor reads the file")
            {
                auto loader = TestLoader();
                loader.setTestFile(testFile);

                auto& content = loader.load();
                map<string, Word> actual;

                try
                {
                    actual = extractor.extract(content);
                }
                catch (EmptyStringException&) {}

                THEN("Nothing is extracted")
                {
                    REQUIRE(actual.empty());
                }
            }
        }
    }

    SCENARIO("String extractor reads file with missing definition")
    {
        GIVEN("A file containing a dictionary entry with missing definition")
        {
            const string testFile = "first [adj]\n\n\n";

            WHEN("The extractor reads the file")
            {
                auto loader = TestLoader();
                loader.setTestFile(testFile);

                auto& content = loader.load();
                map<string, Word> actual;

                try
                {
                    actual = extractor.extract(content);
                }
                catch (EmptyStringException&) {}

                THEN("Nothing is extracted")
                {
                    REQUIRE(actual.empty());
                }
            }
        }
    }
}

#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "TestLoader.h"
#include "TestPrinter.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/Dictionary.h"
#include "../lib/TextFileExtractor.h"

using namespace std;
using namespace lib;

namespace textFileExtractorTests
{
    auto formatter = DefinitionFormatter();
    auto printer = TestPrinter(formatter);
    auto extractor = TextFileExtractor(printer);

    SCENARIO("Extractor reads valid file")
    {
        GIVEN("A file containing valid dictionary entries")
        {
            string testFile = "first [adj]\nThis is the first definition.\n\nsecond [adv]\nThis is the second definition.\n\n";

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

    SCENARIO("Extractor reads file with missing word")
    {
        GIVEN("A file containing a dictionary entry with missing word")
        {
            string testFile = "[adj]\nThis is the first definition.\n\n";

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
                catch (invalid_argument&) {}

                THEN("Nothing is extracted")
                {
                    REQUIRE(actual.empty());
                }
            }
        }
    }

    SCENARIO("Extractor reads file with missing type")
    {
        GIVEN("A file containing a dictionary entry with missing type")
        {
            string testFile = "first []\nThis is the first definition.\n\n";

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
                catch (invalid_argument&) {}

                THEN("Nothing is extracted")
                {
                    REQUIRE(actual.empty());
                }
            }
        }
    }

    SCENARIO("Extractor reads file with missing definition")
    {
        GIVEN("A file containing a dictionary entry with missing definition")
        {
            string testFile = "first [adj]\n\n\n";

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
                catch (invalid_argument&) {}

                THEN("Nothing is extracted")
                {
                    REQUIRE(actual.empty());
                }
            }
        }
    }
}
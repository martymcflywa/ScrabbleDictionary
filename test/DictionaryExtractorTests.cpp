#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "TestHelpers.h"
#include "TestReader.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/DictionaryExtractor.h"
#include "../lib/DictionaryTask.h"
#include "../lib/EmptyStringException.h"
#include "../lib/WordFactory.h"

using namespace std;
using namespace lib;

namespace dictionaryExtractorTests
{
    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);
    auto task = DictionaryTask();
    auto extractor = DictionaryExtractor(printer, task);

    SCENARIO("Dictionary extractor reads valid file")
    {
        GIVEN("A file containing valid dictionary entries")
        {
            const string testFile = "first [adj]\nThis is the first definition.\n\nsecond [adv]\nThis is the second definition.\n\n";

            WHEN("The extractor reads the file")
            {
                auto reader = TestReader();
                reader.setTestFile(testFile);

                auto& content = reader.read();
                auto actual = extractor.extract(content);

                THEN("A corresponding collection of Words is created")
                {
                    auto expected = unordered_map<string, shared_ptr<Word>>
                    {
                        { "first", make_shared<Word>(WordFactory::build("first", "adj", "This is the first definition.", printer)) },
                        { "second", make_shared<Word>(WordFactory::build("second", "adv", "This is the second definition.", printer)) }
                    };

                    for(auto expectedIt = expected.begin(), actualIt = actual.begin();
                        expectedIt != expected.end() || actualIt != actual.end();
                        ++expectedIt, ++actualIt)
                    {
                        REQUIRE(expectedIt->first == actualIt->first);
                        REQUIRE(TestHelpers::isSmartPtrEqual(expectedIt->second, actualIt->second));
                    }
                }
            }
        }
    }

    SCENARIO("Dictionary extractor reads file with missing word")
    {
        GIVEN("A file containing a dictionary entry with missing word")
        {
            const string testFile = "[adj]\nThis is the first definition.\n\n";

            WHEN("The extracor reads the file")
            {
                auto reader = TestReader();
                reader.setTestFile(testFile);

                auto& content = reader.read();
                unordered_map<string, shared_ptr<Word>> actual;

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

    SCENARIO("Dictionary extractor reads file with missing type")
    {
        GIVEN("A file containing a dictionary entry with missing type")
        {
            const string testFile = "first []\nThis is the first definition.\n\n";

            WHEN("The extractor reads the file")
            {
                auto reader = TestReader();
                reader.setTestFile(testFile);

                auto& content = reader.read();
                unordered_map<string, shared_ptr<Word>> actual;

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

    SCENARIO("Dictionary extractor reads file with missing definition")
    {
        GIVEN("A file containing a dictionary entry with missing definition")
        {
            const string testFile = "first [adj]\n\n\n";

            WHEN("The extractor reads the file")
            {
                auto reader = TestReader();
                reader.setTestFile(testFile);

                auto& content = reader.read();
                unordered_map<string, shared_ptr<Word>> actual;

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

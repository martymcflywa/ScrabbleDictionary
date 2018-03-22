#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "TestFileFactory.h"
#include "TestHelpers.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryExtractor.h"
#include "../lib/DictionaryTask.h"
#include "../lib/FileNotFoundException.h"
#include "../lib/TextFileReader.h"
#include "../lib/WordFactory.h"

using namespace std;
using namespace lib;

namespace textFileReaderTests
{
    string filepath = ".\\test.txt";

    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);
    auto task = DictionaryTask();
    auto extractor = DictionaryExtractor(printer, task);

    SCENARIO("File reader reads existing file")
    {
        GIVEN("A file that exists")
        {
            const string content = "first [adj]\nThis is the first definition.\n\nsecond [adv]\nThis is the second definition.\n\n";

            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            WHEN("The file is loaded")
            {
                auto reader = TextFileReader(filepath);
                auto& fileContent = reader.read();

                auto actual = extractor.extract(fileContent);

                // delete the test file, keep it out of version control
                reader.dispose();
                fileFactory.cleanup();

                THEN("The content matches input")
                {
                    auto expected = unordered_map<string, shared_ptr<Word>>
                    {
                        { "first", make_shared<Word>(WordFactory::build("first", "adj", "This is the first definition.", printer)) },
                        { "second", make_shared<Word>(WordFactory::build("second", "adv", "This is the second definition.", printer)) }
                    };

                    for (auto expectedIt = expected.begin(), actualIt = actual.begin();
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

    SCENARIO("File reader reads non existent file")
    {
        GIVEN("A file that doesn't exist")
        {
            WHEN("The file is read")
            {
                unique_ptr<TextFileReader> actual;

                try
                {
                    actual.reset(new TextFileReader(filepath));    
                }
                catch (FileNotFoundException&) {}

                THEN("File cannot be read")
                {
                    REQUIRE(actual == nullptr);
                }
            }
        }
    }
}

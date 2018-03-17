#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "TestHelpers.h"
#include "TestFileFactory.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryExtractor.h"
#include "../lib/DictionaryTask.h"
#include "../lib/FileNotFoundException.h"
#include "../lib/TextFileLoader.h"

using namespace std;
using namespace lib;

namespace textFileLoaderTests
{
    string filepath = ".\\test.txt";

    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);
    auto task = DictionaryTask();
    auto extractor = DictionaryExtractor(printer, task);

    SCENARIO("File loader loads existing file")
    {
        GIVEN("A file that exists")
        {
            const string content = "first [adj]\nThis is the first definition.\n\nsecond [adv]\nThis is the second definition.\n\n";

            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            WHEN("The file is loaded")
            {
                auto loader = TextFileLoader(filepath);
                auto& fileContent = loader.load();

                auto actual = extractor.extract(fileContent);

                // delete the test file, keep it out of version control
                loader.dispose();
                fileFactory.cleanup();

                THEN("The content matches input")
                {
                    auto expected = unordered_map<string, shared_ptr<Word>>
                    {
                        { "first", make_shared<Word>(Word("first", "adj", "This is the first definition.", printer)) },
                        { "second", make_shared<Word>(Word("second", "adv", "This is the second definition.", printer)) }
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

    SCENARIO("File loader loads non existent file")
    {
        GIVEN("A file that doesn't exist")
        {
            WHEN("The file is loaded")
            {
                unique_ptr<TextFileLoader> actual;

                try
                {
                    actual.reset(new TextFileLoader(filepath));    
                }
                catch (FileNotFoundException&) {}

                THEN("Loader is not created")
                {
                    REQUIRE(actual == nullptr);
                }
            }
        }
    }
}

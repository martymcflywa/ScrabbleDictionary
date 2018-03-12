#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "TestFileFactory.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/FileNotFoundException.h"
#include "../lib/RegexExtractor.h"
#include "../lib/TextFileLoader.h"

using namespace std;

namespace textFileLoaderTests
{
    string filepath = ".\\test.txt";

    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);
    auto extractor = RegexExtractor(printer);

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

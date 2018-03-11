#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "../lib/TextFileLoader.h"
#include "../lib/TextFileExtractor.h"
#include "../lib/Dictionary.h"
#include "TestFileFactory.h"
#include "TestPrinter.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/FileNotFoundException.h"

using namespace std;

namespace textFileLoaderTests
{
    string filepath = ".\\test.txt";

    auto formatter = DefinitionFormatter();
    auto printer = TestPrinter(formatter);
    auto extractor = TextFileExtractor(printer);

    SCENARIO("File loader loads existing file")
    {
        GIVEN("A file that exists")
        {
            string content = "first [adj]\nThis is the first definition.\n\nsecond [adv]\nThis is the second definition.\n\n";

            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            WHEN("The file is loaded")
            {
                auto loader = TextFileLoader(filepath);
                auto dictionary = Dictionary(loader, extractor);

                auto first = Word("first", "adj", "This is the first definition.", printer);
                auto second = Word("second", "adv", "This is the second definition.", printer);
                auto expected = map<string, Word>();
                expected.insert(pair<string, Word>("first", first));
                expected.insert(pair<string, Word>("second", second));

                auto actual = dictionary.loadDictionary();

                // delete the test file, keep it out of version control
                fileFactory.cleanup();

                THEN("The content matches input")
                {
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
                catch (FileNotFoundException&)
                {
                }

                THEN("Loader is not created")
                {
                    REQUIRE(actual == nullptr);
                }
            }
        }
    }
}

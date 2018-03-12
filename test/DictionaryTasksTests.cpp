#include "stdafx.h"
#include "catch.hpp"
#include "TestFileFactory.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/StringExtractor.h"
#include "../lib/TextFileLoader.h"

using namespace std;

namespace dictionaryTasksTests
{
    string filepath = ".\\test.txt";

    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);
    auto extractor = StringExtractor(printer);

    SCENARIO("Dictionary prints definition for existing word")
    {
        GIVEN("A dictionary with a word")
        {
            const string content = "first [adj]\nThis is the first definition.\n\n";
            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto loader = TextFileLoader(filepath);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            WHEN("The dictionary is searched for an existing word")
            {
                const auto actual = dictionary.getDefinition("first");

                THEN("The definition is printed")
                {
                    const auto expectedType = WordType::getName(Adjective) + ":\n";
                    const auto expected = expectedType + "This is the first definition.";

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("Dictionary prints definition for non existent word")
    {
        GIVEN("A dictionary with a word")
        {
            const string content = "first [adj]\nThis is the first definition.\n\n";
            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto loader = TextFileLoader(filepath);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            WHEN("The dictionary is searched for a non existent word")
            {
                const string word = "second";
                const auto actual = dictionary.getDefinition(word);

                THEN("The word is not found")
                {
                    const auto expected = "Word " + word + " not found";

                    REQUIRE(expected == actual);
                }
            }
        }
    }
}
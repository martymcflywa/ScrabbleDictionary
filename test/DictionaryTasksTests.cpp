#include "stdafx.h"
#include <algorithm>
#include "catch.hpp"
#include "TestFileFactory.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryTask.h"
#include "../lib/StringExtractor.h"
#include "../lib/TextFileLoader.h"

using namespace std;

namespace dictionaryTasksTests
{
    string filepath = ".\\test.txt";

    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);

    SCENARIO("Dictionary prints definition for existing word")
    {
        GIVEN("A dictionary with a word")
        {
            const string content = "first [adj]\nThis is the first definition.\n\n";
            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto task = DictionaryTask();
            auto loader = TextFileLoader(filepath);
            auto extractor = StringExtractor(printer, task);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            WHEN("The dictionary is searched for an existing word")
            {
                const auto actual = dictionary.getDefinition("first");

                // delete the test file, keep it out of version control
                loader.dispose();
                fileFactory.cleanup();

                THEN("The definition is printed")
                {
                    const auto expectedType = WordType::getName(Adjective) + " ";
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

            auto task = DictionaryTask();
            auto loader = TextFileLoader(filepath);
            auto extractor = StringExtractor(printer, task);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            WHEN("The dictionary is searched for a non existent word")
            {
                const string word = "second";
                const auto actual = dictionary.getDefinition(word);

                // delete the test file, keep it out of version control
                loader.dispose();
                fileFactory.cleanup();

                THEN("The word is not found")
                {
                    const auto expected = "Word " + word + " not found";

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    bool contains(list<string> list, const string& target)
    {
        return find(list.begin(), list.end(), target) != list.end();
    }

    SCENARIO("Find longest word where the dictionary contains a single longest word")
    {
        GIVEN("A dictionary with a short word and a long word")
        {
            const string shortWord = "XY";
            const string longWord = "XYZ";
            const string typeAndDef = " [n]\nThe definition.\n\n";

            const string content =
                string(shortWord + typeAndDef) +
                string(longWord + typeAndDef);
            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto task = DictionaryTask();
            auto loader = TextFileLoader(filepath);
            auto extractor = StringExtractor(printer, task);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            WHEN("The longest word is requested")
            {
                const auto actual = dictionary.getLongestWords();

                // delete the test file, keep it out of version control
                loader.dispose();
                fileFactory.cleanup();

                THEN("The dictionary returns the longest word")
                {
                    // assert long word is in the list
                    REQUIRE(contains(actual, longWord));
                    // assert short word is not in the list
                    REQUIRE(!contains(actual, shortWord));
                }
            }
        }
    }

    SCENARIO("Find the longest words where the dictionary contains multiple longest words")
    {
        GIVEN("A dictionary with a short word and two longest words")
        {
            const string shortWord = "AB";
            const string longWord1 = "ABC";
            const string longWord2 = "XYZ";
            const string typeAndDef = " [n]\nThe definition.\n\n";

            const string content =
                string(shortWord + typeAndDef) +
                string(longWord1 + typeAndDef) +
                string(longWord2 + typeAndDef);
            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto task = DictionaryTask();
            auto loader = TextFileLoader(filepath);
            auto extractor = StringExtractor(printer, task);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            WHEN("The longest word is requested")
            {
                const auto actual = dictionary.getLongestWords();

                // delete the test file, keep it out of version control
                loader.dispose();
                fileFactory.cleanup();

                THEN("The dictionary returns both longest words")
                {
                    // assert longest words are in the list
                    REQUIRE(contains(actual, longWord1));
                    REQUIRE(contains(actual, longWord2));

                    // assert short word is not in the list
                    REQUIRE(!contains(actual, shortWord));
                }
            }
        }
    }

    SCENARIO("Find words that end in 'logy' that have a length of seven or less characters")
    {
        GIVEN("A dictionary with words that end in 'logy' that have a length of seven or less characters")
        {
            const string logy0 = "logy";
            const string logy1 = "5logy";
            const string logy2 = "56logy";
            const string logy3 = "567logy";
            const string logy4 = "5678logy";
            const string notLogy = "logynot";

            const string content = 
                string(logy0 + " [n]\nlogy0\n\n") +
                string(logy1 + " [n]\nlogy1\n\n") +
                string(logy2 + " [n]\nlogy2\n\n") +
                string(logy3 + " [n]\nlogy3\n\n") +
                string(logy4 + " [n]\nlogy4\n\n") +
                string(notLogy + " [n]\nnotLogy\n\n");
            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto task = DictionaryTask();
            auto loader = TextFileLoader(filepath);
            auto extractor = StringExtractor(printer, task);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            WHEN("The logy words are requested")
            {
                const auto actual = dictionary.getLogyWords();

                // delete the test file, keep it out of version control
                loader.dispose();
                fileFactory.cleanup();

                THEN("Only words that end in 'logy' and have a length of seven or less characters are returned")
                {
                    // assert these words are in the list
                    REQUIRE(contains(actual, logy0));
                    REQUIRE(contains(actual, logy1));
                    REQUIRE(contains(actual, logy2));
                    REQUIRE(contains(actual, logy3));
                    // assert these words are not in the list
                    REQUIRE(!contains(actual, logy4));
                    REQUIRE(!contains(actual, notLogy));
                }
            }
        }
    }
}
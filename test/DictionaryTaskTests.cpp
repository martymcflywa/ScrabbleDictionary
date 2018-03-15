#include "stdafx.h"
#include "catch.hpp"
#include "TestFileFactory.h"
#include "TestHelpers.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryTask.h"
#include "../lib/StringExtractor.h"
#include "../lib/TextFileLoader.h"

using namespace std;
using namespace lib;

namespace dictionaryTaskTests
{
    const std::string filepath = ".\\test.txt";

    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);

    SCENARIO("Find a word definition")
    {
        GIVEN("A dictionary with a word")
        {
            // TODO: define all this boilerplate stuff in a scenario builder
            const string foundWord = "first";
            const string typeAndDef = " [adj]\nThe definition.\n\n";
            const auto content = foundWord + typeAndDef;
            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto task = DictionaryTask();
            auto loader = TextFileLoader(filepath);
            auto extractor = StringExtractor(printer, task);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            // delete the test file, keep it out of version control
            loader.dispose();
            fileFactory.cleanup();

            WHEN("The dictionary is searched for an existing word")
            {
                const auto actual = dictionary.getDefinition(foundWord);

                THEN("The definition is printed")
                {
                    const auto expectedType = WordType::getName(Adjective);
                    const auto expected = expectedType + " The definition.";

                    REQUIRE(expected == actual);
                }
            }

            AND_WHEN("The dictionary is searched for a non existent word")
            {
                const string notFoundWord = "second";
                const auto actual = dictionary.getDefinition(notFoundWord);

                THEN("The word is not found")
                {
                    const auto expected = "Word '" + notFoundWord + "' not found";

                    REQUIRE(expected == actual);
                }
            }
        }
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

            // delete the test file, keep it out of version control
            loader.dispose();
            fileFactory.cleanup();

            WHEN("The longest word is requested")
            {
                const auto actual = dictionary.getLongestWords();

                THEN("The dictionary returns the longest word")
                {
                    // assert long word is in the list
                    REQUIRE(TestHelpers::listContainsWord(actual, longWord));
                    // assert short word is not in the list
                    REQUIRE(!TestHelpers::listContainsWord(actual, shortWord));
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

            const auto content =
                shortWord + typeAndDef +
                longWord1 + typeAndDef +
                longWord2 + typeAndDef;
            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto task = DictionaryTask();
            auto loader = TextFileLoader(filepath);
            auto extractor = StringExtractor(printer, task);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            // delete the test file, keep it out of version control
            loader.dispose();
            fileFactory.cleanup();

            WHEN("The longest word is requested")
            {
                const auto actual = dictionary.getLongestWords();

                THEN("The dictionary returns both longest words")
                {
                    // assert longest words are in the list
                    REQUIRE(TestHelpers::listContainsWord(actual, longWord1));
                    REQUIRE(TestHelpers::listContainsWord(actual, longWord2));
                    // assert short word is not in the list
                    REQUIRE(!TestHelpers::listContainsWord(actual, shortWord));
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
            const string typeAndDef = " [n]\nThe definition.\n\n";

            const auto content =
                logy0 + typeAndDef +
                logy1 + typeAndDef +
                logy2 + typeAndDef +
                logy3 + typeAndDef +
                logy4 + typeAndDef +
                notLogy + typeAndDef;

            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto task = DictionaryTask();
            auto loader = TextFileLoader(filepath);
            auto extractor = StringExtractor(printer, task);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            // delete the test file, keep it out of version control
            loader.dispose();
            fileFactory.cleanup();

            WHEN("The logy words are requested")
            {
                const auto actual = dictionary.getLogyWords();

                THEN("Only words that end in 'logy' and have a length of seven or less characters are returned")
                {
                    // assert these words are in the list
                    REQUIRE(TestHelpers::listContainsWord(actual, logy0));
                    REQUIRE(TestHelpers::listContainsWord(actual, logy1));
                    REQUIRE(TestHelpers::listContainsWord(actual, logy2));
                    REQUIRE(TestHelpers::listContainsWord(actual, logy3));
                    // assert these words are not in the list
                    REQUIRE(!TestHelpers::listContainsWord(actual, logy4));
                    REQUIRE(!TestHelpers::listContainsWord(actual, notLogy));
                }
            }
        }
    }

    SCENARIO("Find words that rhyme")
    {
        GIVEN("A dictionary with words")
        {
            const string rhyme1 = "roy";
            const string rhyme2 = "troy";
            const string rhyme3 = "destroy";
            const string notRhyme1 = "oy";
            const string notRhyme2 = "joy";
            const string notRhyme3 = "royal";
            const string typeAndDef = " [n]\nThe definition.\n\n";

            const auto content =
                rhyme1 + typeAndDef +
                rhyme2 + typeAndDef +
                rhyme3 + typeAndDef +
                notRhyme1 + typeAndDef +
                notRhyme2 + typeAndDef +
                notRhyme3 + typeAndDef;
            auto fileFactory = TestFileFactory(filepath, content);
            fileFactory.write();

            auto task = DictionaryTask();
            auto loader = TextFileLoader(filepath);
            auto extractor = StringExtractor(printer, task);
            auto dictionary = Dictionary(loader, extractor);
            dictionary.loadDictionary();

            // delete the test file, keep it out of version control
            loader.dispose();
            fileFactory.cleanup();

            WHEN("A word that rhymes is searched")
            {
                const auto actual = dictionary.getRhymes(rhyme1);

                THEN("Only words that rhyme are returned")
                {
                    // assert words that rhyme are in the list
                    REQUIRE(TestHelpers::listContainsWord(actual, rhyme1));
                    REQUIRE(TestHelpers::listContainsWord(actual, rhyme2));
                    REQUIRE(TestHelpers::listContainsWord(actual, rhyme2));
                    // assert words that don't rhyme are not in the list
                    REQUIRE(!TestHelpers::listContainsWord(actual, notRhyme1));
                    REQUIRE(!TestHelpers::listContainsWord(actual, notRhyme2));
                    REQUIRE(!TestHelpers::listContainsWord(actual, notRhyme3));
                }
            }

            AND_WHEN("A word that doesn't rhyme is searched")
            {
                const string notRhyme = "nope";
                const auto actual = dictionary.getRhymes(notRhyme);

                THEN("No words are returned")
                {
                    REQUIRE(actual.empty());
                }
            }

            AND_WHEN("A word that is shorter than the rhyme itself is searched")
            {
                const string tooShort = "oy";
                const auto actual = dictionary.getRhymes(tooShort);

                THEN("No words are returned")
                {
                    REQUIRE(actual.empty());
                }
            }
        }
    }
}
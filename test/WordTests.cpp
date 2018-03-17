#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/EmptyStringException.h"
#include "../lib/UnsupportedTypeException.h"
#include "../lib/Word.h"
#include "TestHelpers.h"

using namespace std;
using namespace lib;

namespace wordTests
{
    const string testWord = "test";
    auto testType = Noun;
    const string testTypeString = "n";
    const string testDefinition = "This is a test description.";

    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);

    SCENARIO("Word getters")
    {
        GIVEN("An entry with a word, valid type and definition")
        {
            auto word = Word(testWord, testTypeString, testDefinition, printer);

            WHEN("The getters are called")
            {
                auto actualWord = word.getWord();
                auto actualType = word.getType();
                auto actualDefinition = word.getDefinition();

                THEN("The content matches input")
                {
                    REQUIRE(testWord == actualWord);
                    REQUIRE(testType == actualType);
                    REQUIRE(TestHelpers::stringContains(testDefinition, actualDefinition));
                }
            }

            AND_WHEN("The definition is printed")
            {
                const auto actual = word.printDefinition();

                THEN("The output includes the word type")
                {
                    const auto expectedType = WordType::getName(testType) + " ";
                    const auto expected = expectedType + testDefinition;

                    REQUIRE(TestHelpers::stringContains(expected, actual));
                }
            }
        }
    }

    SCENARIO("Word validation")
    {
        GIVEN("An entry with a word, invalid type and definition")
        {
            const string invalidType = "z";
            unique_ptr<Word> actual;

            WHEN("The word is constructed")
            {
                try
                {
                    actual.reset(new Word(testWord, invalidType, testDefinition, printer));
                }
                catch (UnsupportedTypeException&) {}

                THEN("The word is not created")
                {
                    REQUIRE(actual == nullptr);
                }
            }
        }

        GIVEN("An entry with an empty word, valid type and definition")
        {
            const string emptyWord = "";
            unique_ptr<Word> actual;

            WHEN("The word is constructed")
            {
                try
                {
                    actual.reset(new Word(emptyWord, testTypeString, testDefinition, printer));
                }
                catch (EmptyStringException&) {}

                THEN("The word is not created")
                {
                    REQUIRE(actual == nullptr);
                }
            }
        }

        GIVEN("An entry with a word, empty type, and definition")
        {
            const string emptyType = "";
            unique_ptr<Word> actual;

            WHEN("The word is constructed")
            {
                try
                {
                    actual.reset(new Word(testWord, emptyType, testDefinition, printer));
                }
                catch (EmptyStringException&) {}
                catch (UnsupportedTypeException&) {}

                THEN("The word is not created")
                {
                    REQUIRE(actual == nullptr);
                }
            }
        }

        GIVEN("An entry with a word, valid type, and empty definition")
        {
            const string emptyDefinition = "";
            unique_ptr<Word> actual;

            WHEN("The word is constructed")
            {
                try
                {
                    actual.reset(new Word(testWord, testTypeString, emptyDefinition, printer));
                }
                catch (EmptyStringException&) {}

                THEN("The word is not created")
                {
                    REQUIRE(actual == nullptr);
                }
            }
        }
    }

    SCENARIO("Word definitions")
    {
        GIVEN("A verb Word")
        {
            const string word = "test";
            const string type = "v";
            const string definiton = "this is a test";

            auto wordObj = Word(word, type, definiton, printer);

            WHEN("The word is printed")
            {
                const auto actual = wordObj.printDefinition();

                THEN("Verb prefixes the definition")
                {
                    const auto expectedType = WordType::getName(Verb) + " ";
                    const auto expected = expectedType + definiton;

                    REQUIRE(TestHelpers::stringContains(expected, actual));
                }
            }
        }

        GIVEN("A noun Word")
        {
            const string word = "test";
            const string type = "n";
            const string definiton = "this is a test";

            auto wordObj = Word(word, type, definiton, printer);

            WHEN("The word is printed")
            {
                const auto actual = wordObj.printDefinition();

                THEN("Noun prefixes the definition")
                {
                    const auto expectedType = WordType::getName(Noun) + " ";
                    const auto expected = expectedType + definiton;

                    REQUIRE(TestHelpers::stringContains(expected, actual));
                }
            }
        }

        GIVEN("An adverb Word")
        {
            const string word = "test";
            const string type = "adv";
            const string definiton = "this is a test";

            auto wordObj = Word(word, type, definiton, printer);

            WHEN("The word is printed")
            {
                const auto actual = wordObj.printDefinition();

                THEN("Adverb prefixes the definition")
                {
                    const auto expectedType = WordType::getName(Adverb) + " ";
                    const auto expected = expectedType + definiton;

                    REQUIRE(TestHelpers::stringContains(expected, actual));
                }
            }
        }

        GIVEN("An adjective Word")
        {
            const string word = "test";
            const string type = "adj";
            const string definiton = "this is a test";

            auto wordObj = Word(word, type, definiton, printer);

            WHEN("The word is printed")
            {
                const auto actual = wordObj.printDefinition();

                THEN("Adjective prefixes the definition")
                {
                    const auto expectedType = WordType::getName(Adjective) + " ";
                    const auto expected = expectedType + definiton;

                    REQUIRE(TestHelpers::stringContains(expected, actual));
                }
            }
        }

        GIVEN("A preposition Word")
        {
            const string word = "test";
            const string type = "prep";
            const string definiton = "this is a test";

            auto wordObj = Word(word, type, definiton, printer);

            WHEN("The word is printed")
            {
                const auto actual = wordObj.printDefinition();

                THEN("Preposition prefixes the definition")
                {
                    const auto expectedType = WordType::getName(Preposition) + " ";
                    const auto expected = expectedType + definiton;

                    REQUIRE(TestHelpers::stringContains(expected, actual));
                }
            }
        }

        GIVEN("A proper noun Word")
        {
            const string word = "test";
            const string type = "pn";
            const string definiton = "this is a test";

            auto wordObj = Word(word, type, definiton, printer);

            WHEN("The word is printed")
            {
                const auto actual = wordObj.printDefinition();

                THEN("Proper noun prefixes the definition")
                {
                    const auto expectedType = WordType::getName(ProperNoun) + " ";
                    const auto expected = expectedType + definiton;

                    REQUIRE(TestHelpers::stringContains(expected, actual));
                }
            }
        }

        GIVEN("A noun and verb Word")
        {
            const string word = "test";
            const string type = "n_and_v";
            const string definiton = "this is a test";

            auto wordObj = Word(word, type, definiton, printer);

            WHEN("The word is printed")
            {
                const auto actual = wordObj.printDefinition();

                THEN("Noun and verb prefixes the definition")
                {
                    const auto expectedType = WordType::getName(NounAndVerb) + " ";
                    const auto expected = expectedType + definiton;

                    REQUIRE(TestHelpers::stringContains(expected, actual));
                }
            }
        }

        GIVEN("A misc Word")
        {
            const string word = "test";
            const string type = "misc";
            const string definiton = "this is a test";

            auto wordObj = Word(word, type, definiton, printer);

            WHEN("The word is printed")
            {
                const auto actual = wordObj.printDefinition();

                THEN("Misc prefixes the definition")
                {
                    const auto expectedType = WordType::getName(Misc) + " ";
                    const auto expected = expectedType + definiton;

                    REQUIRE(TestHelpers::stringContains(expected, actual));
                }
            }
        }
    }
}

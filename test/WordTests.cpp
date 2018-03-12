#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/EmptyStringException.h"
#include "../lib/UnsupportedTypeException.h"
#include "../lib/Word.h"

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

    SCENARIO("Word with valid type")
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
                    REQUIRE(testDefinition == actualDefinition);
                }
            }

            AND_WHEN("The entry is printed")
            {
                const auto actual = word.printDefinition();

                THEN("The print output contains a type header with definition")
                {
                    const auto expectedType = WordType::getName(testType) + ":\n";
                    const auto expected = expectedType + testDefinition;

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("Word with invalid type")
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
    }

    SCENARIO("Word with empty word")
    {
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
    }

    SCENARIO("Word with empty type")
    {
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
    }

    SCENARIO("Word with empty definition")
    {
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

    SCENARIO("Word verb definition printing")
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
                    const auto expectedType = WordType::getName(Verb) + ":\n";
                    const auto expected = expectedType + definiton;

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("Word noun definition printing")
    {
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
                    const auto expectedType = WordType::getName(Noun) + ":\n";
                    const auto expected = expectedType + definiton;

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("Word adverb definition printing")
    {
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
                    const auto expectedType = WordType::getName(Adverb) + ":\n";
                    const auto expected = expectedType + definiton;

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("Word adjective definition printing")
    {
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
                    const auto expectedType = WordType::getName(Adjective) + ":\n";
                    const auto expected = expectedType + definiton;

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("Word preposition definition printing")
    {
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
                    const auto expectedType = WordType::getName(Preposition) + ":\n";
                    const auto expected = expectedType + definiton;

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("Word proper noun definition printing")
    {
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
                    const auto expectedType = WordType::getName(ProperNoun) + ":\n";
                    const auto expected = expectedType + definiton;

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("Word noun and verb definition printing")
    {
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
                    const auto expectedType = WordType::getName(NounAndVerb) + ":\n";
                    const auto expected = expectedType + definiton;

                    REQUIRE(expected == actual);
                }
            }
        }
    }

    SCENARIO("Word misc definition printing")
    {
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
                    const auto expectedType = WordType::getName(Misc) + ":\n";
                    const auto expected = expectedType + definiton;

                    REQUIRE(expected == actual);
                }
            }
        }
    }
}

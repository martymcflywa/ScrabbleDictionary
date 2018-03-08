#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "../lib/Word.h"
#include "TestPrinter.h"

using namespace std;
using namespace lib;

namespace wordTests
{
	const string testWord = "test";
	auto testType = Noun;
	const string testTypeString = "n";
	const string testDefinition = "This is a test description.";
	auto testPrinter = TestPrinter();

    SCENARIO("Word with valid type")
    {
        GIVEN("An entry with a word, valid type and definition")
        {
            auto word = Word(testWord, testTypeString, testDefinition, testPrinter);

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
                const string expectedTypeHeader = "Noun (n.):\n";
                const auto expected = expectedTypeHeader + testDefinition;

                word.printDefinition();
                auto actual = testPrinter.getOutput();

                THEN("The print output contains a type header with definition")
                {
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
					actual.reset(new Word(testWord, invalidType, testDefinition, testPrinter));
				}
				catch (invalid_argument&)
				{
				}

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
					actual.reset(new Word(emptyWord, testTypeString, testDefinition, testPrinter));
				} catch (invalid_argument&)
				{
				}

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
					actual.reset(new Word(testWord, emptyType, testDefinition, testPrinter));
				}
				catch (invalid_argument&)
				{
				}

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
					actual.reset(new Word(testWord, testTypeString, emptyDefinition, testPrinter));
				}
				catch (invalid_argument&)
				{
				}

				THEN("The word is not created")
				{
					REQUIRE(actual == nullptr);
				}
			}
		}
	}
}

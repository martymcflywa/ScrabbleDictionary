#include "stdafx.h"
#include "catch.hpp"
#include <string>
#include "../lib/Word.h"
#include "TestPrinter.h"

using namespace std;
using namespace lib;

namespace wordTests
{
    SCENARIO("Word acceptance criteria")
    {
        GIVEN("An entry with a word, definition and valid type")
        {
            auto testPrinter = TestPrinter();
            const string expectedWord = "test";
            auto expectedType = Noun;
            const string expectedDefinition = "This is a test description.";

            auto word = Word(expectedWord, "[n]", expectedDefinition, testPrinter);

            WHEN("The getters are called")
            {
                auto actualWord = word.getWord();
                auto actualType = word.getType();
                auto actualDefinition = word.getDefinition();

                THEN("The content matches input")
                {
                    REQUIRE(expectedWord == actualWord);
                    REQUIRE(expectedType == actualType);
                    REQUIRE(expectedDefinition == actualDefinition);
                }
            }
            AND_WHEN("The entry is printed")
            {
                const string expectedTypeHeader = "Noun (n.):\n";
                const auto expected = expectedTypeHeader + expectedDefinition;

                word.printDefinition();
                auto actual = testPrinter.getOutput();

                THEN("The print output contains a type header with definition")
                {
                    REQUIRE(expected == actual);
                }
            }
        }
    }
}

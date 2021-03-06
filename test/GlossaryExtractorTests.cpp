#include "stdafx.h"
#include "catch.hpp"
#include "TestHelpers.h"
#include "TestReader.h"
#include "../lib/GlossaryExtractor.h"

using namespace std;
using namespace lib;

namespace glossaryExtractorTests
{
    auto extractor = GlossaryExtractor();

    SCENARIO("Glossary extractor reads valid file")
    {
        GIVEN("A multiline text file with words and punctuation")
        {
            const string word1 = "this";
            const string word2 = "is";
            const string word3 = "only-a";
            const string word4 = "test";
            const string word5 = "file";
            const string word6 = "can't";
            const string word7 = "preface";

            const auto testFile =
                "�" + word1 + "!� " + "\"" + word2 + "\"\n" +
                word3 + "--" + word4 + "\n" +
                "\tFILE" + "_" + word6 + "_\n"
                "﻿" + word7;

            auto reader = TestReader();
            reader.setTestFile(testFile);

            WHEN("The extractor reads the file")
            {
                auto& content = reader.read();
                auto actual = extractor.extract(content);

                THEN("Words without punctuation are returned")
                {
                    REQUIRE(TestHelpers::vectorContains(actual, word1));
                    REQUIRE(TestHelpers::vectorContains(actual, word2));
                    REQUIRE(TestHelpers::vectorContains(actual, word3));
                    REQUIRE(TestHelpers::vectorContains(actual, word4));
                    REQUIRE(TestHelpers::vectorContains(actual, word5));
                    REQUIRE(TestHelpers::vectorContains(actual, word6));
                    REQUIRE(TestHelpers::vectorContains(actual, word7));
                }
            }
        }
    }
}
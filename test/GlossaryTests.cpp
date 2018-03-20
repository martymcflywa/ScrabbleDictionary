#include "stdafx.h"
#include "catch.hpp"
#include <list>
#include "TestDictionaryBuilder.h"
#include "TestGlossaryBuilder.h"
#include "../lib/GlossaryFormatter.h"

using namespace std;
using namespace lib;

namespace glossaryTests
{
    const string word1 = "abc";
    const string word2 = "cab";
    const string word3 = "bca";
    const string word4 = "ab'c";
    const string word5 = "bac";
    const string usedTwice = "acb";
    const string notUsed = "xyz";
    const auto words = list<string>
    {
        word1, word2, word3, word4, word5, usedTwice, notUsed
    };
    const string usageText = "“abc!” _CAB?_\nbca, bac.\nab'c--acb; acb...";

    SCENARIO("Word usage")
    {
        GIVEN("A dictionary with words and a text file with words and special characters")
        {
            auto dictionaryBuilder = TestDictionaryBuilder(words);
            auto dictionary = dictionaryBuilder.build();

            WHEN("Glossary scans a text file for word usage")
            {
                auto reader = TestReader();
                reader.setTestFile(usageText);

                auto glossaryBuilder = TestGlossaryBuilder(dictionary);
                auto glossary = glossaryBuilder.build();
                glossary.setUsageFrequency(reader);

                THEN("Words used once are rare")
                {
                    for (auto& word : words)
                    {
                        if (word == usedTwice || word == notUsed)
                            continue;

                        REQUIRE(dictionary.isRareWord(word));
                    }
                }

                AND_THEN("Words used more than once are not rare")
                {
                    REQUIRE(!dictionary.isRareWord(usedTwice));
                }

                AND_THEN("Words not used are not rare")
                {
                    REQUIRE(!dictionary.isRareWord(notUsed));
                }
            }
        }
    }

    SCENARIO("Rare words")
    {
        GIVEN("A dictionary with rare words and a text file with words and special characters")
        {
            auto builder = TestDictionaryBuilder(words);
            auto dictionary = builder.build();

            auto reader = TestReader();
            reader.setTestFile(usageText);

            auto glossaryBuilder = TestGlossaryBuilder(dictionary);
            auto glossary = glossaryBuilder.build();
            glossary.setUsageFrequency(reader);

            WHEN("Glossary scans a text file for rare words")
            {
                const string rareText = "abc? Cab\ncab--BCA!\n_ab'c_ ABC\n“bac!” acb--";
                reader = TestReader();
                reader.setTestFile(rareText);

                glossary.generate(reader);
                glossary.write();

                const auto& actual = glossaryBuilder.getWriter().getContent();

                THEN("Rare words are included in the glossary")
                {
                    for (auto& word : words)
                    {
                        if (word == usedTwice || word == notUsed)
                            continue;
                            
                        REQUIRE(actual.find(word) != string::npos);
                    }
                }

                AND_THEN("Words used more than once are not included in the glossary")
                {
                    REQUIRE(actual.find(usedTwice) == string::npos);
                }

                AND_THEN("Words not used are not included in the glossary")
                {
                    REQUIRE(actual.find(notUsed) == string::npos);
                }
            }
        }
    }
}
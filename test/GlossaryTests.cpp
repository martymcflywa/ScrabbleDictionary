#include "stdafx.h"
#include "catch.hpp"
#include <list>
#include <map>
#include "TestDictionaryBuilder.h"
#include "TestGlossaryBuilder.h"
#include "TestHelpers.h"
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
    const string word6 = "acb";
    const auto words = list<string>
    {
        word1, word2, word3, word4, word5, word6
    };
    const string usageText = "“abc!” _CAB?_\nbca, bac.\nab'c--acb;";

    SCENARIO("Word usage")
    {
        GIVEN("A dictionary with words and a text file with words and special characters")
        {
            auto dictionaryBuilder = TestDictionaryBuilder(words);
            auto dictionary = dictionaryBuilder.build();

            WHEN("Glossary scans a text file for word usage")
            {
                auto loader = TestLoader();
                loader.setTestFile(usageText);
                auto glossaryBuilder = TestGlossaryBuilder(dictionary);
                auto glossary = glossaryBuilder.build();
                glossary.setUsageFrequency(loader);

                THEN("Words that exist in the dictionary have their usage incremented")
                {
                    for (auto& word : words)
                    {
                        REQUIRE(dictionary.isRareWord(word));
                    }
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

            auto loader = TestLoader();
            loader.setTestFile(usageText);
            auto glossaryBuilder = TestGlossaryBuilder(dictionary);
            auto glossary = glossaryBuilder.build();
            glossary.setUsageFrequency(loader);

            WHEN("Glossary scans a text file for rare words")
            {
                const string rareText = "abc? Cab\ncab--BCA!\n_ab'c_ ABC\n“bac!” acb--";
                loader = TestLoader();
                loader.setTestFile(rareText);

                auto formatter = GlossaryFormatter();
                const auto actual = glossary.generateGlossary(loader, formatter);

                THEN("Rare words are found")
                {
                    for (auto& word : words)
                    {
                        REQUIRE(TestHelpers::mapContains(actual, word));
                    }
                }
            }
        }
    }
}
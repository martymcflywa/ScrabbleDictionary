#include "stdafx.h"
#include "catch.hpp"
#include "TestDictionaryBuilder.h"
#include "TestHelpers.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"

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
            const string foundWord = "first";
            const string type = " [adj]\n";
            const string definition = "The definition.";
            const auto typeAndDef = type + definition + "\n\n";

            auto builder = TestDictionaryBuilder(foundWord, typeAndDef);
            auto dictionary = builder.build();

            WHEN("The dictionary is searched for an existing word")
            {
                const auto actual = dictionary.getDefinition(foundWord);

                THEN("The definition is printed")
                {
                    const auto expectedType = WordType::getName(Adjective);
                    const auto expected = expectedType + " " + definition;

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
            const auto words = list<string>{ shortWord, longWord };

            auto builder = TestDictionaryBuilder(words);
            auto dictionary = builder.build();

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
            const auto words = list<string>{ shortWord, longWord1, longWord2 };

            auto builder = TestDictionaryBuilder(words);
            auto dictionary = builder.build();

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
            const string logy1 = "logy";
            const string logy2 = "5logy";
            const string logy3 = "56logy";
            const string logy4 = "567logy";
            const string notLogy1 = "5678logy";
            const string notLogy2 = "logynot";
            const auto words = list<string>
            {
                logy1,
                logy2,
                logy3,
                logy4,
                notLogy1,
                notLogy2
            };

            auto builder = TestDictionaryBuilder(words);
            auto dictionary = builder.build();

            WHEN("The logy words are requested")
            {
                const auto actual = dictionary.getLogyWords();

                THEN("Only words that end in 'logy' and have a length of seven or less characters are returned")
                {
                    // assert these words are in the list
                    REQUIRE(TestHelpers::listContainsWord(actual, logy1));
                    REQUIRE(TestHelpers::listContainsWord(actual, logy2));
                    REQUIRE(TestHelpers::listContainsWord(actual, logy3));
                    REQUIRE(TestHelpers::listContainsWord(actual, logy4));
                    // assert these words are not in the list
                    REQUIRE(!TestHelpers::listContainsWord(actual, notLogy1));
                    REQUIRE(!TestHelpers::listContainsWord(actual, notLogy2));
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
            const auto words = list<string>
            {
                rhyme1,
                rhyme2,
                rhyme3,
                notRhyme1,
                notRhyme2,
                notRhyme3
            };

            auto builder = TestDictionaryBuilder(words);
            auto dictionary = builder.build();

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

    SCENARIO("Calculate scrabble scores")
    {
        const string definition = "\nTest definition.\n\n";

        GIVEN("A dictionary with all word types")
        {
            const string adjectiveWord = "quixotic";
            const auto adjectiveTypeDef = " [adj]" + definition;
            const auto expectedAdjectiveScore = 26;

            const string adverbWord = "quizzically";
            const auto adverbTypeDef = " [adv]" + definition;
            const auto expectedAdverbScore = 43;

            const string nounWord = "zephyr";
            const auto nounTypeDef = " [n]" + definition;
            const auto expectedNounScore = 23;

            const string nounAndVerbWord = "whistle";
            const auto nounAndVerbTypeDef = " [n_and_v]" + definition;
            const auto expectedNounAndVerbScore = 13;

            const string prepositionWord = "versus";
            const auto prepositionTypeDef = " [prep]" + definition;
            const auto expectedPrepositionScore = 9;

            const string verbWord = "quadruplicated";
            const auto verbTypeDef = " [v]" + definition;
            const auto expectedVerbScore = 29;

            const string miscWord = "misc";
            const auto miscWordTypeDef = " [misc]" + definition;
            const auto expectedMiscScore = 0;

            const string properNounWord = "propernoun";
            const auto properNounTypeDef = " [pn]" + definition;
            const auto expectedProperNounScore = 0;

            const string hyphenWord = "hyphen-word";
            const auto hyphenTypeDef = " [v]" + definition;
            const auto expectedHyphenScore = 0;

            const auto words = list<string>
            {
                adjectiveWord,
                adverbWord,
                nounWord,
                nounAndVerbWord,
                prepositionWord,
                verbWord,
                miscWord,
                properNounWord,
                hyphenWord
            };
            const auto typeAndDefs = list<string>
            {
                adjectiveTypeDef,
                adverbTypeDef,
                nounTypeDef,
                nounAndVerbTypeDef,
                prepositionTypeDef,
                verbTypeDef,
                miscWordTypeDef,
                properNounTypeDef,
                hyphenTypeDef
            };

            auto builder = TestDictionaryBuilder(words, typeAndDefs);
            auto dictionary = builder.build();

            WHEN("The score is requested for each word")
            {
                auto actualAdjectiveScore = dictionary.getScrabbleScore(adjectiveWord);
                auto actualAdverbScore = dictionary.getScrabbleScore(adverbWord);
                auto actualNounScore = dictionary.getScrabbleScore(nounWord);
                auto actualNounAndVerbScore = dictionary.getScrabbleScore(nounAndVerbWord);
                auto actualPrepositionScore = dictionary.getScrabbleScore(prepositionWord);
                auto actualVerbScore = dictionary.getScrabbleScore(verbWord);
                auto actualMiscScore = dictionary.getScrabbleScore(miscWord);
                auto actualProperNounScore = dictionary.getScrabbleScore(properNounWord);
                auto actualHyphenScore = dictionary.getScrabbleScore(hyphenWord);

                THEN("An adjective word can score")
                {
                    REQUIRE(expectedAdjectiveScore == actualAdjectiveScore);
                }

                AND_THEN("An adverb word can score")
                {
                    REQUIRE(expectedAdverbScore == actualAdverbScore);
                }

                AND_THEN("A noun word can score")
                {
                    REQUIRE(expectedNounScore == actualNounScore);
                }

                AND_THEN("A noun and verb word can score")
                {
                    REQUIRE(expectedNounAndVerbScore == actualNounAndVerbScore);
                }

                AND_THEN("A preposition word can score")
                {
                    REQUIRE(expectedPrepositionScore == actualPrepositionScore);
                }
                
                AND_THEN("A verb word can score")
                {
                    REQUIRE(expectedVerbScore == actualVerbScore);
                }

                AND_THEN("A misc word can't score")
                {
                    REQUIRE(expectedMiscScore == actualMiscScore);
                }

                AND_THEN("A proper noun word can't score")
                {
                    REQUIRE(expectedProperNounScore == actualProperNounScore);
                }

                AND_THEN("A hyphen word can't score")
                {
                    REQUIRE(expectedHyphenScore == actualHyphenScore);
                }
            }

            AND_WHEN("A score is requested for a non existent word")
            {
                auto actual = dictionary.getScrabbleScore("nope");

                THEN("A negative score is returned")
                {
                    REQUIRE(actual == -1);
                }
            }
        }
    }
}
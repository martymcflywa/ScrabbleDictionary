#include "stdafx.h"
#include "catch.hpp"
#include "TestDictionaryBuilder.h"
#include "TestHelpers.h"
#include "../lib/Dictionary.h"

using namespace std;
using namespace lib;

namespace dictionaryTaskTests
{
    SCENARIO("Find a word definition and scrabble score")
    {
        const string foundWord = "first";
        const string type = " [adj]\n";
        const string definition = "The definition.";
        const auto typeAndDef = type + definition + "\n\n";

        GIVEN("A dictionary with a word")
        {
            auto builder = TestDictionaryBuilder(foundWord, typeAndDef);
            auto dictionary = builder.build();

            WHEN("The dictionary is searched for an existing word")
            {
                const auto actual = dictionary.getDefinition(foundWord);

                THEN("The definition and scrabble score is printed")
                {
                    const auto expectedType = WordType::getName(Adjective);
                    const auto expectedScore = dictionary.getScrabbleScore(foundWord);
                    const auto expected = expectedType + " " + definition + 
                        "\nScrabble score for '" + foundWord + "': " + to_string(expectedScore);

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

    SCENARIO("Find longest words in the dictionary")
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
                    REQUIRE(TestHelpers::listContainsWord(actual, longWord));
                }
                
                AND_THEN("The dictionary does not return the short word")
                {
                    REQUIRE(!TestHelpers::listContainsWord(actual, shortWord));
                }
            }
        }

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
                    REQUIRE(TestHelpers::listContainsWord(actual, longWord1));
                    REQUIRE(TestHelpers::listContainsWord(actual, longWord2));
                }

                AND_THEN("The dictionary does not return the short word")
                {
                    REQUIRE(!TestHelpers::listContainsWord(actual, shortWord));
                }
            }
        }
    }

    SCENARIO("Find words that end in 'logy' that have a length of seven or less characters")
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

        GIVEN("A dictionary with words that end in 'logy' that have a length of seven or less characters")
        {
            auto builder = TestDictionaryBuilder(words);
            auto dictionary = builder.build();

            WHEN("The logy words are requested")
            {
                const auto actual = dictionary.getLogyWords();

                THEN("Only words that end in 'logy' and have a length of seven or less characters are returned")
                {
                    REQUIRE(TestHelpers::listContainsWord(actual, logy1));
                    REQUIRE(TestHelpers::listContainsWord(actual, logy2));
                    REQUIRE(TestHelpers::listContainsWord(actual, logy3));
                    REQUIRE(TestHelpers::listContainsWord(actual, logy4));
                }

                AND_THEN("Non logy words are not returned")
                {
                    REQUIRE(!TestHelpers::listContainsWord(actual, notLogy1));
                    REQUIRE(!TestHelpers::listContainsWord(actual, notLogy2));
                }
            }
        }
    }

    SCENARIO("Find words that rhyme")
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

        GIVEN("A dictionary with words")
        {
            auto builder = TestDictionaryBuilder(words);
            auto dictionary = builder.build();

            WHEN("A word that rhymes is searched")
            {
                const auto actual = dictionary.getRhymes(rhyme1);

                THEN("Words that rhyme are returned")
                {
                    REQUIRE(TestHelpers::listContainsWord(actual, rhyme1));
                    REQUIRE(TestHelpers::listContainsWord(actual, rhyme2));
                    REQUIRE(TestHelpers::listContainsWord(actual, rhyme2));
                }

                AND_THEN("Words that don't rhyme are not returned")
                {
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

        GIVEN("A dictionary with all word types")
        {
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

    SCENARIO("Find anagrams")
    {
        const string anagram1 = "tesla";
        const string anagram2 = "least";
        const string anagram3 = "slate";
        const string anagram4 = "steal";
        const string notAnagram1 = "abcde";
        const string notAnagram2 = "slat";

        const auto words = list<string>
        {
            anagram1,
            anagram2,
            anagram3,
            anagram4,
            notAnagram1,
            notAnagram2
        };

        GIVEN("A dictionary with words")
        {
            auto builder = TestDictionaryBuilder(words);
            auto dictionary = builder.build();

            WHEN("Anagrams of an existing word is requested")
            {
                const auto actual = dictionary.getWordAnagrams(anagram1);

                THEN("Anagrams of the word are returned")
                {
                    REQUIRE(TestHelpers::listContainsWord(actual, anagram1));
                    REQUIRE(TestHelpers::listContainsWord(actual, anagram2));
                    REQUIRE(TestHelpers::listContainsWord(actual, anagram3));
                    REQUIRE(TestHelpers::listContainsWord(actual, anagram4));
                }

                AND_THEN("Non anagrams are not returned")
                {
                    REQUIRE(!TestHelpers::listContainsWord(actual, notAnagram1));
                    REQUIRE(!TestHelpers::listContainsWord(actual, notAnagram2));
                }
            }

            AND_WHEN("Anagrams of a non existent word is requested")
            {
                const string target = "nope";
                const auto actual = dictionary.getWordAnagrams(target);

                THEN("No anagrams are returned")
                {
                    REQUIRE(actual.empty());
                }
            }

            AND_WHEN("Anagrams of a collection of letters is requested")
            {
                const string target = "alset";
                const auto actual = dictionary.getStringAnagrams(target);

                THEN("Anagrams of the word are returned")
                {
                    REQUIRE(TestHelpers::listContainsWord(actual, anagram1));
                    REQUIRE(TestHelpers::listContainsWord(actual, anagram2));
                    REQUIRE(TestHelpers::listContainsWord(actual, anagram3));
                    REQUIRE(TestHelpers::listContainsWord(actual, anagram4));
                }

                AND_THEN("Non anagrams are not returned")
                {
                    REQUIRE(!TestHelpers::listContainsWord(actual, notAnagram1));
                    REQUIRE(!TestHelpers::listContainsWord(actual, notAnagram2));
                }
            }

            AND_WHEN("Anagrams of a collection of letters that do not have any anagrams are requested")
            {
                const string target = "nope";
                const auto actual = dictionary.getStringAnagrams(target);

                THEN("No anagrams are returned")
                {
                    REQUIRE(actual.empty());
                }
            }
        }
    }
}
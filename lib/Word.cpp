﻿#include "stdafx.h"
#include "EmptyStringException.h"
#include "UnsupportedTypeException.h"
#include "Word.h"

using namespace std;
using namespace lib;

/**
* \brief Constructs a Word object with values extracted from a source dictionary.
* Resolves word type to an enum and calculates scrabble score on construction.
* \param word The word itself.
* \param type The type of word, ie. adj, n, etc. Must not include brackets "[]".
* \param definition The definition of the word.
* \param printer Inject implementation of IPrint so that Word is not coupled to implementation of printing.
*/
Word::Word(const string& word, const string& type, const string& definition, IPrint& printer) :
    _word(validate(word)),
    _type(resolveType(type)),
    _definition(validate(definition)),
    _scrabbleScore(calculateScrabbleScore()),
    _usage(0),
    _printer(printer)
{
}

string Word::getWord() const
{
    return _word;
}

Type Word::getType() const
{
    return _type;
}

string Word::getDefinition() const
{
    return _definition;
}

int Word::getScrabbleScore() const
{
    return _scrabbleScore;
}

string Word::printDefinition() const
{
    return _printer.print(*this);
}

/**
* \brief Returns true if word is not misc, proper noun or hyphenated.
* \return True if word type is not misc, proper noun or hyphenated.
*/
bool Word::isLegalScrabbleWord() const
{
    return !(_type == Misc || _type == ProperNoun || _word.find("-") != string::npos);
}

/**
* \brief Increment the usage count of the word.
*/
void Word::incrementUsage()
{
    _usage++;
}

/**
* \brief Returns true if usage == 1.
* \returns True if usage == 1.
*/
bool Word::isRareWord() const
{
    return _usage == 1;
}

/**
* \brief Implementation of operator ==, really useful for unit tests.
* \param that The other Word to compare to.
* \returns true if both Words contain the same values.
*/
bool Word::operator==(const Word& that) const
{
    return _word == that._word
        && _type == that._type
        && _definition == that._definition
        && _scrabbleScore == that._scrabbleScore;
}

/**
 * \brief Resolves a Word type from string to Type enum.
 * \param type The type as a string, extracted from the source dictionary.
 * \return The corresponding Type enum value.
 */
Type Word::resolveType(const string& type)
{
    const auto initialType = static_cast<Type>(-1);
    auto out = initialType;

    // would rather switch here but... https://stackoverflow.com/a/650218
    if (type == "v")
        out = Verb;
    if (type == "n")
        out = Noun;
    if (type == "adv")
        out = Adverb;
    if (type == "adj")
        out = Adjective;
    if (type == "prep")
        out = Preposition;
    if (type == "pn")
        out = ProperNoun;
    if (type == "n_and_v")
        out = NounAndVerb;
    if (type == "misc")
        out = Misc;

    // throw if we got some unexpected type
    if (out == initialType)
        throw UnsupportedTypeException(type);

    return out;
}

/**
* \brief Calculates the score for the word. Misc, proper noun or hyphenated words always return 0;
* \returns The score for the word if not misc, proper noun or hyphenated words, else returns 0.
*/
int Word::calculateScrabbleScore() const
{
    // cannot score with misc, proper noun and hyphenated words
    if (!isLegalScrabbleWord())
        return 0;

    // I already have a solution for this in github, so borrowing it:
    // https://github.com/martymcflywa/exercism/blob/master/java/scrabble-score/src/main/java/Scrabble.java

    const auto capitalA = 'A';
    const int letterScores[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

    // map each uppercase char to corresponding index on letterScores, 
    // by (uppercase letter ascii value minus 'A' ascii value) then reduce to sum
    // TODO: find out how to do this with map/reduce in cpp
    auto score = 0;
    for (auto letter : _word)
        score += letterScores[toupper(letter) - capitalA];

    return score;
}

/**
 * \brief Ensure we don't receive any empty strings. Throw if we do.
 * \param input The extracted value from the source dictionary.
 * \return The value if it passes validation, else throw.
 */
string Word::validate(const string& input)
{
    if (input.empty())
        throw EmptyStringException();

    return input;
}
#include "stdafx.h"
#include "Word.h"

/**
 * \brief Constructs a Word object with values extracted from a source dictionary.
 * \param word The word itself.
 * \param type The type of word, ie. adj, n, etc. Must not include brackets "[]". Will be resolved to an enum during construction.
 * \param definition The definition of the word.
 * \param printer Inject implementation of IPrinter to decouple Word from implementation of printing.
 * This means we could easily implement a Json (or whatever) printer, and inject it here if requirements change down the track.
 */
Word::Word(const string& word, const string& type, const string& definition, IPrinter& printer) :
    _word(validate(word)),
    _type(resolveType(type)),
    _definition(validate(definition)),
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

void Word::printDefinition()
{
    _printer.print(*this);
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
        && _definition == that._definition;
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

    // would rather switch case it up here but... https://stackoverflow.com/a/650218
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
        throw invalid_argument("Type " + type + " not supported");

    return out;
}

/**
 * \brief Ensure we don't receive any empty strings. Throw if we do.
 * \param input The extracted value from the source dictionary.
 * \return The value if it passes validation, else throw.
 */
string Word::validate(const string& input)
{
    if (input.empty())
        throw invalid_argument("Received an empty string");

    return input;
}
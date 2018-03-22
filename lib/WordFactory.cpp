#include "stdafx.h"
#include "EmptyStringException.h"
#include "WordFactory.h"
#include "UnsupportedTypeException.h"

using namespace std;
using namespace lib;

Word WordFactory::build(const string& word, const string& type, const string& definition, IPrint& printer)
{
    if (word.empty())
        throw EmptyStringException("Word");
    if (type.empty())
        throw EmptyStringException("Type");
    if (definition.empty())
        throw EmptyStringException("Definition");

    return { word, resolveType(type), definition, printer };
}

/**
* \brief Resolves a Word type from string to Type enum.
* \param type The type as a string, extracted from the source dictionary.
* \return The corresponding Type enum value.
*/
Type WordFactory::resolveType(const std::string& type)
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

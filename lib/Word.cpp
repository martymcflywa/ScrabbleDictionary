#include "stdafx.h"
#include "Word.h"

lib::Type lib::Word::resolveType(const string& type)
{
	auto initialType = -1;
    auto out = static_cast<Type>(initialType);

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

	if (out == initialType)
		throw invalid_argument("Type " + type + " not supported");

    return out;
}

string lib::Word::validate(const string& input)
{
	if (input.empty())
		throw invalid_argument("Attempting to use an empty string");

	return input;
}

lib::Word::Word(const string& word, const string& type, const string& definition, IPrinter& printer):
    _word(validate(word)),
	_type(resolveType(type)),
    _definition(validate(definition)),
    _printer(printer)
{
}

string lib::Word::getWord() const
{
    return _word;
}

lib::Type lib::Word::getType() const
{
    return _type;
}

string lib::Word::getDefinition() const
{
    return _definition;
}

void lib::Word::printDefinition()
{
    _printer.print(*this);
}

// useful for unit tests
bool lib::Word::operator==(const Word& that) const
{
	return _word == that._word
		&& _type == that._type
		&& _definition == that._definition;
}

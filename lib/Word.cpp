#include "stdafx.h"
#include "Word.h"

lib::Type lib::Word::resolveType(const string type)
{
    auto outputType = static_cast<Type>(-1);

    if (type == "[v]")
        outputType = Verb;
    if (type == "[n]")
        outputType = Noun;
    if (type == "[adv]")
        outputType = Adverb;
    if (type == "[adj]")
        outputType = Adjective;
    if (type == "[prep]")
        outputType = Preposition;
    if (type == "[pn]")
        outputType = ProperNoun;
    if (type == "[n_and_v]")
        outputType = NounAndVerb;
    if (type == "[misc]")
        outputType = Misc;

    return outputType;
}

lib::Word::Word(const string word, const string type, const string definition, IPrinter& printer):
    _word(word),
    _definition(definition),
    _printer(printer)
{
    _type = resolveType(type);
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

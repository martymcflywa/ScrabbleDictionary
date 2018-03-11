#include "stdafx.h"
#include "WordFactory.h"
#include "EmptyStringException.h"

Word WordFactory::build(string& word, string& type, string& definition, IPrint& printer)
{
    if (word.empty())
        throw EmptyStringException("Word");
    if (type.empty())
        throw EmptyStringException("Type");
    if (definition.empty())
        throw EmptyStringException("Definition");

    return { word, type, definition, printer };
}

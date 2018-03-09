#include "stdafx.h"
#include "WordFactory.h"

Word WordFactory::build(string& word, string& type, string& definition, IPrint& printer)
{
    if (word.empty())
        throw invalid_argument("Word is empty");
    if (type.empty())
        throw invalid_argument("Type is empty");
    if (definition.empty())
        throw invalid_argument("Definition is empty");

    return { word, type, definition, printer };
}

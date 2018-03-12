#include "stdafx.h"
#include "DefinitionFormatter.h"
#include "Word.h"
#include "WordType.h"

/**
* \brief Formats the definition when printing to console.
*/
string DefinitionFormatter::format(const Word& word)
{
    return WordType::getName(word.getType()) + ":\n" +
        word.getDefinition();
}

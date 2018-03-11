#include "stdafx.h"
#include "DefinitionFormatter.h"
#include "WordType.h"
#include "Word.h"

/**
* \brief Formats the definition when printing to console.
*/
string DefinitionFormatter::format(Word& word)
{
    return WordType::getName(word.getType()) + ":\n" +
        word.getDefinition();
}

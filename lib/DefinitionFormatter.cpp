#include "stdafx.h"
#include "DefinitionFormatter.h"
#include "WordType.h"
#include "Word.h"

string DefinitionFormatter::format(Word& word)
{
    return WordType::getName(word.getType()) + ":\n" +
        word.getDefinition();
}

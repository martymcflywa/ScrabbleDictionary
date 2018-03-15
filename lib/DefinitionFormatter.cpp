#include "stdafx.h"
#include "DefinitionFormatter.h"
#include "Word.h"
#include "WordType.h"

using namespace std;
using namespace lib;

/**
* \brief Formats the definition when printing to console.
*/
string DefinitionFormatter::format(const Word& word)
{
    return WordType::getName(word.getType()) + " " + word.getDefinition();
}

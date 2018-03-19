#include "stdafx.h"
#include "GlossaryFormatter.h"
#include "Word.h"
#include "WordType.h"

using namespace std;
using namespace lib;

string GlossaryFormatter::format(const Word& word)
{
    return 
        "[WORD] " + word.getWord() + "\n" +
        "[TYPE] " + WordType::getName(word.getType()) + "\n"
        "[DEFINITION] " + word.getDefinition() + "\n\n";
}

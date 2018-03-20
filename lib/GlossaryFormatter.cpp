#include "stdafx.h"
#include "GlossaryFormatter.h"
#include "Word.h"
#include "WordType.h"

using namespace std;
using namespace lib;

string GlossaryFormatter::format(const Word& word)
{
    return word.getWord() + ":\n" + WordType::getName(word.getType()) + " " + word.getDefinition();
}

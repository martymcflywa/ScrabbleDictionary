#include "stdafx.h"
#include "DefinitionPrinter.h"
#include "../cli/Logger.h"

using namespace std;
using namespace cli;
using namespace lib;

DefinitionPrinter::DefinitionPrinter(IFormat& formatter) : _formatter(formatter)
{
}

string DefinitionPrinter::print(const Word& word)
{
    return _formatter.format(word);
}

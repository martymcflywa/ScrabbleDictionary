#include "stdafx.h"
#include "DefinitionPrinter.h"
#include "../cli/Logger.h"

using namespace cli;

lib::DefinitionPrinter::DefinitionPrinter(IFormat& formatter) : _formatter(formatter)
{
}

void lib::DefinitionPrinter::print(const Word& word)
{
    auto output = _formatter.format(word);
    Logger::log(Output, output);
}

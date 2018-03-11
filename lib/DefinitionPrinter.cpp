﻿#include "stdafx.h"
#include "DefinitionPrinter.h"
#include "../cli/Printer.h"

using namespace cli;

lib::DefinitionPrinter::DefinitionPrinter(IFormat& formatter) : _formatter(formatter)
{
}

void lib::DefinitionPrinter::print(Word& word)
{
    auto output = _formatter.format(word);
    Printer::print(Output, output);
}

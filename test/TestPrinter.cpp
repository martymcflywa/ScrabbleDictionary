#include "stdafx.h"
#include "TestPrinter.h"
#include "../lib/Word.h"

TestPrinter::TestPrinter(IFormat& formatter) : _formatter(formatter)
{
}

string TestPrinter::print(const Word& word)
{
    _output = _formatter.format(word);
    return _output;
}

string TestPrinter::getOutput() const
{
    return _output;
}

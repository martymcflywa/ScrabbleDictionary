#include "stdafx.h"
#include "TestPrinter.h"
#include "../lib/Word.h"

TestPrinter::TestPrinter(IFormat& formatter) : _formatter(formatter)
{
}

void TestPrinter::print(Word& word)
{
    _output = _formatter.format(word);
}

string TestPrinter::getOutput() const
{
    return _output;
}

#include "stdafx.h"
#include "TestPrinter.h"
#include "../lib/Word.h"

string TestPrinter::format(Word& word)
{
    return WordType::getName(word.getType()) + ":\n" +
        word.getDefinition();
}

void TestPrinter::print(Word& word)
{
    _output = format(word);
}

string TestPrinter::getOutput() const
{
    return _output;
}

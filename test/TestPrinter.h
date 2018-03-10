#pragma once
#include <string>
#include "../lib/IPrint.h"
#include "../lib/IFormat.h"

using namespace std;
using namespace lib;

class TestPrinter : public IPrint
{
    IFormat& _formatter;
    string _output;

public:
    TestPrinter(IFormat& formatter);
    void print(Word& word) override;
    string getOutput() const;
};

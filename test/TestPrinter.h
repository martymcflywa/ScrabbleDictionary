#pragma once
#include <string>
#include "../lib/IPrinter.h"

using namespace std;
using namespace lib;

class TestPrinter : public IPrinter
{
    string _output;
    string format(Word& word) override;

public:
    void print(Word& word) override;
    string getOutput() const;
};

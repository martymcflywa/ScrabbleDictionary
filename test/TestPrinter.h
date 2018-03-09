#pragma once
#include <string>
#include "../lib/IPrint.h"

using namespace std;
using namespace lib;

class TestPrinter : public IPrint
{
    string _output;
    string format(Word& word) override;

public:
    void print(Word& word) override;
    string getOutput() const;
};

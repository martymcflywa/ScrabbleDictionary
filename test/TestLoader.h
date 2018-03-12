#pragma once
#include <string>
#include <sstream>
#include "../lib/ILoad.h"

using namespace std;
using namespace lib;

class TestLoader : public ILoad
{
    istringstream _testDictionary;

public:
    TestLoader() = default;
    void setTestFile(string& testFile);
    istream& load() override;
    void dispose() override;
};

#pragma once
#include <string>
#include <sstream>
#include "../lib/ILoader.h"

using namespace std;
using namespace lib;

class TestLoader : public ILoader
{
    istringstream _testDictionary;

public:
    void setTestFile(string testFile);
    istream& load(string filepath) override;
};

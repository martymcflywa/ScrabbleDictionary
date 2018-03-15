#pragma once
#include <string>
#include <sstream>
#include "../lib/ILoad.h"

class TestLoader : public lib::ILoad
{
    std::istringstream _testDictionary;

public:
    TestLoader() = default;
    void setTestFile(const std::string& testFile);
    std::istream& load() override;
    void dispose() override;
};

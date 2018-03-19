#pragma once
#include <sstream>
#include <string>
#include "../lib/IRead.h"

class TestReader : public lib::IRead
{
    std::istringstream _testDictionary;

public:
    TestReader() = default;
    void setTestFile(const std::string& testFile);
    std::istream& read() override;
    void dispose() override;
};

#pragma once
#include <string>
#include "../lib/IWrite.h"

class TestWriter : public lib::IWrite<const std::string&>
{
    std::string _content;
public:
    void write(const std::string& content) override;
    std::string getFilepath() override;
    std::string& getContent();
};

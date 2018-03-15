#pragma once
#include <string>

class TestFileFactory
{
    const std::string& _filepath;
    const std::string& _content;

public:
    TestFileFactory(const std::string& filepath, const std::string& content);
    void write() const;
    void cleanup() const;
};

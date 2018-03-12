#pragma once
#include <string>

using namespace std;

class TestFileFactory
{
    const string& _filepath;
    const string& _content;

public:
    TestFileFactory(const string& filepath, const string& content);
    void write() const;
    void cleanup() const;
};

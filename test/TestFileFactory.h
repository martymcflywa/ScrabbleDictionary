#pragma once
#include <string>

using namespace std;

class TestFileFactory
{
    string& _filepath;
    string& _content;

public:
    TestFileFactory(string& filepath, string& content);
    void write() const;
    void cleanup() const;
};

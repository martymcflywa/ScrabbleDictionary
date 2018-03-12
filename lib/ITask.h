#pragma once
#include <list>
#include <string>

using namespace std;

class ITask
{
public:
    virtual ~ITask() = default;
    virtual void setLongestWord(const string& word) = 0;
    virtual void setLogyWords(const string& word) = 0;
    virtual string getLongestWord() = 0;
    virtual list<string> getLogyWords() = 0;
};

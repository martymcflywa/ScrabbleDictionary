#pragma once
#include <list>
#include <string>

using namespace std;

class ITask
{
public:
    virtual ~ITask() = default;
    virtual void setLongestWords(const string& word) = 0;
    virtual void setLogyWords(const string& word) = 0;
    virtual list<string> getLongestWords() = 0;
    virtual list<string> getLogyWords() = 0;
};

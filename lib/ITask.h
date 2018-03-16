#pragma once
#include <list>
#include <string>
#include <memory>
#include "Word.h"

class ITask
{
public:
    virtual ~ITask() = default;
    virtual void setLongestWords(const std::string& word) = 0;
    virtual void setLogyWords(const std::string& word) = 0;
    virtual void setRhymes(const std::string& word) = 0;
    virtual void setAnagrams(std::shared_ptr<lib::Word> word) = 0;
    virtual std::list<std::string> getLongestWords() = 0;
    virtual std::list<std::string> getLogyWords() = 0;
    virtual std::list<std::string> getRhymes(const std::string& word) = 0;
    virtual std::list<std::shared_ptr<lib::Word>> getAnagrams(const std::string& word) = 0;
};

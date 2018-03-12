#pragma once
#include "ITask.h"

class DictionaryTask : public ITask
{
    string _longestWord;
    list<string> _logyWords{};

public:
    DictionaryTask();
    void setLongestWord(const string& word) override;
    void setLogyWords(const string& word) override;
    string getLongestWord() override;
    list<string> getLogyWords() override;
private:
    bool endsWith(const string& word, const string& ending) const;
};

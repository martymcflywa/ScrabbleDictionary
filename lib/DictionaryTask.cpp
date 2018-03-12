#include "stdafx.h"
#include "DictionaryTask.h"

DictionaryTask::DictionaryTask()
= default;

void DictionaryTask::setLongestWord(const string& word)
{
    if (word.length() > _longestWord.length())
        _longestWord = word;
}

void DictionaryTask::setLogyWords(const string& word)
{
    const string ending = "logy";

    if (word.length() >= ending.length() && word.length() < 8 && endsWith(word, ending))
        _logyWords.insert(_logyWords.end(), word);
}

string DictionaryTask::getLongestWord()
{
    return _longestWord;
}

list<string> DictionaryTask::getLogyWords()
{
    return _logyWords;
}

bool DictionaryTask::endsWith(const string& word, const string& ending) const
{
    return equal(ending.rbegin(), ending.rend(), word.rbegin());
}

#include "stdafx.h"
#include "DictionaryTask.h"

/**
* \brief Sets a collection of longest words. It compares the current word length with the longest length seen so far.
* If the lengths are equal, it adds the word to the collection. If the length is greater than max, it clears the list,
* adds the current word to the fresh list and sets a new max threshold.
* \param word The current word during extraction.
*/
void DictionaryTask::setLongestWords(const string& word)
{
    // if current word length is equal to max, add it to the list
    if (word.length() == _maxWordLength)
        _longestWords.insert(_longestWords.end(), word);

    // if current word length is greater than max, clear the list, add current word to fresh list, set new max threshold
    if (word.length() > _maxWordLength)
    {
        _longestWords.clear();
        _longestWords.insert(_longestWords.end(), word);
        _maxWordLength = word.length();
    }
}

/**
* \brief Checks if current word's length is equal to or greater than 'logy' length, and less than 8 char long,
* and ends with 'logy'. If true, word is added to collection.
* \param word The current word during extraction.
*/
void DictionaryTask::setLogyWords(const string& word)
{
    const string ending = "logy";

    if (word.length() >= ending.length() && word.length() < 8 && endsWith(word, ending))
        _logyWords.insert(_logyWords.end(), word);
}

/**
* \brief Returns the collection of longest words found in dictionary.
* \returns The collection of longest words found in dictionary.
*/
list<string> DictionaryTask::getLongestWords()
{
    return _longestWords;
}

/**
* \brief Returns the collection of words ending in 'logy' with length of seven or less.
* \returns The collection of words ending in 'logy' with length of seven or less.
*/
list<string> DictionaryTask::getLogyWords()
{
    return _logyWords;
}

/**
* \brief Returns true if the word ends with ending.
* \param word The word to inspect.
* \param ending The ending of the word we'd like to find.
* \return True if the word ends with ending.
*/
bool DictionaryTask::endsWith(const string& word, const string& ending) const
{
    return equal(ending.rbegin(), ending.rend(), word.rbegin());
}

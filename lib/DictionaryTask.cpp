#include "stdafx.h"
#include <algorithm>
#include "DictionaryTask.h"

using namespace std;
using namespace lib;

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

    if (word.length() >= LOGY_ENDING.length()
            && word.length() <= MAX_LOGY_LENGTH
            && endsWith(word, LOGY_ENDING))
    {
        _logyWords.insert(_logyWords.end(), word);
    }
}

/**
* \brief Get the rhyme part of the word, used as key for rhyme map.
* If true, checks if rhyme key exists in rhyme map. If true, add to list of values,
* else create a new map entry, with last three letters as key, and word as list entry.
* \param word The current word during extraction.
*/
void DictionaryTask::setRhymes(const std::string& word)
{
    // get the rhyme part
    const auto key = getRhymeKey(word);
    // don't add entries with empty keys
    if (key.empty())
        return;

    // try to find rhyme in map
    const auto it = _rhymes.find(key);

    // if not found, add a new k/v pair
    if (it == _rhymes.end())
    {
        auto value = list<string>{ word };
        _rhymes.insert(pair<string, list<string>>(key, value));
        return;
    }

    // if found, add word to the list
    it->second.push_back(word);
}

/**
* \brief Strip word of any '-', then sort letters alphabetically. Result is key to anagram map.
* If key exists, add to value (list of shared_ptr<Word>). If it doesn't exist,
* add new k/v pair of alphabetically sorted letters as key, and a new list of shared_ptr<Word>,
* inserting current shared_ptr<Word> into it.
* \param word The current word during extraction.
*/
void DictionaryTask::setAnagrams(const shared_ptr<Word> word)
{
    // convert word into key (no '-', alphabetically sorted)
    const auto key = getAnagramKey(word->getWord());
    // try to find key in anagram map
    const auto it = _anagrams.find(key);

    // if not found, add a new k/v pair
    if (it == _anagrams.end())
    {
        auto value = list<shared_ptr<Word>>{ word };
        _anagrams.insert(pair<string, list<shared_ptr<Word>>>(key, value));
        return;
    }

    // else we found an anagram, add it to the list
    it->second.push_back(word);
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
* \brief Returns word/s that rhyme with the parameter word, if any exist.
* \param word The word to search for rhymes.
* \returns Word/s that rhyme with parameter word.
*/
list<string> DictionaryTask::getRhymes(const string& word)
{
    const auto key = getRhymeKey(word);
    const auto it = _rhymes.find(key);

    // if not found, return an empty list
    if (it == _rhymes.end())
        return list<string>();

    return it->second;
}

/**
* \brief Convert word to key for anagram map. If key exists in map,
* return list value for that key, else return an empty list.
* \param word The word to search for anagrams.
* \returns Anagram/s of the word, if they exist, else returns an empty list.
*/
list<shared_ptr<Word>> DictionaryTask::getAnagrams(const string& word)
{
    const auto key = getAnagramKey(word);
    const auto it = _anagrams.find(key);

    // if not found, return an empty list
    if (it == _anagrams.end())
        return list<shared_ptr<Word>>();

    return it->second;
}

/**
* \brief Returns the rhyming part of the word if >= 3 letters,
* else returns an empty string.
* \param word The current word being extracted.
* \returns The rhyming part of the word if >= 3 letters,
* else returns an empty string.
*/
string DictionaryTask::getRhymeKey(const string& word)
{
    if (word.length() < RHYME_LENGTH)
        return "";

    return word.substr(word.length() - RHYME_LENGTH);
}

/**
* \brief If word length == 1, return word. Else remove all '-' from string.
* Then sort alphabetically and return it.
* \param word The word to generate an anagram key with.
* \returns The word's letters sorted alphabetically and without '-'.
*/
string DictionaryTask::getAnagramKey(const string& word)
{
    // if single letter, nothing else to do
    if (word.length() == 1)
        return word;

    // make a copy
    auto key = word;
    // strip hyphens '-'
    key.erase(remove(key.begin(), key.end(), '-'), key.end());
    // sort alphabetically
    sort(key.begin(), key.end());

    return key;
}

/**
* \brief Returns true if the word ends with ending.
* \param word The word to inspect.
* \param ending The ending of the word we'd like to find.
* \return True if the word ends with ending.
*/
bool DictionaryTask::endsWith(const string& word, const string& ending)
{
    const auto endIndex = word.length() - ending.length();
    return word.find(ending, endIndex) != string::npos;
}

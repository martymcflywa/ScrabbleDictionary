#include "stdafx.h"
#include <algorithm>
#include "DictionaryTask.h"
#include "UnsupportedTaskException.h"

using namespace std;
using namespace lib;

void DictionaryTask::handleTasks(const std::shared_ptr<Word> wordObj)
{
    setLongestWords(wordObj);
    setLogyWords(wordObj);
    setRhymes(wordObj);
    setAnagrams(wordObj);
}

std::list<std::shared_ptr<Word>> DictionaryTask::getTaskResult(const TaskType taskType)
{
    switch (taskType)
    {
    case LongestWords:
        return getLongestWords();
    case LogyWords:
        return getLogyWords();
    default:
        throw UnsupportedTaskException(to_string(taskType));
    }
}

std::list<std::shared_ptr<Word>> DictionaryTask::getTaskResult(const TaskType taskType, const std::string& word)
{
    switch (taskType)
    {
    case Rhymes:
        return getRhymes(word);
    case WordAnagrams:
    case StringAnagrams:
        return getAnagrams(taskType, word);
    default:
        throw UnsupportedTaskException(to_string(taskType));
    }
}

/**
* \brief Sets a collection of longest words. It compares the current word length with the longest length seen so far.
* If the lengths are equal, it adds the word to the collection. If the length is greater than max, it clears the list,
* adds the current word to the fresh list and sets a new max threshold.
* \param wordObj The current Word during extraction.
*/
void DictionaryTask::setLongestWords(const shared_ptr<Word> wordObj)
{
    const auto word = wordObj->getWord();

    // if current word length is equal to max, add it to the list
    if (word.length() == _maxWordLength)
        _longestWords.insert(_longestWords.end(), wordObj);

    // if current word length is greater than max, clear the list, add current word to fresh list, set new max threshold
    if (word.length() > _maxWordLength)
    {
        _longestWords.clear();
        _longestWords.insert(_longestWords.end(), wordObj);
        _maxWordLength = word.length();
    }
}

/**
* \brief Checks if current word's length is equal to or greater than 'logy' length, and less than 8 char long,
* and ends with 'logy'. If true, word is added to collection.
* \param wordObj The current word during extraction.
*/
void DictionaryTask::setLogyWords(const shared_ptr<Word> wordObj)
{
    const auto word = wordObj->getWord();

    if (word.length() >= LOGY_ENDING.length()
            && word.length() <= MAX_LOGY_LENGTH
            && endsWith(word, LOGY_ENDING))
    {
        _logyWords.insert(_logyWords.end(), wordObj);
    }
}

/**
* \brief Get the rhyme part of the word, used as key for rhyme map.
* If true, checks if rhyme key exists in rhyme map. If true, add to list of values,
* else create a new map entry, with last three letters as key, and word as list entry.
* \param wordObj The current word during extraction.
*/
void DictionaryTask::setRhymes(const shared_ptr<Word> wordObj)
{
    const auto word = wordObj->getWord();

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
        auto value = list<shared_ptr<Word>>{ wordObj };
        _rhymes.insert(pair<string, list<shared_ptr<Word>>>(key, value));
        return;
    }

    // if found, add word to the list
    it->second.push_back(wordObj);
}

/**
* \brief Strip word of any '-', then sort letters alphabetically. Result is key to anagram map.
* If key exists, add to value (list of shared_ptr<Word>). If it doesn't exist,
* add new k/v pair of alphabetically sorted letters as key, and a new list of shared_ptr<Word>,
* inserting current shared_ptr<Word> into it.
* \param wordObj The current word during extraction.
*/
void DictionaryTask::setAnagrams(const shared_ptr<Word> wordObj)
{
    // convert word into key (no '-', alphabetically sorted)
    const auto key = getAnagramKey(wordObj->getWord());
    // try to find key in anagram map
    const auto it = _anagrams.find(key);

    // if not found, add a new k/v pair
    if (it == _anagrams.end())
    {
        auto value = list<shared_ptr<Word>>{ wordObj };
        _anagrams.insert(pair<string, list<shared_ptr<Word>>>(key, value));
        return;
    }

    // else we found an anagram, add it to the list
    it->second.push_back(wordObj);
}

/**
* \brief Returns the collection of longest words found in dictionary.
* \returns The collection of longest words found in dictionary.
*/
list<shared_ptr<Word>> DictionaryTask::getLongestWords() const
{
    return _longestWords;
}

/**
* \brief Returns the collection of words ending in 'logy' with length of seven or less.
* \returns The collection of words ending in 'logy' with length of seven or less.
*/
list<shared_ptr<Word>> DictionaryTask::getLogyWords() const
{
    return _logyWords;
}

/**
* \brief Returns word/s that rhyme with the parameter word, if any exist.
* \param word The word to search for rhymes.
* \returns Word/s that rhyme with parameter word.
*/
list<shared_ptr<Word>> DictionaryTask::getRhymes(const string& word)
{
    const auto key = getRhymeKey(word);
    const auto it = _rhymes.find(key);

    // if not found, return an empty list
    if (it == _rhymes.end())
        return list<shared_ptr<Word>>();

    return filterResult(
        it->second,
        [word](shared_ptr<Word> const& wordObj)
        {
            return wordObj->getWord() == word;
        });
}

/**
* \brief Sort word's letters alphabetically, as key to anagram map.
* If key exists in anagram map, return list value for that key, else return an empty list.
* \param taskType Only WordAnagrams or StringAnagrams supported.
* \param word The word to search for anagrams.
* \returns Anagram/s of the word, if they exist, else returns an empty list.
*/
list<shared_ptr<Word>> DictionaryTask::getAnagrams(TaskType taskType, const string& word)
{
    const auto key = getAnagramKey(word);
    const auto it = _anagrams.find(key);

    // if not found, return an empty list
    if (it == _anagrams.end())
        return list<shared_ptr<Word>>();

    // TODO: would rather init a function<bool()> variable up here to avoid repeated code...
    // switch determines which predicate to store in the variable...
    // then call return filterResult() once after the switch case...
    // but had problems assigning the predicate to the variable... investigate further
    switch (taskType)
    {
    case WordAnagrams: // remove words that match the search pattern
        return filterResult(
            it->second,
            [word](shared_ptr<Word> const& wordObj)
            {
                return wordObj->getWord() == word;
            });
    case StringAnagrams: // remove words that match the search pattern or are not legal
        return filterResult(
            it->second,
            [word](shared_ptr<Word> const& wordObj)
            {
                return wordObj->getWord() == word
                    || !wordObj->isLegalScrabbleWord();
            });
    default:
        throw UnsupportedTaskException(to_string(taskType));
    }
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
* \brief Filter the results based on a predicate lambda expression.
* \param result The collection of results from the task.
* \param predicate The predicate lambda expression, where if true, will exclude the result from the collection.
* \return A new result after filter is applied.
*/
template<typename Predicate>
list<shared_ptr<Word>> DictionaryTask::filterResult(list<shared_ptr<Word>> result, Predicate predicate)
{
    // cool solution from https://stackoverflow.com/a/42723273
    // adapted to accept a predicate lambda exp for custom filtering
    result.erase(
        remove_if(result.begin(), result.end(), predicate),
        result.end());

    return result;
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

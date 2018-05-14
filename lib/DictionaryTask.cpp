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

std::vector<std::shared_ptr<Word>> DictionaryTask::getTaskResult(const TaskType taskType)
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

std::vector<std::shared_ptr<Word>> DictionaryTask::getTaskResult(const TaskType taskType, const std::string& word)
{
    switch (taskType)
    {
    case Rhymes:
        return getRhymes(word);
    case WordAnagrams:
        return getWordAnagrams(word);
    case StringAnagrams:
        return getStringAnagrams(word);
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

    // ignore if less than max
    if (word.length() < _maxWordLength)
        return;

    // clear collection if greater than max
    if (word.length() > _maxWordLength)
        _longestWords.clear();

    _longestWords.push_back(wordObj);
    _maxWordLength = word.length();
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
        _logyWords.push_back(wordObj);
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
        auto value = vector<shared_ptr<Word>>{ wordObj };
        _rhymes.insert(pair<string, vector<shared_ptr<Word>>>(key, value));
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
        auto value = vector<shared_ptr<Word>>{ wordObj };
        _anagrams.insert(pair<string, vector<shared_ptr<Word>>>(key, value));
        return;
    }

    // else we found an anagram, add it to the list
    it->second.push_back(wordObj);
}

/**
* \brief Returns the collection of longest words found in dictionary.
* \returns The collection of longest words found in dictionary.
*/
vector<shared_ptr<Word>> DictionaryTask::getLongestWords() const
{
    return _longestWords;
}

/**
* \brief Returns the collection of words ending in 'logy' with length of seven or less.
* \returns The collection of words ending in 'logy' with length of seven or less.
*/
vector<shared_ptr<Word>> DictionaryTask::getLogyWords() const
{
    return _logyWords;
}

/**
* \brief Returns word/s that rhyme with the parameter word, if any exist.
* \param word The word to search for rhymes.
* \returns Word/s that rhyme with parameter word.
*/
vector<shared_ptr<Word>> DictionaryTask::getRhymes(const string& word)
{
    const auto key = getRhymeKey(word);
    const auto it = _rhymes.find(key);

    // if not found, return an empty list
    if (it == _rhymes.end())
        return vector<shared_ptr<Word>>();

    return filter(
        it->second,
        [&word](const shared_ptr<Word>& wordObj)
        {
            return wordObj->getWord() == word;
        });
}

/**
* \brief Returns all anagrams, including illegal scrabble words for a search pattern.
* Search pattern does not have to be an existing word in the dictionary. If the search
* pattern exists in the result, it will be filtered out.
* \param word The word to search for anagrams.
* \returns Any anagram/s of the word, if they exist, else returns an empty list.
*/
std::vector<std::shared_ptr<Word>> DictionaryTask::getWordAnagrams(const std::string& word)
{
    const auto key = getAnagramKey(word);
    const auto it = _anagrams.find(key);

    // if not found, return an empty list
    if (it == _anagrams.end())
        return vector<shared_ptr<Word>>();

    // remove search pattern from result
    return filter(
        it->second,
        [&word](const shared_ptr<Word>& wordObj)
        {
            return word == wordObj->getWord();
        });
}

/**
* \brief Returns the highest scrabble scoring anagrams from a collection of letters.
* Not all letters have to be used in anagrams. If the letters form a word in the result,
* it will be filtered out.
* \param letters The collection of letters to search anagrams of.
* \return The highest scrabble scoring anagrams, if any exist, else returns an empty list.
*/
std::vector<std::shared_ptr<Word>> DictionaryTask::getStringAnagrams(const std::string& letters)
{
    auto result = vector<shared_ptr<Word>>{};
    auto maxScore = 0;

    // TODO: needs optimizing, iterating over every anagram key is not ideal! This is worst case O(n^2)
    // IDEA: Binary search on first letter of key since std::map is sorted, see map::lower_bound
    for (const auto& pair : _anagrams)
    {
        auto legalWords = filter(
            pair.second,
            [](const shared_ptr<Word>& wordObj)
            {
                return !wordObj->isLegalScrabbleWord();
            });

        if (legalWords.empty())
            continue;

        // Safe to assume at this point, all words in legalWords have the same scrabble score,
        // since they all contain the exact same letters.

        const auto currentMaxScore = legalWords.front()->getScrabbleScore();

        // Only interested in this collection of anagrams if it has a 
        // current max score greater than or equal to max score
        if (currentMaxScore < maxScore)
            continue;

        const auto key = pair.first;

        if (letters.length() < key.length())
            continue;

        if (!hasAllLetters(letters, key))
            continue;

        // If we find a higher scoring collection of anagrams,
        // reset the result cache and set a new max score
        if (currentMaxScore > maxScore)
        {
            maxScore = currentMaxScore;
            result.clear();
        }

        for (auto& it : legalWords)
            result.push_back(it);
    }

    return filter(
        result,
        [&letters](const shared_ptr<Word>& wordObj)
        {
            return letters == wordObj->getWord();
        });
}

/**
* \brief Returns true if all the characters in the key exist in the collection of letters.
* \param letters The collection of letters being checked.
* \param key Each letter in the key will be checked against collection of letters.
* \return True if all characters in the key exist in the collection of letters.
*/
bool DictionaryTask::hasAllLetters(string letters, const string& key)
{
    // TODO: Naive solution here, adds even more complexity to getStringAnagrams loop
    // IDEA: Trie or radix tree, see https://stackoverflow.com/q/2835910
    for (auto c : key)
    {
        const auto foundChar = letters.find(c);

        if (foundChar == string::npos)
            return false;
        
        letters.erase(foundChar, 1);
    }
    return true;
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

    // make lowercase
    auto key = word;
    transform(word.begin(), word.end(), key.begin(), tolower);

    // strip hyphens '-'
    key.erase(remove(key.begin(), key.end(), '-'), key.end());
    // sort alphabetically
    sort(key.begin(), key.end());

    return key;
}

/**
* \brief Filter the results based on a unary predicate lambda expression.
* \param result The collection of results from the task.
* \param predicate The unary predicate lambda expression, where if true, 
* will exclude the result from the collection.
* \return A new result after filter is applied.
*/
template<typename Predicate>
vector<shared_ptr<Word>> DictionaryTask::filter(vector<shared_ptr<Word>> result, const Predicate& predicate)
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

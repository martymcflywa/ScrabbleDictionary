#pragma once
#include "ITask.h"

class DictionaryTask : public ITask
{
    unsigned int _maxWordLength = 0;
    list<string> _longestWords {};
    list<string> _logyWords {};

public:
    DictionaryTask() = default;
    /**
     * \brief Sets a collection of longest words. It compares the current word length with the longest length seen so far.
     * If the lengths are equal, it adds the word to the collection. If the length is greater than max, it clears the list,
     * adds the current word to the fresh list and sets a new max threshold.
     * \param word The current word during extraction.
     */
    void setLongestWords(const string& word) override;
    /**
     * \brief Checks if current word's length is equal to or greater than 'logy' length, and less than 8 char long,
     * and ends with 'logy'. If true, word is added to collection.
     * \param word The current word during extraction.
     */
    void setLogyWords(const string& word) override;
    /**
     * \brief Returns the collection of longest words found in dictionary.
     * \returns The collection of longest words found in dictionary.
     */
    list<string> getLongestWords() override;
    /**
     * \brief Returns the collection of words ending in 'logy' with length of seven or less.
     * \returns The collection of words ending in 'logy' with length of seven or less. 
     */
    list<string> getLogyWords() override;
private:
    /**
     * \brief Returns true if the word ends with ending.
     * \param word The word to inspect.
     * \param ending The ending of the word we'd like to find.
     * \return True if the word ends with ending.
     */
    bool endsWith(const string& word, const string& ending) const;
};

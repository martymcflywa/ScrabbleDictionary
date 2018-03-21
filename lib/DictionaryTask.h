#pragma once
#include "ITask.h"
#include "Word.h"
#include <unordered_map>

namespace lib
{
    class DictionaryTask : public ITask
    {
        unsigned int _maxWordLength = 0;
        const std::string LOGY_ENDING = "logy";
        const unsigned int MAX_LOGY_LENGTH = 7;
        static const unsigned int RHYME_LENGTH = 3;

        std::vector<std::shared_ptr<Word>> _longestWords{};
        std::vector<std::shared_ptr<Word>> _logyWords{};
        std::unordered_map<std::string, std::vector<std::shared_ptr<Word>>> _rhymes{};
        std::unordered_map<std::string, std::vector<std::shared_ptr<Word>>> _anagrams{};

    public:
        DictionaryTask() = default;
        void handleTasks(std::shared_ptr<Word> wordObj) override;
        std::vector<std::shared_ptr<Word>> getTaskResult(TaskType taskType) override;
        std::vector<std::shared_ptr<Word>> getTaskResult(TaskType taskType, const std::string& word) override;
    private:
        /**
        * \brief Sets a collection of longest words. It compares the current word length with the longest length seen so far.
        * If the lengths are equal, it adds the word to the collection. If the length is greater than max, it clears the list,
        * adds the current word to the fresh list and sets a new max threshold.
        * \param wordObj The current Word during extraction.
        */
        void setLongestWords(std::shared_ptr<Word> wordObj);
        /**
        * \brief Checks if current word's length is equal to or greater than 'logy' length, and less than 8 char long,
        * and ends with 'logy'. If true, word is added to collection.
        * \param wordObj The current word during extraction.
        */
        void setLogyWords(std::shared_ptr<Word> wordObj);
        /**
        * \brief Checks if current word's length is equal to or greater than min rhyme length.
        * If true, checks if rhyme key exists in rhyme map. If true, add to list of values,
        * else create a new map entry, with last three letters as key, and word as list entry.
        * \param wordObj The current word during extraction.
        */
        void setRhymes(std::shared_ptr<Word> wordObj);
        /**
        * \brief Sort letters alphabetically, strip any '-'. Result is key to anagram map.
        * If key exists, add to value (list of shared_ptr<Word>). If it doesn't exist,
        * add new k/v pair of alphabetically sorted letters as key, and a new list of shared_ptr<Word>,
        * inserting current shared_ptr<Word> into it.
        * \param wordObj The current word during extraction.
        */
        void setAnagrams(std::shared_ptr<Word> wordObj);
        /**
        * \brief Returns the collection of longest words found in dictionary.
        * \returns The collection of longest words found in dictionary.
        */
        std::vector<std::shared_ptr<Word>> getLongestWords() const;
        /**
        * \brief Returns the collection of words ending in 'logy' with length of seven or less.
        * \returns The collection of words ending in 'logy' with length of seven or less.
        */
        std::vector<std::shared_ptr<Word>> getLogyWords() const;
        /**
        * \brief Returns word/s that rhyme with the parameter word, if any exist.
        * \param word The word to search for rhymes.
        * \returns Word/s that rhyme with parameter word.
        */
        std::vector<std::shared_ptr<Word>> getRhymes(const std::string& word);
        /**
        * \brief Sort word's letters alphabetically, as key to anagram map.
        * If key exists in anagram map, return list value for that key, else return an empty list.
        * \param taskType Only WordAnagrams or StringAnagrams supported.
        * \param word The word to search for anagrams.
        * \returns Anagram/s of the word, if they exist, else returns an empty list.
        */
        std::vector<std::shared_ptr<Word>> getAnagrams(TaskType taskType, const std::string& word);
        /**
         * \brief Returns the rhyming part of the word if >= 3 letters,
         * else returns an empty string.
         * \param word The current word being extracted.
         * \returns The rhyming part of the word if >= 3 letters,
         * else returns an empty string. 
         */
        static std::string getRhymeKey(const std::string& word);
        /**
         * \brief If word length == 1, return word. Else remove all '-' from string.
         * Then sort alphabetically and return it.
         * \param word The word to generate an anagram key with.
         * \returns The word's letters sorted alphabetically and without '-'. 
         */
        static std::string getAnagramKey(const std::string& word);
        /**
        * \brief Filter the results based on a lambda predicate.
        * \param result The collection of results from the task.
        * \param predicate The predicate lambda expression, where if true, will exclude the result from the collection.
        * \return A new result after filter is applied.
        */
        template<typename Predicate>
        static std::vector<std::shared_ptr<Word>> filterResult(std::vector<std::shared_ptr<Word>> result, Predicate predicate);
        /**
        * \brief Returns true if the word ends with ending.
        * \param word The word to inspect.
        * \param ending The ending of the word we'd like to find.
        * \return True if the word ends with ending.
        */
        static bool endsWith(const std::string& word, const std::string& ending);
    };
}

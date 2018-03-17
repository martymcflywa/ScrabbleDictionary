#pragma once
#include <list>
#include <unordered_map>
#include "IExtract.h"
#include "ILoad.h"
#include "Word.h"

namespace lib {

    /**
     * \brief A collection of Word objects loaded from a source (ie. text file).
     */
    class Dictionary
    {
        ILoad& _loader;
        IExtract& _extractor;
        ITask& _task;

        /**
         * \brief Was initially using std::map, but switched to std::unordered_map for O(1) lookup.
         * No constraints re memory, and data set isn't too large, seems a better choice over std::map when
         * searching for definition/scrabble score. Using std::shared_ptr<Word> to 
         * share instance with ITask cache.
         */
        std::unordered_map<std::string, std::shared_ptr<Word>> _dictionary{};

    public:
        /**
        * \brief Constructs the Dictionary. Responsible for loading entries from a source dictionary. 
        * Using dependency injection to decouple implementation details of loading and extracting.
        * \param loader Implementation of ILoad, responsible for loading dictionary entries from a source.
        * \param extractor Implementation of IExtract, responsible for extracting values from the source dictionary.
        * \param task Implementation of ITask, responsible for aggregating dictionary entries to answer questions about it.
        */
        Dictionary(ILoad& loader, IExtract& extractor, ITask& task);
        /**
        * \brief Loads dictionary entries from a source. Depends on ILoad and IExtract to load and extract the contents
        * from the source.
        * \returns map<string, Word> populated with entries from the source dictionary.
        */
        void loadDictionary();
        /**
         * \brief Searches for the word in collection. If it exists, returns the type and definition, 
         * else return message that word does not exist.
         * \param word The word to search for.
         * \return The definition or notify user word does not exist.
         */
        std::string getDefinition(const std::string& word);
        /**
        * \brief Returns the longest word/s in the dictionary.
        * \returns The longest word/s in the dictionary.
        */
        std::list<std::shared_ptr<Word>> getLongestWords() const;
        /**
        * \brief Returns words that end in 'logy' that have a length less than or equal to seven.
        * \returns Words that end in 'logy' that have a length less than or equal to seven.
        */
        std::list<std::shared_ptr<Word>> getLogyWords() const;
        /**
         * \brief Returns word/s that rhyme with the parameter word.
         * \param word The word to search for rhymes.
         * \returns Word/s that rhyme with parameter word.
         */
        std::list<std::shared_ptr<Word>> getRhymes(const std::string& word) const;
        /**
         * \brief Returns the score for the word. Misc, ProperNoun and hyphenated words always return 0;
         * \param word The word to search for its score.
         * \returns The score for the word if found, else returns 0.
         */
        int getScrabbleScore(const std::string& word) const;
        /**
         * \brief Search the dictionary for the word. If it exists, will look for anagrams of that word.
         * If it doesn't exist, or no anagrams exist, returns an empty list.
         * \param word The word to search for anagrams.
         * \returns Anagram/s of the word, if the word exists in the dictionary, else returns an empty list. 
         */
        std::list<std::shared_ptr<Word>> getWordAnagrams(const std::string& word) const;
        /**
         * \brief Search for any anagrams of the letters. Returns any anagrams that exist,
         * else returns an empty list.
         * \param letters The letters to search for anagrams.
         * \returns Anagram/s of the letters, if they exist, else returns an empty list. 
         */
        std::list<std::shared_ptr<Word>> getStringAnagrams(const std::string& letters) const;
        /**
         * \brief Returns how many entries are loaded in the dictionary.
         * \returns How many entries are loaded in the dictionary. 
         */
        int size() const;
    };
}

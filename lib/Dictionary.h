#pragma once
#include <list>
#include <unordered_map>
#include "IExtract.h"
#include "ILoad.h"
#include "ITask.h"
#include "Word.h"

namespace lib {

    /**
     * \brief A collection of Word objects loaded from a source (ie. text file).
     */
    class Dictionary
    {
        ILoad& _loader;
        IExtract<std::unordered_map<std::string, std::shared_ptr<Word>>, std::istream&>& _extractor;
        ITask& _task;

        /**
         * \brief Was initially using std::map, but switched to std::unordered_map for O(1) hash lookup.
         * Apparently uses more memory but brief has no memory constraints, and data set isn't too large.
         * Seems a better choice over std::map when searching for definition/scrabble score with O(log n) bst lookup. 
         * Using std::shared_ptr<Word> to share instance with ITask result cache.
         * 
         * Further investigation:
         * See discussion on stackoverflow re map vs. unordered_map: https://stackoverflow.com/q/2196995
         * This answer advises map has better performance due to bst key search: https://stackoverflow.com/a/2197457
         * But this answer argues that when inserting sorted to map, bst depth negates the performance: https://stackoverflow.com/a/12512109
         * Since dictionary2018.txt is sorted, map's bst would be unbalanced on insert. Sticking with unoredered_map.
         * Also interesting point re DoS vulnerability of unordered_map: https://stackoverflow.com/a/41384008
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
        Dictionary(
            ILoad& loader, 
            IExtract<std::unordered_map<std::string, std::shared_ptr<Word>>, std::istream&>& extractor, 
            ITask& task);
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
         * If it doesn't exist, returns an empty list.
         * \param word The word to search for anagrams.
         * \returns Anagram/s of the word, if the word exists in the dictionary, else returns an empty list. 
         */
        std::list<std::shared_ptr<Word>> getWordAnagrams(const std::string& word) const;
        /**
        * \brief Search for anagrams of a string of letters.
        * Returns any anagrams that exist, else returns an empty list.
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

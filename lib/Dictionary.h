#pragma once
#include <map>
#include <regex>
#include "Word.h"
#include "ILoad.h"
#include "IExtract.h"
#include <list>

using namespace std;
using namespace lib;

namespace lib {

    /**
     * \brief A collection of Word objects loaded from a source (ie. text file).
     */
    class Dictionary
    {
        ILoad& _loader;
        IExtract& _extractor;
        map<string, Word> _dictionary{};

    public:
        /**
        * \brief Constructs the Dictionary. Responsible for loading entries from a source dictionary. 
        * Using dependency injection to decouple implementation details of loading and extracting.
        * \param loader Implementation of ILoad, responsible for loading dictionary entries from a source.
        * \param extractor Implementation of IExtract, responsible for extracting values from the source dictionary.
        */
        Dictionary(ILoad& loader, IExtract& extractor);
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
        string getDefinition(const string& word);
        /**
        * \brief Returns the longest word/s in the dictionary.
        * \returns The longest word/s in the dictionary.
        */
        list<string> getLongestWord() const;
        /**
        * \brief Returns words that end in 'logy' that have a length less than or equal to seven.
        * \returns Words that end in 'logy' that have a length less than or equal to seven.
        */
        list<string> getLogyWords() const;
        /**
         * \brief Returns how many entries are loaded in the dictionary.
         * \returns How many entries are loaded in the dictionary. 
         */
        int size() const;
    };
}

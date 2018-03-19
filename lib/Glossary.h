#pragma once
#include <istream>
#include "Dictionary.h"
#include "IExtract.h"
#include "Word.h"

namespace lib
{
    class IFormat;
    class ILoad;

    /**
     * \brief Responsible for
     * Determining usage of words from a text file that exist in a dictionary.
     * Generating a glossary of rare words from a text file that appear in a dictionary.
     * Glossary words must be unique.
     */
    class Glossary
    {
        Dictionary& _dictionary;
        IExtract<std::vector<std::string>, std::istream&>& _extractor;

    public:
        /**
         * \brief Constructs the Glossary.
         * \param dictionary A reference to a Dictionary object. Must be completely loaded.
         * \param extractor An implementation of IExtract, responsible for extracting all
         * words from a text file, without punctuation, special or uppercase characters.
         */
        Glossary(Dictionary& dictionary, IExtract<std::vector<std::string>, std::istream&>& extractor);
        /**
         * \brief Scans a text file and extracts all words from it. If word appears in the dictionary,
         * increment the Word's usage field.
         * \param loader The file loader responsible for reading the text file.
         */
        void setUsageFrequency(ILoad& loader) const;
        /**
        * \brief Scans a text file and extracts all words from it. If word is rare,
        * add its definition to collection.
        * Using std::map to keep words unique and in alphabetical order.
        * \param loader The file loader responsible for reading the text file.
        * \param formatter The formatter for glossary entries.
        * \returns A collection of unique rare word definitions
        */
        std::map<std::string, std::string> generateGlossary(ILoad& loader, IFormat& formatter) const;
    };
}


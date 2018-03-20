#pragma once
#include <istream>
#include "Dictionary.h"
#include "IExtract.h"
#include "IWrite.h"
#include "Word.h"

namespace lib
{
    class IFormat;
    class IRead;

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
        IFormat& _formatter;
        IWrite<const std::string&>& _writer;
        std::map<std::string, std::string> _glossary {};

    public:
        /**
         * \brief Constructs the Glossary.
         * \param dictionary A reference to a Dictionary object. Must be completely loaded.
         * \param extractor An implementation of IExtract, responsible for extracting all
         * words from a text file, without punctuation, special or uppercase characters.
         * \param formatter Formats the glossary entries when writing to file.
         * \param writer An implementation of IWriter, responsible for writing the glossary.
         */
        Glossary(
            Dictionary& dictionary,
            IExtract<std::vector<std::string>, std::istream&>& extractor,
            IFormat& formatter,
            IWrite<const std::string&>& writer);
        /**
         * \brief Scans a text file and extracts all words from it. If word appears in the dictionary,
         * increment the Word's usage field.
         * \param reader The file reader responsible for reading the text file.
         */
        void setUsageFrequency(IRead& reader) const;
        /**
        * \brief Scans a text file and extracts all words from it. If word is rare,
        * add its definition to collection.
        * Using std::map to keep words unique and in alphabetical order.
        * \param reader The file reader responsible for reading the text file.
        * \returns A collection of unique rare word definitions
        */
        void generate(IRead& reader);
        /**
         * \brief Writes the generated glossary to file.
         */
        void write() const;
        std::string getOutputFilepath() const;
    };
}


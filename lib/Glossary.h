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
        IRead& _usageReader;
        IRead& _rareWordReader;
        IExtract<std::vector<std::string>, std::istream&>& _extractor;
        IFormat& _formatter;
        IWrite<const std::string&>& _writer;
        std::map<std::string, std::string> _glossary {};
        bool _isLoaded;

    public:
        /**
         * \brief Constructs the Glossary.
         * \param dictionary A reference to a Dictionary object. Must be completely loaded.
         * \param usageReader Reads the source which determines word usage.
         * \param rareWordReader Reads the source to generate a glossary of rare words from.
         * \param extractor An implementation of IExtract, responsible for extracting all
         * words from a text file, without punctuation, special or uppercase characters.
         * \param formatter Formats the glossary entries when writing to file.
         * \param writer An implementation of IWriter, responsible for writing the glossary.
         */
        Glossary(
            Dictionary& dictionary,
            IRead& usageReader,
            IRead& rareWordReader,
            IExtract<std::vector<std::string>, std::istream&>& extractor,
            IFormat& formatter,
            IWrite<const std::string&>& writer);

        /**
         * \brief Use as non-blocking asynchronous call to generate the glossary.
         */
        void generateAsync();
        /**
         * \brief Writes the generated glossary to file.
         */
        void write() const;
        /**
         * \brief Returns ptr to glossary as const read only. Helper to print entries.
         * \returns readonly const ptr to glossary so we can print it to user interface.
         */
        const std::map<std::string, std::string>* getGlossary() const;
        std::string getOutputFilepath() const;
        /**
         * \brief Returns true if generate glossary async task complete.
         * \returns True if generate glossary async task complete.
         */
        bool isLoaded() const;
        unsigned size() const;
    private:
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
        */
        void generate(IRead& reader);
    };
}


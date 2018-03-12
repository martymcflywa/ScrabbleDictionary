#pragma once
#include "IExtract.h"
#include "ITask.h"

namespace lib
{
    /**
    * \brief Implementation of IExtract, using std::string::substr() which follows the expected format of Dictionary2018.txt.
    * It assumes that a single entry within the source dictionary will be composed of three separate lines.
    * First line contains word and type.
    * Second line contains definition.
    * Third line is empty, delimiter for the next entry.
    */
    class StringExtractor : public IExtract
    {
        IPrint& _printer;
        ITask& _task;

    public:
        /**
        * \brief StringExtractor constructor.
        * \param printer Implementation of IPrinter interface, dependency of constructing Words.
        */
        StringExtractor(IPrint& printer, ITask& task);
        /**
         * \brief Extracts/parses words, types and definitions from a source dictionary.
         * \param content The stream from source dictionary.
         * \return The dictionary as a map<string, Word> where the key is the word itself.
         */
        map<string, Word> extract(istream& content) override;
        /**
         * \brief Returns the longest word in the dictionary.
         * \returns The longest word in the dictionary.
         */
        string getLongestWord() override;
        list<string> getLogyWords() override;

    private:
        string extractWord(const string& line) const;
        string extractType(const string& line) const;
        static string extract(const string& line, int start, int length);
    };
}

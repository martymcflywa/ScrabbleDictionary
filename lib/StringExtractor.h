#pragma once
#include "IExtract.h"

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

    public:
        /**
        * \brief StringExtractor constructor.
        * \param printer Implementation of IPrinter interface, dependency of constructing Words.
        */
        StringExtractor(IPrint& printer);
        map<string, Word> extract(istream& content) override;

    private:
        string extractWord(const string& line) const;
        string extractType(const string& line) const;
        static string extract(const string& line, int start, int length);
    };
}

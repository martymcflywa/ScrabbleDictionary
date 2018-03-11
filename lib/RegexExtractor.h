#pragma once
#include "IExtract.h"

namespace lib
{
    /**
     * \brief Implementation of IExtract, which follows the expected format of Dictionary2018.txt.
     * It assumes that a single entry within the source dictionary will be composed of three separate lines.
     * First line contains word and type.
     * Second line contains definition.
     * Third line is empty, delimiter for the next entry.
     */
    class RegexExtractor : public IExtract
    {
        IPrint& _printer;
        const string HEADER_PATTERN = "^(\\S+) \\[(\\w+)\\]";
        const string DEFINITION_PATTERN = "^.*";
        const string END_OF_ENTRY_PATTERN = "^\\s*$";

    public:
        /**
         * \brief RegexExtractor constructor.
         * \param printer Implementation of IPrinter interface, dependency of constructing Words.
         */
        RegexExtractor(IPrint& printer);
        map<string, Word> extract(istream& content) override;

    private:
        string extractWord(string& line) const;
        string extractType(string& line) const;
        string extractDefinition(string& line) const;
        string extract(string pattern, string& line, int groupIndex) const;
    };
}
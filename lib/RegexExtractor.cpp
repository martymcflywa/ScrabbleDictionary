#include "stdafx.h"
#include <regex>
#include "RegexExtractor.h"
#include "WordFactory.h"

RegexExtractor::RegexExtractor(IPrint& printer) : _printer(printer)
{
}

map<string, Word> RegexExtractor::extract(istream& content)
{
    const auto firstLine = 0;
    const auto lastLine = 2;
    auto currentLine = 0;

    auto output = map<string, Word>();

    string line;
    string word;
    string type;
    string definition;

    while (getline(content, line))
    {
        // the last line of the entry, time to construct the word and add it to collection.
        if (currentLine == lastLine)
        {
            output.insert(pair<string, Word>(word, WordFactory::build(word, type, definition, _printer)));
            currentLine = 0;
            continue;
        }

        // the first line of the entry, grab the word and type
        if (currentLine == firstLine)
        {
            word = extractWord(line);
            type = extractType(line);
            currentLine++;
            continue;
        }

        // the second line of the entry (implied), grab the definition
        definition = extractDefinition(line);
        currentLine++;
    }
    return output;
}

string RegexExtractor::extractWord(const string& line) const
{
    const auto groupIndex = 1;
    return extract(HEADER_PATTERN, line, groupIndex);
}

string RegexExtractor::extractType(const string& line) const
{
    const auto groupIndex = 2;
    return extract(HEADER_PATTERN, line, groupIndex);
}

string RegexExtractor::extractDefinition(const string& line) const
{
    const auto groupIndex = 0;
    return extract(DEFINITION_PATTERN, line, groupIndex);
}

string RegexExtractor::extract(const string& pattern, const string& line, int groupIndex) const
{
    const regex regex(pattern, regex_constants::ECMAScript);
    smatch match;
    regex_match(line, match, regex);

    if (match.empty())
        return "";

    return match[groupIndex];
}

#include "stdafx.h"
#include <regex>
#include "TextFileExtractor.h"
#include "WordFactory.h"

TextFileExtractor::TextFileExtractor(IPrint& printer) : _printer(printer)
{
}

map<string, Word> TextFileExtractor::extract(istream& content)
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

string TextFileExtractor::extractWord(string& line) const
{
    const auto groupIndex = 1;
    return extract(HEADER_PATTERN, line, groupIndex);
}

string TextFileExtractor::extractType(string& line) const
{
    const auto groupIndex = 2;
    return extract(HEADER_PATTERN, line, groupIndex);
}

string TextFileExtractor::extractDefinition(string& line) const
{
    const auto groupIndex = 0;
    return extract(DEFINITION_PATTERN, line, groupIndex);
}

string TextFileExtractor::extract(string pattern, string& line, int groupIndex) const
{
    const regex regex(pattern, regex_constants::ECMAScript);
    smatch match;
    regex_match(line, match, regex);

    if (match.empty())
        return "";

    return match[groupIndex];
}

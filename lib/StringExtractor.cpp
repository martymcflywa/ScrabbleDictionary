#include "stdafx.h"
#include "StringExtractor.h"
#include "WordFactory.h"

StringExtractor::StringExtractor(IPrint& printer) : _printer(printer)
{
}

map<string, Word> StringExtractor::extract(istream& content)
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
        definition = line;
        currentLine++;
    }
    return output;
}

string StringExtractor::extractWord(const string& line) const
{
    const auto start = 0;
    const auto length = line.find("[", start) - 1;

    return extract(line, start, length);
}

string StringExtractor::extractType(const string& line) const
{
    const auto start = line.find("[", 0) + 1;
    const auto end = line.find("]", start);
    const auto length = end - start;

    return extract(line, start, length);
}

string StringExtractor::extract(const string& line, const int start, const int length)
{
    if (start < 0 || length < 1)
        return "";

    return line.substr(start, length);
}

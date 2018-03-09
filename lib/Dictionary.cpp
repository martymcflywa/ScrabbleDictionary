#include "stdafx.h"
#include "Dictionary.h"
#include <regex>

/**
 * \brief Constructs the Dictionary. Responsible for loading entries from a source dictionary. Using dependency injection to decouple
 * implementation of loading and printing.
 * \param loader Inject implementation of ILoader to decouple Dictionary from implementation detail of loading. Allows flexibility if
 * requirements ever change and the source changes to database rather than file.
 * \param printer Same goes for IPrinter. Currently we are printing to console but what if future requirements change and we want to print as Json.
 */
Dictionary::Dictionary(ILoader& loader, IPrinter& printer) : _loader(loader), _printer(printer)
{
}

/**
 * \brief Load dictionary entries from a source. Depends on ILoader to retrieve the contents from the source.
 * The function then iterates over each line, using regex to extract words, types and definitions.
 * The currentLine counter and isEndOfEntry() is used to group together entries which extend over multiple lines.
 * \param location The location of the dictionary source. Can be a filepath, db connection string etc. It depends on the injected ILoader.
 * \returns The dictionary as map<string, Word> where the key is the actual word itself, and the value is the Word object.
 */
map<string, Word> Dictionary::loadDictionary(const string& location) const
{
    auto& content = _loader.load(location);
    string line;
    auto output = map<string, Word>();

    auto currentLine = 0;
    string word;
    string type;
    string definition;

    while (getline(content, line))
    {
        // the last blank line of the entry, time to construct the word and add it to collection.
        if (isEndOfEntry(line))
        {
            output.insert(pair<string, Word>(word, buildWord(word, type, definition)));
            currentLine = 0;
            continue;
        }

        // the first line of the entry, grab the word and type
        if (currentLine == 0)
        {
            word = extractWord(line);
            type = extractType(line);
            currentLine++;
            continue;
        }

        // the second line of the entry, grab the definition
        definition = extractDefinition(line);
        currentLine++;
    }
    return output;
}

bool Dictionary::isEndOfEntry(string& line) const
{
    const regex pattern(END_OF_ENTRY_PATTERN, regex_constants::ECMAScript);
    smatch match;
    regex_match(line, match, pattern);

    return !match.empty();
}

string Dictionary::extractWord(string& line) const
{
    const auto groupIndex = 1;
    return extract(HEADER_PATTERN, line, groupIndex);
}

string Dictionary::extractType(string& line) const
{
    const auto groupIndex = 2;
    return extract(HEADER_PATTERN, line, groupIndex);
}

string Dictionary::extractDefinition(string& line) const
{
    const auto groupIndex = 0;
    return extract(DEFINITION_PATTERN, line, groupIndex);
}

string Dictionary::extract(string pattern, string& line, int groupIndex) const
{
    const regex regex(pattern, regex_constants::ECMAScript);
    smatch match;
    regex_match(line, match, regex);

    if (match.empty())
        return "";

    return match[groupIndex];
}

Word Dictionary::buildWord(string& word, string& type, string& definition) const
{
    if (word.empty())
        throw invalid_argument("Word is empty");
    if (type.empty())
        throw invalid_argument("Type is empty");
    if (definition.empty())
        throw invalid_argument("Definition is empty");

    return { word, type, definition, _printer };
}

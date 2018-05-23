#include "stdafx.h"
#include <algorithm>
#include <regex>
#include <string>
#include "GlossaryExtractor.h"

using namespace std;
using namespace lib;

/**
* \brief Extracts words from a text file, ignoring any special characters,
* converting words to lowercase.
* \param content The stream from the source text file.
* \return A collection of lowercase words extracted from the text file.
*/
vector<string> GlossaryExtractor::extract(istream& content)
{
    string line;
    auto words = vector<string>();

    while(!content.eof())
    {
        getline(content, line);

        // TODO: solution here ensures hyphenated words are also captured.
        // BUT it doubles the processing time. Could do with optimizing.
        // IDEA: could using regex exclusively improve efficiency?

        // Old vs. new solution:
        // Processing time: old = ~25s, new = ~45s
        // Result: old = 155 entries, new = 149 entries
        // After diffing both glossary.txt files, appears new solution
        // is more correct, although there is still ambiguity with usage
        // of '-' in source text files, so it's still not 100%.

        // words in text are sometimes delimited by "--", as well as " "
        const auto onlySpaces = replace(line, "--", " ");
        auto tokens = split(onlySpaces, SPECIAL_CHARS);

        // append to words
        words.insert(words.end(), tokens.begin(), tokens.end());
    }
    return words;
}

/**
* \brief If found in the line, the 'pattern' will be replaced by 'replacement'.
* \param line The line to search for the pattern.
* \param pattern A regex pattern as a string. Must follow ECMAScript regex syntax.
* TODO: Throw exception if incorrect syntax
* \param replacement What to replace the pattern with in the line.
* \return The line with the pattern replaced by the replacement.
*/
string GlossaryExtractor::replace(const string& line, const string& pattern, const string& replacement) const
{
    const auto rgx = regex(pattern, regex_constants::ECMAScript);
    string output;
    regex_replace(back_inserter(output), line.begin(), line.end(), rgx, replacement);
    return output;
}

/**
* \brief Splits a string into a vector of strings based on a delimiter.
* \param line The line to split.
* \param delimiter The delimiter to split on.
* \return A vector of strings, without the delimiter.
*/
vector<string> GlossaryExtractor::split(string line, const string& delimiter)
{
    auto tokens = vector<string>{};

    unsigned start = 0;
    unsigned end;

    do
    {
        start = line.find_first_not_of(delimiter, start);

        if (start == string::npos)
            break;

        end = line.find_first_of(delimiter, start);
        auto token = line.substr(start, end - start);
        transform(token.begin(), token.end(), token.begin(), ::tolower);

        if (!token.empty())
            tokens.push_back(token);

        start = end + 1;
    }
    while (end != string::npos);

    return tokens;
}

/**
* \brief Splits each string in the input vector to a flattened output vector,
* based on a delimiter.
* \param tokens The vector of tokens to split.
* \param delimiter The delimiter to split on.
* \return A flattened vector of strings, without the delimiter.
*/
vector<string> GlossaryExtractor::split(vector<string> tokens, const string& delimiter)
{
    auto words = vector<string>{};

    for (const auto& token : tokens)
    {
        const auto splitTokens = split(token, delimiter);
        words.insert(words.end(), splitTokens.begin(), splitTokens.end());
    }
    return words;
}

/**
* \brief Erases the target from a collection of strings.
* \param tokens The collection of strings to search and remove the target from.
* \param target The target to delete.
* \return The collection of strings with the target erased.
*/
std::vector<std::string> GlossaryExtractor::erase(std::vector<std::string> tokens, const char& target) const
{
    auto words = vector<string>{};

    for (auto& token : tokens)
    {
        token.erase(remove(token.begin(), token.end(), target), token.end());

        if (!token.empty())
            words.push_back(token);
    }
    return words;
}

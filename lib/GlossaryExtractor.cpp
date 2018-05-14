#include "stdafx.h"
#include <algorithm>
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
        unsigned start = 0;
        unsigned end;

        do
        {
            start = line.find_first_not_of(SPECIAL_CHARS, start);

            if (start == string::npos)
                break;

            end = line.find_first_of(SPECIAL_CHARS, start);

            auto word = line.substr(start, end - start);
            transform(word.begin(), word.end(), word.begin(), tolower);

            words.push_back(word);
            start = end + 1;
        }
        while (end != string::npos);
    }
    return words;
}

#include "stdafx.h"
#include <map>
#include "Glossary.h"
#include "IFormat.h"


using namespace std;
using namespace lib;
/**
* \brief Constructs the Glossary.
* \param dictionary A reference to a Dictionary object. Must be completely loaded.
* \param extractor An implementation of IExtract, responsible for extracting all
* words from a text file, without punctuation, special or uppercase characters.
*/
Glossary::Glossary(Dictionary& dictionary, IExtract<vector<string>, istream&>& extractor) :
    _dictionary(dictionary),
    _extractor(extractor)
{
}

/**
* \brief Scans a text file and extracts all words from it. If word appears in the dictionary,
* increment the Word's usage field.
* \param loader The file loader responsible for reading the text file.
*/
void Glossary::setUsageFrequency(ILoad& loader) const
{
    // TODO: can we make this concurrent producer/consumer?
    auto words = _extractor.extract(loader.load());
    loader.dispose();

    for (auto& word : words)
    {
        _dictionary.incrementUsage(word);
    }
}

/**
* \brief Scans a text file and extracts all words from it. If word is rare,
* add its definition to collection.
* Using std::map to keep words unique and in alphabetical order.
* \param loader The file loader responsible for reading the text file.
* \param formatter The formatter for glossary entries.
* \returns A collection of unique rare word definitions
*/
map<string, string> Glossary::generateGlossary(ILoad& loader, IFormat& formatter) const
{
    // TODO: can we make this concurrent producer/consumer?
    auto words = _extractor.extract(loader.load());
    loader.dispose();

    map<string, string> glossary;

    for (auto& word : words)
    {
        if (_dictionary.isRareWord(word))
        {
            const auto rareWord = _dictionary.get(word);

            // sanity check, make sure word exists
            if (rareWord == nullptr)
                continue;

            glossary.insert(pair<string, string>(word, formatter.format(*rareWord)));
        }
    }

    return glossary;
}

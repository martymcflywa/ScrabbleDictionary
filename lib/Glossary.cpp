#include "stdafx.h"
#include "Glossary.h"
#include "IFormat.h"


using namespace std;
using namespace lib;
/**
* \brief Constructs the Glossary.
* \param dictionary A reference to a Dictionary object. Must be completely loaded.
* \param extractor An implementation of IExtract, responsible for extracting all
* words from a text file, without punctuation, special or uppercase characters.
* \param formatter Formats the glossary entries when writing to file.
* \param writer An implementation of IWriter, responsible for writing the glossary.
*/
Glossary::Glossary(
        Dictionary& dictionary, 
        IExtract<vector<string>, istream&>& extractor,
        IFormat& formatter,
        IWrite<const string&>& writer) :
    _dictionary(dictionary),
    _extractor(extractor),
    _formatter(formatter),
    _writer(writer)
{
}

/**
* \brief Scans a text file and extracts all words from it. If word appears in the dictionary,
* increment the Word's usage field.
* \param reader The file reader responsible for reading the text file.
*/
void Glossary::setUsageFrequency(IRead& reader) const
{
    // TODO: can we make this concurrent producer/consumer?
    auto words = _extractor.extract(reader.read());
    reader.dispose();

    for (auto& word : words)
    {
        _dictionary.incrementUsage(word);
    }
}

/**
* \brief Scans a text file and extracts all words from it. If word is rare,
* add its definition to collection.
* Using std::map to keep words unique and in alphabetical order.
* \param reader The file reader responsible for reading the text file.
* \returns A collection of unique rare word definitions
*/
void Glossary::generate(IRead& reader)
{
    // TODO: can we make this concurrent producer/consumer?
    auto words = _extractor.extract(reader.read());
    reader.dispose();

    for (auto& word : words)
    {
        if (_dictionary.isRareWord(word))
        {
            const auto* rareWord = _dictionary.get(word);

            // sanity check, make sure word exists
            if (rareWord == nullptr)
                continue;

            _glossary.insert(pair<string, string>(word, _formatter.format(*rareWord)));
        }
    }
}

/**
* \brief Writes the generated glossary to file.
*/
void Glossary::write() const
{
    // build a string from the map
    string glossary = "";

    for (const auto& it : _glossary)
        glossary += it.second + "\n\n";

    _writer.write(glossary);
}

std::string Glossary::getOutputFilepath() const
{
    return _writer.getFilepath();
}

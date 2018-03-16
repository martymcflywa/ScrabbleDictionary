#include "stdafx.h"
#include "Dictionary.h"

using namespace std;
using namespace lib;

/**
 * \brief Constructs the Dictionary. Responsible for loading entries from a source dictionary. 
 * Using dependency injection to decouple implementation details of loading and extracting.
 * \param loader Implementation of ILoad, responsible for loading dictionary entries from a source.
 * \param extractor Implementation of IExtract, responsible for extracting values from the source dictionary.
 */
Dictionary::Dictionary(ILoad& loader, IExtract& extractor) : _loader(loader), _extractor(extractor)
{
}

/**
 * \brief Loads dictionary entries from a source. Depends on ILoad and IExtract to load and extract the contents from the source.
 */
void Dictionary::loadDictionary()
{
    auto& content = _loader.load();
    _dictionary = _extractor.extract(content);
    _loader.dispose();
}

/**
* \brief Searches for the word in collection. If it exists, returns the type and definition, 
* else return message that word does not exist.
* \param word The word to search for.
* \return The definition or notify user word does not exist.
*/
string Dictionary::getDefinition(const string& word)
{
    const auto it = _dictionary.find(word);

    if (it == _dictionary.end())
        return "Word '" + word + "' not found";

    return it->second->printDefinition();
}

/**
* \brief Returns the longest word/s in the dictionary.
* \returns The longest word/s in the dictionary.
*/
list<string> Dictionary::getLongestWords() const
{
    return _extractor.getLongestWords();
}

/**
* \brief Returns words that end in 'logy' that have a length less than or equal to seven.
* \returns Words that end in 'logy' that have a length less than or equal to seven.
*/
list<string> Dictionary::getLogyWords() const
{
    return _extractor.getLogyWords();
}

/**
* \brief Returns word/s that rhyme with the parameter word.
* \param word The word to search for rhymes.
* \returns Word/s that rhyme with parameter word.
*/
list<string> Dictionary::getRhymes(const std::string& word) const
{
    return _extractor.getRhymes(word);
}

/**
* \brief Returns the score for the word. Misc, ProperNoun and hyphenated words always return 0;
* \param word The word to search for its score.
* \returns The score for the word if found, else returns -1.
*/
int Dictionary::getScrabbleScore(const std::string& word) const
{
    const auto it = _dictionary.find(word);

    // if not found, return a negative value,
    // so we can tell difference between not found and words you can't use in scrabble
    if (it == _dictionary.end())
        return -1;

    return it->second->getScrabbleScore();
}

/**
* \brief Returns how many entries are loaded in the dictionary.
* \returns How many entries are loaded in the dictionary.
*/
int Dictionary::size() const
{
    return _dictionary.size();
}

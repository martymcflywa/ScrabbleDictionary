#include "stdafx.h"
#include "Dictionary.h"

using namespace std;
using namespace lib;

/**
 * \brief Constructs the Dictionary. Responsible for loading entries from a source dictionary. 
 * Using dependency injection to decouple implementation details of extracting and tasks.
 * \param extractor Implementation of IExtract, responsible for extracting values from the source dictionary.
 * \param task Implementation of ITask, responsible for aggregating data from the dictionary during extract loop.
 */
Dictionary::Dictionary(
        IExtract<std::unordered_map<std::string, std::shared_ptr<Word>>, std::istream&>& extractor,
        ITask& task) :
    _extractor(extractor),
    _task(task)
{
}

/**
* \brief Loads dictionary entries from a source. Depends on IRead and IExtract to read and extract the contents
* from a source.
* \param reader Implementation of IReader. In this case, it should be able to read text files.
*/
void Dictionary::loadDictionary(IRead& reader)
{
    // TODO: can we make this concurrent producer/consumer?
    _dictionary = _extractor.extract(reader.read());
    reader.dispose();
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

    return it == _dictionary.end() ? "Word '" + word + "' not found" : it->second->printDefinition();
}

/**
* \brief Returns the longest word/s in the dictionary.
* \returns The longest word/s in the dictionary.
*/
vector<shared_ptr<Word>> Dictionary::getLongestWords() const
{
    return _task.getTaskResult(LongestWords);
}

/**
* \brief Returns words that end in 'logy' that have a length less than or equal to seven.
* \returns Words that end in 'logy' that have a length less than or equal to seven.
*/
vector<shared_ptr<Word>> Dictionary::getLogyWords() const
{
    return _task.getTaskResult(LogyWords);
}

/**
* \brief Returns word/s that rhyme with the parameter word.
* \param word The word to search for rhymes.
* \returns Word/s that rhyme with parameter word.
*/
vector<shared_ptr<Word>> Dictionary::getRhymes(const string& word) const
{
    return _task.getTaskResult(Rhymes, word);
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
    return it == _dictionary.end() ? -1 : it->second->getScrabbleScore();
}

/**
* \brief Search the dictionary for the word. If it exists, will look for anagrams of that word.
* If it doesn't exist, returns an empty list.
* \param word The word to search for anagrams.
* \returns Anagram/s of the word, if the word exists in the dictionary, else returns an empty list.
*/
vector<shared_ptr<Word>> Dictionary::getWordAnagrams(const string& word) const
{
    const auto it = _dictionary.find(word);

    return it == _dictionary.end() ? vector<shared_ptr<Word>>() : _task.getTaskResult(WordAnagrams, word);
}

/**
* \brief Search for anagrams of a string of letters.
* Returns any anagrams that exist, else returns an empty list.
* \param letters The letters to search for anagrams.
* \returns Anagram/s of the letters, if they exist, else returns an empty list.
*/
vector<shared_ptr<Word>> Dictionary::getStringAnagrams(const string& letters) const
{
    return _task.getTaskResult(StringAnagrams, letters);
}

/**
* \brief Increments a Word's usage if found in the dictionary.
* \param word The word to search for and increment its usage.
*/
void Dictionary::incrementUsage(const std::string & word) const
{
    const auto it = _dictionary.find(word);

    if (it != _dictionary.end())
        it->second->incrementUsage();
}

/**
* \brief Returns true if word exists and usage == 1.
* \returns True if word exists and usage == 1.
*/
bool Dictionary::isRareWord(const std::string& word) const
{
    const auto it = _dictionary.find(word);

    return it == _dictionary.end() ? false : it->second->isRareWord();
}

Word* Dictionary::get(const std::string& word)
{
    const auto it = _dictionary.find(word);
    
    if (it == _dictionary.end())
        return nullptr;

    return it->second.get();
}

/**
* \brief Returns how many entries are loaded in the dictionary.
* \returns How many entries are loaded in the dictionary.
*/
int Dictionary::size() const
{
    return _dictionary.size();
}

#include "stdafx.h"
#include "StringExtractor.h"
#include "WordFactory.h"

using namespace std;
using namespace lib;

/**
* \brief StringExtractor constructor.
* \param printer Implementation of IPrinter interface, dependency of constructing Words.
* \param task Implementation of ITask interface, responsible for performing tasks outlined in the brief,
* ie. Get longest word, get words that end with 'logy'.
*/
StringExtractor::StringExtractor(IPrint& printer, ITask& task) : _printer(printer), _task(task)
{
}

/**
* \brief Extracts/parses words, types and definitions from a source dictionary. It adds an optimization where dictionary tasks
* are evaluated in this loop as well by using ITask, improves response times when user requests answers for questions.
* \param content The stream from source dictionary.
* \return The dictionary as a map<string, Word> where the key is the word itself.
*/
map<string, shared_ptr<Word>> StringExtractor::extract(istream& content)
{
    const auto firstLine = 0;
    const auto lastLine = 2;
    auto currentLine = 0;

    auto output = map<string, shared_ptr<Word>>();

    string line;
    string word;
    string type;
    string definition;

    while (getline(content, line))
    {
        // the last line of the entry, time to construct the word and add it to collection.
        if (currentLine == lastLine)
        {
            output.insert(pair<string, shared_ptr<Word>>(word, WordFactory::build(word, type, definition, _printer)));

            // optimisation: find answers for tasks in the one loop
            _task.setLongestWords(word);
            _task.setLogyWords(word);
            _task.setRhymes(word);

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
/**
* \brief Returns the longest word/s in the dictionary.
* \returns The longest word/s in the dictionary.
*/
list<string> StringExtractor::getLongestWords()
{
    return _task.getLongestWords();
}

/**
* \brief Returns words that end in 'logy' that have a length less than or equal to seven.
* \returns Words that end in 'logy' that have a length less than or equal to seven.
*/
list<string> StringExtractor::getLogyWords()
{
    return _task.getLogyWords();
}

/**
* \brief Returns word/s that rhyme with the parameter word, if any exist.
* \param word The word to search for rhymes.
* \returns Word/s that rhyme with parameter word.
*/
list<string> StringExtractor::getRhymes(const string& word)
{
    return _task.getRhymes(word);
}

/**
* \brief Uses '[' to determine location of word in the line.
* \param line The current line being inspected from the source file.
* \returns The word.
*/
string StringExtractor::extractWord(const string& line) const
{
    const auto start = 0;
    const auto length = line.find("[", start) - 1;
    return extract(line, start, length);
}

/**
* \brief Uses '[' and ']' to determine location of type in the line.
* \param line The current line being inspected from the source file.
* \returns The type.
*/
string StringExtractor::extractType(const string& line) const
{
    const auto start = line.find("[", 0) + 1;
    const auto end = line.find("]", start);
    const auto length = end - start;
    return extract(line, start, length);
}

/**
* \brief Helper function to help keep extractWord and extractType DRY.
* \param line The current line being inspected from the source file.
* \param start The start index.
* \param length The length of the word.
* \returns The word.
*/
string StringExtractor::extract(const string& line, const int start, const int length)
{
    if (start < 0 || length < 1)
        return "";

    return line.substr(start, length);
}

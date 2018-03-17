#include "stdafx.h"
#include "DictionaryExtractor.h"
#include "WordFactory.h"

using namespace std;
using namespace lib;

/**
* \brief DictionaryExtractor constructor.
* \param printer Implementation of IPrinter interface, dependency of constructing Words.
* \param task Implementation of ITask interface, responsible for performing tasks outlined in the brief,
* ie. Get longest word, get words that end with 'logy'.
*/
DictionaryExtractor::DictionaryExtractor(IPrint& printer, ITask& task) : _printer(printer), _task(task)
{
}

/**
* \brief Extracts/parses words, types and definitions from a source dictionary. It adds an optimization where dictionary tasks
* are evaluated in this loop as well by using ITask, improves response times when user requests answers for questions.
* \param content The stream from source dictionary.
* \return The dictionary as a map<string, Word> where the key is the word itself.
*/
unordered_map<string, shared_ptr<Word>> DictionaryExtractor::extract(istream& content)
{
    const auto firstLine = 0;
    const auto lastLine = 2;
    auto currentLine = 0;

    auto output = unordered_map<string, shared_ptr<Word>>();

    string line;
    string word;
    string type;
    string definition;

    while (getline(content, line))
    {
        if (currentLine == lastLine)
        {
            // the last line of the entry, time to construct the word and add it to collection.
            const auto wordObj = make_shared<Word>(WordFactory::build(word, type, definition, _printer));
            output.insert(pair<string, shared_ptr<Word>>(word, wordObj));

            // optimisation: handle tasks in the extract loop while loading,
            // rather than multiple loops later on
            _task.handleTasks(wordObj);

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
* \brief Uses '[' to determine location of word in the line.
* \param line The current line being inspected from the source file.
* \returns The word.
*/
string DictionaryExtractor::extractWord(const string& line) const
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
string DictionaryExtractor::extractType(const string& line) const
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
string DictionaryExtractor::extract(const string& line, const int start, const int length)
{
    if (start < 0 || length < 1)
        return "";

    return line.substr(start, length);
}

#pragma once
#include <memory>
#include <unordered_map>
#include "IExtract.h"
#include "ITask.h"

namespace lib
{
    /**
    * \brief Implementation of IExtract, specific to extracting dictionary entries from dictionary2018.txt.
    * Each dictionary entry is composed of three lines.
    * First line: "word [type]\n"
    * Second line: "definition\n"
    * Third line: "\n" (empty line delimiter)
    */
    class DictionaryExtractor : public IExtract<std::unordered_map<std::string, std::shared_ptr<Word>>, std::istream&>
    {
        IPrint& _printer;
        ITask& _task;

    public:
        /**
        * \brief DictionaryExtractor constructor.
        * \param printer Implementation of IPrinter interface, dependency of constructing Words.
        * \param task Implementation of ITask interface, responsible for performing tasks outlined in the brief,
        * ie. Get longest word, get words that end with 'logy'.
        */
        DictionaryExtractor(IPrint& printer, ITask& task);
        /**
        * \brief Extracts/parses words, types and definitions from a source dictionary. It adds an optimization where dictionary tasks
        * are evaluated in this loop as well by using ITask, improves response times when user requests answers for questions.
        * \param content The stream from source dictionary.
        * \return The dictionary as a map<string, Word> where the key is the word itself.
        */
        std::unordered_map<std::string, std::shared_ptr<Word>> extract(std::istream& content) override;
    private:
        std::string extractWord(const std::string& line) const;
        /**
         * \brief Uses '[' and ']' to determine location of type in the line.
         * \param line The current line being inspected from the source file.
         * \returns The type.
         */
        std::string extractType(const std::string& line) const;
        /**
         * \brief Helper function to help keep extractWord and extractType DRY.
         * \param line The current line being inspected from the source file.
         * \param start The start index.
         * \param length The length of the word.
         * \returns The word. 
         */
        static std::string extract(const std::string& line, int start, int length);
    };
}

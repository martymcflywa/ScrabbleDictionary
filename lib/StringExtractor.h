#pragma once
#include "IExtract.h"
#include "ITask.h"
#include <memory>

namespace lib
{
    /**
    * \brief Implementation of IExtract, using std::string::find() and std::string::substr(), following the expected format of 
    * Dictionary2018.txt. It assumes that a single entry within the source dictionary will be composed of three separate lines.
    * First line contains word and type.
    * Second line contains definition.
    * Third line is empty, delimiter for the next entry.
    */
    class StringExtractor : public IExtract
    {
        IPrint& _printer;
        ITask& _task;

    public:
        /**
        * \brief StringExtractor constructor.
        * \param printer Implementation of IPrinter interface, dependency of constructing Words.
        * \param task Implementation of ITask interface, responsible for performing tasks outlined in the brief,
        * ie. Get longest word, get words that end with 'logy'.
        */
        StringExtractor(IPrint& printer, ITask& task);
        /**
        * \brief Extracts/parses words, types and definitions from a source dictionary. It adds an optimization where dictionary tasks
        * are evaluated in this loop as well by using ITask, improves response times when user requests answers for questions.
        * \param content The stream from source dictionary.
        * \return The dictionary as a map<string, Word> where the key is the word itself.
        */
        std::map<std::string, std::shared_ptr<Word>> extract(std::istream& content) override;
        /**
         * \brief Returns the longest word/s in the dictionary.
         * \returns The longest word/s in the dictionary.
         */
        std::list<std::string> getLongestWords() override;
        /**
         * \brief Returns words that end in 'logy' that have a length less than or equal to seven.
         * \returns Words that end in 'logy' that have a length less than or equal to seven. 
         */
        std::list<std::string> getLogyWords() override;
        /**
        * \brief Returns word/s that rhyme with the parameter word, if any exist.
        * \param word The word to search for rhymes.
        * \returns Word/s that rhyme with parameter word.
        */
        std::list<std::string> getRhymes(const std::string& word) override;
    private:
        /**
         * \brief Uses '[' to determine location of word in the line.
         * \param line The current line being inspected from the source file.
         * \returns The word. 
         */
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

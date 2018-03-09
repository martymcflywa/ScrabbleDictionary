#pragma once
#include <map>
#include <regex>
#include "Word.h"
#include "ILoader.h"

using namespace std;
using namespace lib;

namespace lib {

    /**
     * \brief A collection of Word objects loaded from a source (ie. text file).
     */
    class Dictionary
    {
        ILoader & _loader;
        IPrinter& _printer;
        const string HEADER_PATTERN = "^(\\S+) \\[(\\w+)\\]";
        const string DEFINITION_PATTERN = "^.*";
        const string END_OF_ENTRY_PATTERN = "^\\s*$";

    public:
        /**
         * \brief Constructs the Dictionary. Requires injection of ILoader and IPrinter.
         * \param loader the implementation of ILoader, responsible for loading dictionary entries from a source.
         * \param printer the implementation of IPrinter, responsible for printing the output of a Word.
         */
        Dictionary(ILoader& loader, IPrinter& printer);
        /**
         * \brief Load dictionary entries from a source. Not concerned with what the source is, it is abstracted away into ILoader.
         * \param location The location of the dictionary source. Can be a filepath, db connection string etc.
         * The requirement depends on ILoader implementation.
         * \returns The dictionary as map<string, Word> where the key is the actual word itself, and the value is the Word object.
         */
        map<string, Word> loadDictionary(const string& location) const;

    private:
        bool isEndOfEntry(string& line) const;
        string extractWord(string& line) const;
        string extractType(string& line) const;
        string extractDefinition(string& line) const;
        string extract(string pattern, string& line, int groupIndex) const;
        Word buildWord(string& word, string& type, string& definition) const;
    };
}

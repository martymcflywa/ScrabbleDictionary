#pragma once
#include <string>
#include "IPrinter.h"
#include "WordType.h"

using namespace std;
using namespace lib;

namespace lib
{
    class Word
    {
        string _word;
        Type _type;
        string _definition;
        IPrinter& _printer;

    public:
        /**
         * \brief Constructs a Word object with values extracted from a source dictionary.
         * \param word The word itself.
         * \param type The type of word, ie. adj, n, etc. Must not include brackets "[]".
         * \param definition The definition of the word.
         * \param printer Inject implementation of IPrinter so that Word is not coupled to implementation of printing.
         */
        Word(const string& word, const string& type, const string& definition, IPrinter& printer);
        /**
         * \brief Don't want anyone using this.
         */
        Word() = delete;
        string getWord() const;
        Type getType() const;
        string getDefinition() const;
        void printDefinition();
        /**
         * \brief Implementation of operator ==, really useful for unit tests.
         * \param that The other Word to compare to.
         * \returns true if both Words contain the same values.
         */
        bool operator == (const Word& that) const;

    private:
        static Type resolveType(const string& type);
        static string validate(const string& input);
    };
}

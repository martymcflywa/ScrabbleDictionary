#pragma once
#include <string>
#include "IPrint.h"
#include "WordType.h"

namespace lib
{
    class Word
    {
        std::string _word;
        Type _type;
        std::string _definition;
        IPrint& _printer;

    public:
        /**
         * \brief Constructs a Word object with values extracted from a source dictionary.
         * \param word The word itself.
         * \param type The type of word, ie. adj, n, etc. Must not include brackets "[]".
         * \param definition The definition of the word.
         * \param printer Inject implementation of IPrint so that Word is not coupled to implementation of printing.
         */
        Word(const std::string& word, const std::string& type, const std::string& definition, IPrint& printer);
        /**
         * \brief Don't want anyone using this.
         */
        Word() = delete;
        std::string getWord() const;
        Type getType() const;
        std::string getDefinition() const;
        std::string printDefinition() const;
        /**
         * \brief Implementation of operator ==, really useful for unit tests.
         * \param that The other Word to compare to.
         * \returns true if both Words contain the same values.
         */
        bool operator == (const Word& that) const;

    private:
        static Type resolveType(const std::string& type);
        static std::string validate(const std::string& input);
    };
}

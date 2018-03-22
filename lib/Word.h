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
        unsigned _scrabbleScore;
        unsigned _usage;
        IPrint& _printer;

    public:
        /**
         * \brief Constructs a Word object with values extracted from a source dictionary.
         * \param word The word itself.
         * \param type Type of the word, ie. Noun, Adjective etc.
         * \param definition The definition of the word.
         * \param printer Inject implementation of IPrint so that Word is not coupled to implementation of printing.
         */
        Word(const std::string& word, Type type, const std::string& definition, IPrint& printer);
        /**
         * \brief Don't want anyone using this.
         */
        Word() = delete;
        std::string getWord() const;
        Type getType() const;
        std::string getDefinition() const;
        int getScrabbleScore() const;
        std::string printDefinition() const;
        /**
         * \brief Returns true if word is not misc, proper noun or hyphenated.
         * \return True if word type is not misc, proper noun or hyphenated.
         */
        bool isLegalScrabbleWord() const;
        /**
         * \brief Increment the usage count of the word.
         */
        void incrementUsage();
        /**
         * \brief Returns true if usage < 2.
         * \returns True if usage < 2.
         */
        bool isRareWord() const;
        /**
         * \brief Implementation of operator ==, really useful for unit tests.
         * \param that The other Word to compare to.
         * \returns true if both Words contain the same values.
         */
        bool operator==(const Word& that) const;

    private:
        /**
        * \brief Calculates the score for the word. Misc, proper noun or hyphenated words always return 0;
        * \returns The score for the word if not misc, proper noun or hyphenated words, else returns 0.
        */
        int calculateScrabbleScore() const;
    };
}

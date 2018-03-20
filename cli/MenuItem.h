#pragma once
#include <string>

namespace cli
{
    /**
     * \brief Define the menu items in this struct once. If they change, can just edit this struct.
     */
    struct MenuItem
    {
        static const std::string SEARCH_DEFINITION_SCORE;
        static const std::string LONGEST_WORDS;
        static const std::string LOGY_WORDS;
        static const std::string RHYME_WORDS;
        static const std::string ANAGRAM_WORD;
        static const std::string ANAGRAM_STRING;
        static const std::string GLOSSARY;
        static const std::string QUIT;
        static const std::string BACK;
    };
}

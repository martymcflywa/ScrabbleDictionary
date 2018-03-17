#pragma once
#include <string>

namespace cli
{
    /**
     * \brief Define the menu items in this struct once. If they change, can just edit this struct.
     */
    struct MenuItem
    {
        static const std::string SEARCH_DEFINITION;
        static const std::string LONGEST_WORDS;
        static const std::string WORDS_END_WITH_LOGY;
        static const std::string RHYME_WORDS;
        static const std::string QUIT;
        static const std::string BACK;
    };
}

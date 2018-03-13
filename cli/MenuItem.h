#pragma once
#include <string>

using namespace std;

namespace cli
{
    /**
     * \brief Define the menu items in this struct once. If they change, can just edit this struct.
     */
    struct MenuItem
    {
        static const string SEARCH_DEFINITION;
        static const string LONGEST_WORD;
        static const string WORDS_END_WITH_LOGY;
        static const string QUIT;
        static const string BACK;
    };
}

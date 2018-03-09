#pragma once
#include "Word.h"

namespace lib
{
    /**
     * \brief Generates Word objects.
     */
    class WordFactory
    {
    public:
        static Word build(string& word, string& type, string& definition, IPrint& printer);
    };
}
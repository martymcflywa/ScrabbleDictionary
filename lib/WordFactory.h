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
        static Word build(const string& word, const string& type, const string& definition, IPrint& printer);
    };
}
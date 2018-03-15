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
        static Word build(
            const std::string& word,
            const std::string& type,
            const std::string& definition,
            IPrint& printer);
    };
}
#pragma once
#include "Word.h"
#include <memory>

namespace lib
{
    /**
     * \brief Generates Word objects.
     */
    class WordFactory
    {
    public:
        static std::shared_ptr<Word> build(
            const std::string& word,
            const std::string& type,
            const std::string& definition,
            IPrint& printer);
    };
}

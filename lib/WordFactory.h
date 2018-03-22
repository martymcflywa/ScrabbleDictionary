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
    private:
        /**
        * \brief Resolves a Word type from string to Type enum.
        * \param type The type as a string, extracted from the source dictionary.
        * \return The corresponding Type enum value.
        */
        static Type resolveType(const std::string& type);
    };
}

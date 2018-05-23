#pragma once
#include <vector>
#include "IExtract.h"

namespace lib
{
    /**
     * \brief Implementation of IExtract, specific to extracting words from a text file,
     * ignoring any special characters, punctuation etc. and converts words to lowercase.
     */
    class GlossaryExtractor : public IExtract<std::vector<std::string>, std::istream&>
    {
        /**
         * \brief The stuff to ignore.
         */
        const std::string SPECIAL_CHARS = " \t\r\n,.!?;:-_“”\"+=@#$%^&*()[]{}<>\\/|`~ï»¿";
    public:
        /**
         * \brief Extracts words from a text file, ignoring any special characters,
         * converting words to lowercase.
         * \param content The stream from the source text file.
         * \return A collection of lowercase words extracted from the text file.
         */
        std::vector<std::string> extract(std::istream& content) override;
    };
}

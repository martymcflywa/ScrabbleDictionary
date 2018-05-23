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
        const std::string SPECIAL_CHARS = " \t\r\n,.!?;:_’“”\"+=@#$%^&*()[]{}<>\\/|`~ï»¿â€œÂ";
    public:
        /**
         * \brief Extracts words from a text file, ignoring any special characters,
         * converting words to lowercase.
         * \param content The stream from the source text file.
         * \return A collection of lowercase words extracted from the text file.
         */
        std::vector<std::string> extract(std::istream& content) override;
    private:
        /**
         * \brief If found in the line, the 'pattern' will be replaced by 'replacement'.
         * \param line The line to search for the pattern.
         * \param pattern A regex pattern as a string. Must follow ECMAScript regex syntax.
         * TODO: Throw exception if incorrect syntax
         * \param replacement What to replace the pattern with in the line.
         * \return The line with the pattern replaced by the replacement.
         */
        std::string replace(const std::string& line, const std::string& pattern, const std::string& replacement) const;
        /**
         * \brief Splits a string into a vector of strings based on a delimiter.
         * \param line The line to split.
         * \param delimiter The delimiter to split on.
         * \return A vector of strings, without the delimiter.
         */
        static std::vector<std::string> split(std::string line, const std::string& delimiter);
        /**
         * \brief Splits each string in the input vector to a flattened output vector,
         * based on a delimiter.
         * \param tokens The vector of tokens to split.
         * \param delimiter The delimiter to split on.
         * \return A flattened vector of strings, without the delimiter.
         */
        static std::vector<std::string> split(std::vector<std::string> tokens, const std::string& delimiter);
        /**
         * \brief Erases the target from a collection of strings.
         * \param tokens The collection of strings to search and remove the target from.
         * \param target The target to delete.
         * \return The collection of strings with the target erased.
         */
        std::vector<std::string> erase(std::vector<std::string> tokens, const char& target) const;
    };
}

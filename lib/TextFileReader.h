#pragma once
#include <fstream>
#include <string>
#include "IRead.h"

namespace lib
{
    /**
    * \brief Implementation of IRead, which reads stuff from a text file.
    */
    class TextFileReader : public IRead
    {
        std::string _filepath;
        std::ifstream _file;

    public:
        /**
        * \brief Validates filepath during construction. If it fails validation, throw.
        * \param filepath The filepath to the text file.
        */
        TextFileReader(const std::string& filepath);
        std::istream& read() override;
        void dispose() override;
    private:
        /**
        * \brief Checks if file exists at filepath.
        * \param filepath The filepath to check.
        * \return true if file exists.
        */
        static bool isFileExists(const std::string& filepath);
    };
}
#pragma once
#include <fstream>
#include <string>
#include "ILoad.h"

namespace lib
{
    /**
    * \brief Implementation of ILoad, which expects the source dictionary to be provided as a text file.
    */
    class TextFileLoader : public ILoad
    {
        std::string _filepath;
        std::ifstream _file;

    public:
        /**
        * \brief Validates filepath during construction. If it fails validation, throw.
        * \param filepath The filepath to the source dictionary.
        */
        TextFileLoader(const std::string& filepath);
        std::istream& load() override;
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
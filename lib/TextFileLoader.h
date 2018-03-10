#pragma once
#include <string>
#include <fstream>
#include "ILoad.h"

using namespace std;
using namespace lib;

/**
 * \brief Implementation of ILoad, which expects the source dictionary to be provided as a text file.
 */
class TextFileLoader : public ILoad
{
    string _filepath;
    ifstream _file;

public:
    /**
     * \brief Validates filepath during construction. If it fails validation, throw.
     * \param filepath The filepath to the source dictionary.
     */
    TextFileLoader(string& filepath);
    istream& load() override;
    void dispose() override;
private:
    /**
     * \brief Checks if file exists at filepath.
     * \param filepath The filepath to check.
     * \return true if file exists.
     */
    static bool isFileExists(string& filepath);
};
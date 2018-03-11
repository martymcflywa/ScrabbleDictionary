#include "stdafx.h"
#include "TextFileLoader.h"
#include "FileNotFoundException.h"

/**
* \brief Validates filepath during construction. If it fails validation, throw.
* \param filepath The filepath to the source dictionary.
*/
TextFileLoader::TextFileLoader(string& filepath) : _filepath(filepath)
{
    if(!isFileExists(_filepath))
        throw FileNotFoundException(_filepath);
}

istream& TextFileLoader::load()
{
    _file.open(_filepath);

    if(!_file)
        throw invalid_argument("Error reading file at " + _filepath);

    return _file;
}

void TextFileLoader::dispose()
{
    _file.close();
}

bool TextFileLoader::isFileExists(string& filepath)
{
    // found solution here https://stackoverflow.com/a/12774387
    auto file = ifstream(filepath.c_str());
    file.close();
    return file.good();
}
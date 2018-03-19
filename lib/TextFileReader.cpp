#include "stdafx.h"
#include "FileNotFoundException.h"
#include "FileIoException.h"
#include "TextFileReader.h"

using namespace std;
using namespace lib;

/**
* \brief Validates filepath during construction. If it fails validation, throw.
* \param filepath The filepath to the text file.
*/
TextFileReader::TextFileReader(const string& filepath) : _filepath(filepath)
{
    if(!isFileExists(_filepath))
        throw FileNotFoundException(_filepath);
}

istream& TextFileReader::read()
{
    _file.open(_filepath);

    if(!_file)
        throw FileIoException("reading", _filepath);

    return _file;
}

void TextFileReader::dispose()
{
    _file.close();
}

/**
* \brief Checks if file exists at filepath.
* \param filepath The filepath to check.
* \return true if file exists.
*/
bool TextFileReader::isFileExists(const string& filepath)
{
    // found solution here https://stackoverflow.com/a/12774387
    auto file = ifstream(filepath.c_str());
    file.close();
    return file.good();
}
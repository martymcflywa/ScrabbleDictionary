#include "stdafx.h"
#include "TextFileWriter.h"
#include <fstream>
#include "FileIoException.h"

using namespace std;
using namespace lib;

TextFileWriter::TextFileWriter(const std::string& filepath) : _filepath(filepath)
{
}

void TextFileWriter::write(const std::string& content)
{
    auto file = ofstream(_filepath);

    if (!file.is_open())
        throw FileIoException("writing", _filepath);

    file << content;
    file.close();
}

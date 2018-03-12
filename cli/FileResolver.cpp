#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "../lib/FileNotFoundException.h"
#include "FileResolver.h"
#include "Logger.h"

using namespace lib;
using namespace cli;

string FileResolver::getFilepath()
{
    Logger::log(Input, "Enter filepath to source dictionary.");
    string filepath;

    getline(cin, filepath, '\n');
    return validate(filepath);
}

string FileResolver::validate(string& filepath)
{
    auto file = ifstream(filepath.c_str());
    file.close();

    if (!file.good())
        throw FileNotFoundException(filepath);

    return filepath;
}

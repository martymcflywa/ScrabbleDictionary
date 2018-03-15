#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "FileResolver.h"
#include "Logger.h"
#include "../lib/FileNotFoundException.h"

using namespace std;

string cli::FileResolver::getFilepath()
{
    Logger::log(Input, "Enter filepath to source dictionary.");
    string filepath;

    getline(cin, filepath, '\n');
    return validate(filepath);
}

string cli::FileResolver::validate(string& filepath)
{
    auto file = ifstream(filepath.c_str());
    file.close();

    if (!file.good())
        throw lib::FileNotFoundException(filepath);

    return filepath;
}

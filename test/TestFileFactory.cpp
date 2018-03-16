﻿#include "stdafx.h"
#include <fstream>
#include "TestFileFactory.h"

using namespace std;

TestFileFactory::TestFileFactory(const string& filepath, const string& content) : 
    _filepath(filepath), 
    _content(content)
{
    write();
}

void TestFileFactory::write() const
{
    auto file = ofstream(_filepath);

    if(!file.is_open())
        throw invalid_argument("Unable to write to file at " + _filepath);

    file << _content;
    file.close();
}

void TestFileFactory::cleanup() const
{
    if(remove(_filepath.c_str()) != 0)
        throw invalid_argument("Unable to delete file at " + _filepath);
}

#include "stdafx.h"
#include "TestLoader.h"

void TestLoader::setTestFile(const string testFile)
{
    _testDictionary.str(testFile);
}

istream& TestLoader::load(string filepath)
{
    istream& is(_testDictionary);
    return is;
}

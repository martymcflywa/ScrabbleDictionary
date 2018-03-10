#include "stdafx.h"
#include "TestLoader.h"

void TestLoader::setTestFile(string& testFile)
{
    _testDictionary.str(testFile);
}

istream& TestLoader::load()
{
    istream& is(_testDictionary);
    return is;
}

void TestLoader::dispose()
{
    // do nothing, no file or resource to close here
}

#include "stdafx.h"
#include "TestReader.h"

using namespace std;

void TestReader::setTestFile(const string& testFile)
{
    _testDictionary.str(testFile);
}

istream& TestReader::read()
{
    istream& is(_testDictionary);
    return is;
}

void TestReader::dispose()
{
    // do nothing, no file or resource to close here
}

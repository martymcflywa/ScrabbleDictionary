#include "stdafx.h"
#include "TestWriter.h"

using namespace std;

void TestWriter::write(const std::string& content)
{
    _content = content;
}

std::string TestWriter::getFilepath()
{
    return string("pretendToWrite.txt");
}

std::string& TestWriter::getContent()
{
    return _content;
}

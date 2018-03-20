#include "stdafx.h"
#include "TestWriter.h"

void TestWriter::write(const std::string& content)
{
    _content = content;
}

std::string& TestWriter::getContent()
{
    return _content;
}

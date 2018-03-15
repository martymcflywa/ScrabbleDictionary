#include "stdafx.h"
#include "FileReadException.h"

using namespace std;
using namespace lib;

FileReadException::FileReadException(const string& filepath) :
    logicError("Error reading file: " + filepath)
{
}

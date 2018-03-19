#include "stdafx.h"
#include "FileIoException.h"

using namespace std;
using namespace lib;

FileIoException::FileIoException(const string& operation, const string& filepath) :
    logicError("Error " + operation + " file: " + filepath)
{
}

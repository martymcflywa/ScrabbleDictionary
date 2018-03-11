#include "stdafx.h"
#include "FileReadException.h"

lib::FileReadException::FileReadException(const string& filepath) :
    logicError("Error reading file: " + filepath)
{
}

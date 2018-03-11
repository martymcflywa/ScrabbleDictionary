#include "stdafx.h"
#include "EmptyStringException.h"

lib::EmptyStringException::EmptyStringException() :
    logicError("Word, type or definition is empty")
{
}

lib::EmptyStringException::EmptyStringException(const string& arg) :
    logicError(arg + " is empty")
{
}

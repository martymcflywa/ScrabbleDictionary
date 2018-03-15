#include "stdafx.h"
#include "EmptyStringException.h"

using namespace std;
using namespace lib;

EmptyStringException::EmptyStringException() :
    logicError("Word, type or definition is empty")
{
}

EmptyStringException::EmptyStringException(const string& arg) :
    logicError(arg + " is empty")
{
}

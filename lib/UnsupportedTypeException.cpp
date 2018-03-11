#include "stdafx.h"
#include "UnsupportedTypeException.h"

lib::UnsupportedTypeException::UnsupportedTypeException(const string& type) :
    logicError("Type " + type + " unsupported")
{
}

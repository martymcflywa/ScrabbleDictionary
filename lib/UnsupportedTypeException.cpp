#include "stdafx.h"
#include "UnsupportedTypeException.h"

using namespace std;
using namespace lib;

UnsupportedTypeException::UnsupportedTypeException(const string& type) :
    logicError("Type " + type + " unsupported")
{
}

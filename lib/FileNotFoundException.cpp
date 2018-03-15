#include "stdafx.h"
#include "FileNotFoundException.h"

using namespace std;
using namespace lib;

/**
* \brief Throw this when file isn't found.
*/
FileNotFoundException::FileNotFoundException(const string& filepath) : 
    logicError("File not found: " + filepath)
{
}
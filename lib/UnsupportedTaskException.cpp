#include "stdafx.h"
#include "UnsupportedTaskException.h"

using namespace std;
using namespace lib;

UnsupportedTaskException::UnsupportedTaskException(const std::string& taskType) :
    logic_error("Task " + taskType + " unsupported")
{
}

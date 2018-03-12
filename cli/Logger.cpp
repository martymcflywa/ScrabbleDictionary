#include "stdafx.h"
#include <iostream>
#include "Logger.h"

using namespace cli;

void Logger::log(Prefix response, char const* message)
{
    auto m = string(message);
    log(response, m);
}

void Logger::log(Prefix response, string& message)
{
    const auto prefix = resolvePrefix(response);
    cout << prefix + message << endl;
}

string Logger::resolvePrefix(Prefix response)
{
    switch (response)
    {
    case Input:
        return "[INPUT] ";
    case Output:
        return "[OUTPUT] ";
    case Info:
        return "[INFO] ";
    case Error:
        return "[ERROR] ";
    default:
        return "";
    }
}

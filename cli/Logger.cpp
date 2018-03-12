#include "stdafx.h"
#include <iostream>
#include "Logger.h"

using namespace cli;

void Logger::log(Prefix response, char const* message)
{
    const auto m = string(message);
    log(response, m);
}

void Logger::log(Prefix response, const string& message)
{
    const auto prefix = resolvePrefix(response);
    cout << prefix + message << endl;
}

void Logger::log(const string& message)
{
    cout << message << endl;
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

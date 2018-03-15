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

/**
* \brief Print '>' cli prompt when user input required.
*/
void Logger::printPrompt()
{
    cout << "> ";
}

string Logger::resolvePrefix(Prefix response)
{
    switch (response)
    {
    case Error:
        return "[ERROR] ";
    case Info:
        return "[INFO] ";
    case Input:
        return "[INPUT] ";
    case Menu:
        return "[MENU] ";
    case Output:
        return "[OUTPUT] ";
    default:
        return "";
    }
}

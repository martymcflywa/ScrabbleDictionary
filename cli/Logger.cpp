#include "stdafx.h"
#include <iostream>
#include <string>
#include "Logger.h"

using namespace std;
using namespace cli;

void Logger::log(Prefix response, char const* message)
{
    const auto m = string(message);
    log(response, m);
}

void Logger::log(Prefix response, const string& message)
{
    const auto prefix = resolvePrefix(response);

    if (response == Task)
    {
        cout << endl << prefix + message << endl;
        return;
    }
        
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
    case Task: 
        return "[TASK] ";
    default:
        return "";
    }
}

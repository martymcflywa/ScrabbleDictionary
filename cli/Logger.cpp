#include "stdafx.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "Logger.h"

using namespace std;
using namespace std::chrono;
using namespace cli;

void Logger::log(Prefix response, char const* message)
{
    const auto m = string(message);
    log(response, m);
}

void Logger::log(Prefix response, const std::string& message, const duration<double>& duration)
{
    auto timer = ostringstream();
    timer << fixed;
    timer << setprecision(2);
    timer << duration.count();

    const auto instrumentedMessage = message + ", took " + timer.str() + " seconds";

    log(response, instrumentedMessage);
}

void Logger::log(Prefix response, const string& message)
{
    const auto prefix = resolvePrefix(response);

    if (response == Task)
    {
        cout << '\n' << prefix + message << '\n';
        printPrompt();
        return;
    }
        
    cout << prefix + message << '\n';
}

void Logger::log(const string& message)
{
    cout << message << '\n';
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

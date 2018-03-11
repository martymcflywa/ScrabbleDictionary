#include "stdafx.h"
#include <iostream>
#include "Printer.h"

void cli::Printer::print(Prefix response, char const* message)
{
    auto m = string(message);
    print(response, m);
}

void cli::Printer::print(Prefix response, string& message)
{
    const auto prefix = resolvePrefix(response);
    cout << prefix + message << endl;
}

string cli::Printer::resolvePrefix(Prefix response)
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

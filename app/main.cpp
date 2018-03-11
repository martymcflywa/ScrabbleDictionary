// app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../lib/FileNotFoundException.h"
#include "../cli/FileResolver.h"

using namespace lib;
using namespace cli;

int main()
{
    try
    {
        FileResolver::getFilepath();
    }
    catch (FileNotFoundException& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
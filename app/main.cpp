// app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"
#include "../cli/Logger.h"
#include "../lib/EmptyStringException.h"
#include "../lib/FileNotFoundException.h"
#include "../lib/FileIoException.h"
#include "../lib/UnsupportedTaskException.h"
#include "../lib/UnsupportedTypeException.h"

using namespace app;
using namespace cli;
using namespace lib;

int main()
{
    try
    {
        auto application = Application();
        application.init();
        application.run();
    }
    catch (FileNotFoundException& e)
    {
        Logger::log(Error, e.what());
        exit(1);
    }
    catch (FileIoException& e)
    {
        Logger::log(Error, e.what());
        exit(1);
    }
    catch (UnsupportedTypeException& e)
    {
        Logger::log(Error, e.what());
        exit(1);
    }
    catch (EmptyStringException& e)
    {
        Logger::log(Error, e.what());
        exit(1);
    }
    catch (UnsupportedTaskException& e)
    {
        Logger::log(Error, e.what());
        exit(1);
    }

    return 0;
}
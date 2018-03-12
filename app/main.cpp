// app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../cli/FileResolver.h"
#include "../cli/Logger.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/EmptyStringException.h"
#include "../lib/FileNotFoundException.h"
#include "../lib/FileReadException.h"
#include "../lib/StringExtractor.h"
#include "../lib/TextFileLoader.h"
#include "../lib/UnsupportedTypeException.h"

using namespace lib;
using namespace cli;

int main()
{
    try
    {
        // set up all the things, inject where necessary
        const auto filepath = FileResolver::getFilepath(); // fail fast here if we can't find the file
        auto loader = TextFileLoader(filepath);
        auto formatter = DefinitionFormatter();
        auto printer = DefinitionPrinter(formatter);
        auto extractor = StringExtractor(printer);
        // set up dictionary then load
        auto dictionary = Dictionary(loader, extractor);
        dictionary.loadDictionary();

        // show user main menu

    }
    catch (FileNotFoundException& e)
    {
        Logger::log(Error, e.what());
        exit(1);
    }
    catch (FileReadException& e)
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

    return 0;
}
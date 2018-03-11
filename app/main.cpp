// app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../cli/FileResolver.h"
#include "../cli/Printer.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/EmptyStringException.h"
#include "../lib/FileNotFoundException.h"
#include "../lib/FileReadException.h"
#include "../lib/TextFileExtractor.h"
#include "../lib/TextFileLoader.h"
#include "../lib/UnsupportedTypeException.h"

using namespace lib;
using namespace cli;

Dictionary buildDictionary(string& filepath)
{
    // TODO: these need to be const
    // else when out of scope, objects are dereferenced
    auto loader = TextFileLoader(filepath);
    auto formatter = DefinitionFormatter();
    auto printer = DefinitionPrinter(formatter);
    auto extractor = TextFileExtractor(printer);

    return Dictionary(loader, extractor);
}

int main()
{
    try
    {
        auto filepath = FileResolver::getFilepath();
        auto loader = TextFileLoader(filepath);
        auto formatter = DefinitionFormatter();
        auto printer = DefinitionPrinter(formatter);
        auto extractor = TextFileExtractor(printer);

        auto dictionary = Dictionary(loader, extractor);
        dictionary.loadDictionary();
    }
    catch (FileNotFoundException& e)
    {
        Printer::print(Error, e.what());
        exit(1);
    }
    catch (FileReadException& e)
    {
        Printer::print(Error, e.what());
        exit(1);
    }
    catch (UnsupportedTypeException& e)
    {
        Printer::print(Error, e.what());
        exit(1);
    }
    catch (EmptyStringException& e)
    {
        Printer::print(Error, e.what());
        exit(1);
    }

    return 0;
}
// app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../lib/FileNotFoundException.h"
#include "../cli/FileResolver.h"
#include "../cli/Printer.h"
#include "../lib/Dictionary.h"
#include "../lib/TextFileLoader.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/TextFileExtractor.h"

using namespace lib;
using namespace cli;

Dictionary buildDictionary(string& filepath)
{
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
        auto dictionary = buildDictionary(filepath);
    }
    catch (FileNotFoundException& e)
    {
        Printer::print(Error, e.what());
    }
    return 0;
}
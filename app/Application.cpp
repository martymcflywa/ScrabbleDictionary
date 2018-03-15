#include "stdafx.h"
#include "Application.h"
#include "../cli/CliUserInterface.h"
#include "../cli/FileResolver.h"
#include "../cli/Logger.h"
#include "../cli/MenuItem.h"

using namespace app;
using namespace cli;

/**
* \brief Instantiate all the interface implementations, inject dependencies where needed, 
* construct the Dictionary, then user interface.
*/
Application::Application() :
    // Switched to hardcoded path, replaces FileResolver::getFilepath()
    _filepath(string(".\\dictionary2018.txt")),
    _loader(TextFileLoader(_filepath)),
    _formatter(DefinitionFormatter()),
    _printer(DefinitionPrinter(_formatter)),
    _task(DictionaryTask()),
    _extractor(StringExtractor(_printer, _task)),
    _dictionary(Dictionary(_loader, _extractor)),
    _ui(CliUserInterface(_dictionary))
{
}

/**
* \brief Load the dictionary.
*/
void Application::init()
{
    Logger::log(Info, "Loading dictionary...");
    _dictionary.loadDictionary();
    const auto message = "Loaded dictionary with " + to_string(_dictionary.size()) + " entries";
    Logger::log(Info, message);
}


/**
 * \brief Start at main menu.
 */
void Application::run()
{
    _ui.mainMenu();
}

#include "stdafx.h"
#include "Application.h"
#include "../cli/CliUserInterface.h"
#include "../cli/Logger.h"

using namespace std;
using namespace app;
using namespace cli;
using namespace lib;

/**
* \brief Instantiate all the interface implementations, inject dependencies where needed, 
* construct the Dictionary, then user interface.
*/
Application::Application() :
    // Switched to hardcoded path, replaces FileResolver::getFilepath()
    _dictionaryFilepath(string(".\\dictionary2018.txt")),
    _dictionaryReader(TextFileReader(_dictionaryFilepath)),
    _dictionaryFormatter(DefinitionFormatter()),
    _dictionaryPrinter(DefinitionPrinter(_dictionaryFormatter)),
    _dictionaryTask(DictionaryTask()),
    _dictionaryExtractor(DictionaryExtractor(_dictionaryPrinter, _dictionaryTask)),
    _dictionary(Dictionary(_dictionaryExtractor, _dictionaryTask)),
    _ui(CliUserInterface(_dictionary))
{
}

/**
* \brief Load the dictionary.
*/
void Application::init()
{
    Logger::log(Info, "Loading dictionary...");
    _dictionary.loadDictionary(_dictionaryReader);
    const auto message = "Loaded dictionary with " + to_string(_dictionary.size()) + " entries";
    Logger::log(Info, message);
}


/**
 * \brief Starts at main menu.
 */
void Application::run()
{
    _ui.start();
}

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
* construct the Dictionary and Glossary, then UI.
*/
Application::Application() :
    // build the dictionary
    _dictionaryFilepath(string(".\\dictionary2018.txt")),
    _dictionaryReader(TextFileReader(_dictionaryFilepath)),
    _dictionaryFormatter(DefinitionFormatter()),
    _dictionaryPrinter(DefinitionPrinter(_dictionaryFormatter)),
    _dictionaryTask(DictionaryTask()),
    _dictionaryExtractor(DictionaryExtractor(_dictionaryPrinter, _dictionaryTask)),
    _dictionary(Dictionary(_dictionaryExtractor, _dictionaryTask)),
    // build the glossary
    _usageFilepath(string(".\\many_english_works.txt")),
    _rareWordFilepath(string(".\\new_work.txt")),
    _glossaryFormatter(GlossaryFormatter()),
    _glossaryExtractor(GlossaryExtractor()),
    _glossaryWriter(string(".\\glossary.txt")),
    _glossary(Glossary(_dictionary, _glossaryExtractor, _glossaryFormatter, _glossaryWriter)),
    // build the ui
    _ui(CliUserInterface(_dictionary, _usageFilepath, _rareWordFilepath, _glossary))
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

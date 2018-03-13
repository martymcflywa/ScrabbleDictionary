#include "stdafx.h"
#include "Application.h"
#include "../cli/FileResolver.h"
#include "../cli/Logger.h"
#include "../cli/Menu.h"
#include "../cli/MenuItem.h"

using namespace cli;
using namespace app;

/**
* \brief Instantiate all the interface implementations, inject dependencies where needed, then construct the Dictionary.
*/
Application::Application() :
    _filepath(string(".\\dictionary2018.txt")), // Switched to hardcoded path, replaces FileResolver::getFilepath()
    _loader(TextFileLoader(_filepath)),
    _formatter(DefinitionFormatter()),
    _printer(DefinitionPrinter(_formatter)),
    _task(DictionaryTask()),
    _extractor(StringExtractor(_printer, _task)),
    _dictionary(Dictionary(_loader, _extractor))
{
}

/**
* \brief Loads the dictionary.
*/
void Application::init()
{
    Logger::log(Info, "Loading dictionary...");
    _dictionary.loadDictionary();
    const auto message = "Loaded dictionary with " + to_string(_dictionary.size()) + " entries";
    Logger::log(Info, message);
}

/**
* \brief Runs the app. Ask user to select from menu, then perform selected task.
*/
void Application::run()
{
    const auto selection = Menu::select();

    if (selection == MenuItem::SEARCH_DEFINITION)
    {
        searchDefinition();
        return;
    }
    if (selection == MenuItem::LONGEST_WORD)
    {
        longestWord();
        return;
    }
    if (selection == MenuItem::WORDS_END_WITH_LOGY)
    {
        wordsEndWithLogy();
        return;
    }
    if (selection == MenuItem::QUIT)
    {
        Logger::log(Info, "Shutting down, goodbye");
        exit(0);
    }
    // tried throwing here but couldn't call back to run() for retry, stack unwinds on throw,
    // see http://www.acodersjourney.com/2016/08/top-15-c-exception-handling-mistakes-avoid/
    Logger::log(Error, selection + " is not a valid selection, try again");
    run();
}

void Application::searchDefinition()
{
    throw invalid_argument("not implemented");
}

void Application::longestWord()
{
    throw invalid_argument("not implemented");
}

void Application::wordsEndWithLogy()
{
    throw invalid_argument("not implemented");
}

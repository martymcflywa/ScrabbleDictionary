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
* \brief Show the main menu. Ask user to select from menu, then perform selected task.
*/
void Application::mainMenu()
{
    const auto selection = Menu::select();

    if (selection == MenuItem::SEARCH_DEFINITION)
    {
        findDefinition();
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
    // tried throwing here but couldn't call back to mainMenu() for retry, stack unwinds on throw,
    // see http://www.acodersjourney.com/2016/08/top-15-c-exception-handling-mistakes-avoid/
    Logger::log(Error, selection + " is not a valid selection, try again");
    mainMenu();
}

void Application::findDefinition()
{
    const auto word = Menu::findDefinition();
    
    // give user option to go back to main menu
    if (word == MenuItem::BACK)
        mainMenu();

    Logger::log(Output, "Definition for " + word + ":");
    Logger::log(_dictionary.getDefinition(word));

    // recurse to search for another word
    findDefinition();
}

void Application::longestWord()
{
    Logger::log(Output, "The longest word/s found in the dictionary:");
    
    auto longest = _dictionary.getLongestWord();
    for (auto const& word : longest)
        Logger::log(word + " (" + to_string(word.length()) + ")");

    // head back to main menu
    mainMenu();
}

void Application::wordsEndWithLogy()
{
    Logger::log(Output, "Words that end in 'logy' and have a length of seven or less characters:");

    auto logyWords = _dictionary.getLogyWords();
    for (auto const& word : logyWords)
        Logger::log(word + " (" + to_string(word.length()) + ")");

    // head back to main menu
    mainMenu();
}

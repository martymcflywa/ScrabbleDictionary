#include "stdafx.h"
#include "Application.h"
#include "../cli/FileResolver.h"
#include "../cli/Logger.h"
#include "../cli/Menu.h"
#include "../cli/MenuItem.h"

using namespace cli;
using namespace app;

/**
* \brief Instantiate all the interface implementations, inject dependencies where needed, 
* then construct the Dictionary.
*/
Application::Application() :
    // Switched to hardcoded path, replaces FileResolver::getFilepath()
    _filepath(string(".\\dictionary2018.txt")),
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
* If input is invalid, menu is shown again.
* Retry until user picks correct input or rage quits with CTRL+C.
*/
void Application::mainMenu()
{
    string selection;

    // handy input validation from module 5 loop workshop
    do
    {
        selection = Menu::select();
    } 
    while (!isValidMenuItem(selection));

    // bust out of the loop when user picks valid input and do stuff
    if (selection == MenuItem::SEARCH_DEFINITION)
    {
        findDefinition();
        return;
    }
    if (selection == MenuItem::LONGEST_WORDS)
    {
        longestWords();
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
}

/**
* \brief Returns true if user input at main menu matches any MenuItem.
* \param selection The input from the user at main menu.
* \returns true if input matches any MenuItem.
*/
bool Application::isValidMenuItem(const string& selection)
{
    const auto isValid = selection == MenuItem::SEARCH_DEFINITION
        || selection == MenuItem::LONGEST_WORDS
        || selection == MenuItem::WORDS_END_WITH_LOGY
        || selection == MenuItem::QUIT;

    if(!isValid)
        Logger::log(Error, selection + " is not a valid selection, try again");

    return isValid;
}

/**
* \brief Asks user to input a word. Dictionary will attempt to find it.
* If found, will print definition, else will notify user word is not found.
* Repeat until user chooses to go back to main menu.
*/
void Application::findDefinition()
{
    string word;

    // replaced recursive call with do-while, resolves C4717 compile warning:
    // recursive on all control paths, function will cause runtime stack overflow
    do
    {
        word = Menu::findDefinition();
        Logger::log(Output, "Definition for " + word + ":");
        Logger::log(_dictionary.getDefinition(word));
    }
    while (word != MenuItem::BACK);

    // bump back to main menu when we get the BACK command
    mainMenu();
}

/**
* \brief Will print longest word/s found in dictionary.
* Then jumps back to main menu.
*/
void Application::longestWords()
{
    Logger::log(Output, "The longest word/s found in the dictionary:");
    
    auto longest = _dictionary.getLongestWords();
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

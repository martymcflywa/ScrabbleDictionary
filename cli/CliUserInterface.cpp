#include "stdafx.h"
#include <iostream>
#include "CliUserInterface.h"
#include "Logger.h"
#include "MenuItem.h"

using namespace std;
using namespace cli;
using namespace lib;

/**
* \brief Constructor for CliUserInterface. Dictionary used to retrieve
* values to show the user.
* \param dictionary The dictionary, once populated with Words.
*/
CliUserInterface::CliUserInterface(Dictionary& dictionary) : _dictionary(dictionary)
{
    _menu = 
        string("[" + MenuItem::SEARCH_DEFINITION + "] Search for a word's definition\n") +
        string("[" + MenuItem::LONGEST_WORDS + "] Find the longest word/s in the dictionary\n") +
        string("[" + MenuItem::WORDS_END_WITH_LOGY + "] Find words that end in 'logy' and have a length of seven or less characters\n") +
        string("[" + MenuItem::QUIT + "] Quit");
}

/**
* \brief Show user the main menu. Ask user to select item from menu,
* then perform task. If input is invalid, retry until user picks corrrect option,
* or rage quits with CTRL+C.
* \return The selection made by the user.
*/
void CliUserInterface::mainMenu()
{
    // handy input validation from module 5 loops
    string selection;
    do
    {
        Logger::log(Info, "Main menu:");
        Logger::log(Menu, "Select an item by pressing the [key], then [enter]");
        Logger::log(_menu);
        Logger::printPrompt();
        getline(cin, selection);
    } 
    while (!isValidMenuSelection(selection));

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
* \brief Ask user to enter a word to search the dictionary with.
* If word is found, print the definition, else notify user word is not found.
* Repeat until user chooses to go back to main menu.
*/
void CliUserInterface::findDefinition()
{   
    string word;
    do
    {
        Logger::log(Info, "Find definition:");
        Logger::log(Input, "Enter word to find definition, or [" + MenuItem::BACK + "] to go back");
        Logger::printPrompt();
        getline(cin, word);

        // don't print definition for back 'button'
        if (word != MenuItem::BACK)
        {
            Logger::log(Output, "Definition for '" + word + "':");
            Logger::log(_dictionary.getDefinition(word));
        }
    }
    while (word != MenuItem::BACK);

    mainMenu();
}

/**
* \brief Show user the longest word/s in the dictionary.
* Then go back to main menu.
*/
void CliUserInterface::longestWords()
{
    auto longest = _dictionary.getLongestWords();
    Logger::log(Output, "Found " + to_string(longest.size()) + 
        " longest word/s in the dictionary:");

    for (const auto& word : longest)
        Logger::log(word + " (" + to_string(word.length()) + ")");

    // head back to main menu when task complete
    mainMenu();
}

/**
* \brief Show user words that end in 'logy' that have a length of seven or less chars.
* Then go back to main menu.
*/
void CliUserInterface::wordsEndWithLogy()
{
    auto logyWords = _dictionary.getLogyWords();
    Logger::log(Output, "Found " + to_string(logyWords.size()) + 
        " words that end in 'logy' and have a length of seven or less characters:");

    for (const auto& word : logyWords)
        Logger::log(word + " (" + to_string(word.length()) + ")");

    // head back to main menu when task complete
    mainMenu();
}

/**
* \brief Returns true if user selection at main menu matches any MenuItem.
* \param selection The selection made by the user at main menu.
* \returns true if input matches any MenuItem.
*/
bool CliUserInterface::isValidMenuSelection(const string& selection) const
{
    const auto isValid = selection == MenuItem::SEARCH_DEFINITION
        || selection == MenuItem::LONGEST_WORDS
        || selection == MenuItem::WORDS_END_WITH_LOGY
        || selection == MenuItem::QUIT;

    if (!isValid)
        Logger::log(Error, "'" + selection + "' is not a valid selection, try again");

    return isValid;
}

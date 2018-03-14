#include "stdafx.h"
#include <iostream>
#include "Logger.h"
#include "Menu.h"
#include "MenuItem.h"

using namespace cli;

string Menu::select()
{
    Logger::log(Info, "Main menu:");
    Logger::log(Input, "Select an item by pressing the [key], then [enter]");

    const auto menu =
        string("[" + MenuItem::SEARCH_DEFINITION + "] Search for a word's definition\n") +
        string("[" + MenuItem::LONGEST_WORDS + "] Find the longest word/s in the dictionary\n") +
        string("[" + MenuItem::WORDS_END_WITH_LOGY + "] Find words that end in 'logy' and have a length of seven or less characters\n") +
        string("["+ MenuItem::QUIT + "] Quit");

    Logger::log(menu);
    string selection;

    getline(cin, selection);
    return selection;
}

string Menu::findDefinition()
{
    Logger::log(Info, "Find definition:");
    Logger::log(Input, "Enter word to find definition, or [" + MenuItem::BACK + "] to go back");
    string word;
    
    getline(cin, word);
    return word;
}

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
        string("[" + MenuItem::SEARCH_DEFINITION + "] Find a word definition\n") +
        string("[" + MenuItem::LONGEST_WORDS + "] Find longest word/s in the dictionary\n") +
        string("[" + MenuItem::WORDS_END_WITH_LOGY + "] Find word/s that end in 'logy' and have a length of seven or less characters\n") +
        string("[" + MenuItem::RHYME_WORDS + "] Find word/s that rhyme\n") +
        string("[" + MenuItem::QUIT + "] Quit");
}

/**
* \brief Show user the main menu. Ask user to select item from menu,
* then perform task. If input is invalid, retry until user picks corrrect option,
* or rage quits with CTRL+C.
* \return The selection made by the user.
*/
void CliUserInterface::start()
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
    if (selection == MenuItem::RHYME_WORDS)
    {
        rhymeWords();
        return;
    }
    if (selection == MenuItem::QUIT)
    {
        shutdown();
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
        Logger::log(Info, "Find a word definition:");
        Logger::log(Input, "Enter word to find definition, [" + MenuItem::BACK + "] to go back, or [" + MenuItem::QUIT + "] to quit");
        Logger::printPrompt();
        getline(cin, word);

        // don't print definition for control chars
        if (isControlChar(word))
            continue;
        
        Logger::log(Output, "Definition for '" + word + "':");
        Logger::log(_dictionary.getDefinition(word));
    }
    while (!isControlChar(word));

    if (word == MenuItem::BACK)
        start();
    if (word == MenuItem::QUIT)
        shutdown();
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

    for (const auto& ptr : longest)
    {
        const auto word = ptr->getWord();
        Logger::log(word + " (" + to_string(word.length()) + ")");
    }

    // head back to main menu when task complete
    start();
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

    for (const auto& ptr : logyWords)
    {
        const auto word = ptr->getWord();
        Logger::log(word + " (" + to_string(word.length()) + ")");
    }

    // head back to main menu when task complete
    start();
}

/**
* \brief Find words that rhyme with another (last 3 letters are the same).
*/
void CliUserInterface::rhymeWords()
{
    string word;
    do
    {
        Logger::log(Info, "Find word/s that rhyme:");
        Logger::log(Input, "Enter word at least 3 letters long to find words that rhyme, [" + 
                MenuItem::BACK + "] to go back, or [" + MenuItem::QUIT + "] to quit");

        Logger::printPrompt();
        getline(cin, word);

        // don't print rhymes for control chars
        if (isControlChar(word))
            continue;
        // validate input
        if (!isValidRhymeWord(word))
            continue;

        auto rhymes = _dictionary.getRhymes(word);

        // if we found nothing, or only found same word
        if (rhymes.size() == 0 || (rhymes.size() == 1 && rhymes.begin()->get()->getWord() == word))
        {
            Logger::log(Output, "No rhymes found for '" + word + "'");
            continue;
        }

        Logger::log(Output, "Found " + to_string(rhymes.size()) + " word/s that rhyme with '" + word + "':");

        for (auto& it : rhymes)
        {
            if (it->getWord() != word)
                Logger::log(it->getWord());
        }

    }
    while (!isControlChar(word));

    if (word == MenuItem::BACK)
        start();
    if (word == MenuItem::QUIT)
        shutdown();
}

/**
* \brief Shutdown console app gracefully.
*/
void CliUserInterface::shutdown() const
{
    Logger::log(Info, "Shutting down, goodbye");
    exit(0);
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
        || selection == MenuItem::RHYME_WORDS
        || selection == MenuItem::QUIT;

    if (!isValid)
        Logger::log(Error, "'" + selection + "' is not a valid selection, try again");

    return isValid;
}

/**
* \brief Returns true if word length is at least MIN_RHYME_LENGTH.
* \param word The word to search for rhymes.
* \return True if word length is at least MIN_RHYME_LENGTH.
*/
bool CliUserInterface::isValidRhymeWord(const std::string& word) const
{
    const auto isValid = word.length() >= MIN_RHYME_LENGTH;

    if (!isValid)
        Logger::log(Error, "'" + word + "' must be at least " + to_string(MIN_RHYME_LENGTH) + " letters long, try again");

    return isValid;
}

/**
* \brief Returns true of the word is a control char.
* \param word The word to check if a control char.
* \returns True if the word is a control char.
*/
bool CliUserInterface::isControlChar(const std::string& word)
{
    return word == MenuItem::BACK || word == MenuItem::QUIT;
}

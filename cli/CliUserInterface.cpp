#include "stdafx.h"
#include <iostream>
#include "CliUserInterface.h"
#include "Logger.h"
#include "../lib/TextFileReader.h"

using namespace std;
using namespace cli;
using namespace lib;

/**
* \brief Constructor for CliUserInterface. Dictionary used to retrieve
* values to show the user. Glossary used to generate glossary of rare words.
* \param dictionary The dictionary, once populated with Words.
* \param glossary The glossary, generates glossary of rare words.
*/
CliUserInterface::CliUserInterface(Dictionary& dictionary, Glossary& glossary) : 
    _dictionary(dictionary), 
    _glossary(glossary)
{
    _menu = 
        "[" + MenuItem::SEARCH_DEFINITION_SCORE + "] " + SEARCH_DEFINITION_TITLE + '\n' +
        "[" + MenuItem::LONGEST_WORDS + "] " + LONGEST_WORDS_TITLE + '\n' +
        "[" + MenuItem::LOGY_WORDS + "] " + LOGY_WORDS_TITLE + '\n' +
        "[" + MenuItem::RHYME_WORDS + "] " + RHYME_WORDS_TITLE + '\n' +
        "[" + MenuItem::ANAGRAM_WORD + "] " + ANAGRAM_WORD_TITLE + '\n' +
        "[" + MenuItem::ANAGRAM_STRING + "] " + ANAGRAM_STRING_TITLE + '\n' +
        "[" + MenuItem::GLOSSARY + "] " + GLOSSARY_TITLE + '\n' +
        "[" + MenuItem::QUIT + "] Quit";
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

    onSelect(selection);
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
        Logger::log(Info, SEARCH_DEFINITION_TITLE + ":");
        Logger::log(Input, "Enter a word to find its definition and scrabble score");
        Logger::log(CONTROL_TITLE);
        Logger::printPrompt();
        getline(cin, word);

        // don't print definition for control chars
        if (isControlChar(word))
            continue;
        
        Logger::log(Output, "Definition and scrabble score for '" + word + "':");
        Logger::log(_dictionary.getDefinition(word));
    }
    while (!isControlChar(word));

    onControl(word);
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
        Logger::log(Info, RHYME_WORDS_TITLE + ':');
        Logger::log(Input, "Enter a word at least 3 letters long to find words that rhyme");
        Logger::log(CONTROL_TITLE);

        Logger::printPrompt();
        getline(cin, word);

        // don't print rhymes for control chars
        if (isControlChar(word))
            continue;
        // validate input
        if (!isValidRhymeWord(word))
            continue;

        auto rhymes = _dictionary.getRhymes(word);

        // tell user when nothing found then go back to top of loop
        if (rhymes.empty())
        {
            Logger::log(Output, "No rhymes found for '" + word + '\'');
            continue;
        }

        // show result
        Logger::log(Output, "Found " + to_string(rhymes.size()) + " word/s that rhyme with '" + word + "':");

        for (auto& it : rhymes)
            Logger::log(it->getWord());
    }
    while (!isControlChar(word));

    onControl(word);
}

/**
* \brief Find anagram/s for a word from the dictionary.
*/
void CliUserInterface::wordAnagrams()
{
    string word;
    do
    {
        Logger::log(Info, ANAGRAM_WORD_TITLE + ':');
        Logger::log(Input, "Enter a word from the dictionary to find it's anagram/s");
        Logger::log(CONTROL_TITLE);

        Logger::printPrompt();
        getline(cin, word);

        // don't print anagrams for control chars
        if (isControlChar(word))
            continue;

        auto anagrams = _dictionary.getWordAnagrams(word);

        // tell user when nothing found then go back to top of loop
        if (anagrams.empty())
        {
            Logger::log(Output, "No anagrams found for '" + word + '\'');
            continue;
        }

        // show result
        Logger::log(Output, "Found " + to_string(anagrams.size()) + " anagram/s of '" + word + "':");

        for (const auto& it : anagrams)
            Logger::log(it->getWord());
    }
    while (!isControlChar(word));

    onControl(word);
}

/**
* \brief Find anagram/s for a string of letters, doesn't have to be a word or exist in dictionary.
* Prints any anagram/s found, else notifies user no anagrams are found.
*/
void CliUserInterface::stringAnagrams()
{
    string word;
    do
    {
        Logger::log(Info, ANAGRAM_STRING_TITLE + ":");
        Logger::log(Input, "Enter a string of letters to find legal scrabble anagram/s with its (score)");
        Logger::log(CONTROL_TITLE);

        Logger::printPrompt();
        getline(cin, word);

        // don't print anagrams for control chars
        if (isControlChar(word))
            continue;

        auto anagrams = _dictionary.getStringAnagrams(word);

        // tell user when nothing found then go back to top of loop
        if (anagrams.empty())
        {
            Logger::log(Output, "No anagrams found for '" + word + '\'');
            continue;
        }

        // show result
        Logger::log(Output, "Found " + to_string(anagrams.size()) + " legal scrabble anagram/s of '" + word + "':");

        for (const auto& it : anagrams)
            Logger::log(it->getWord() + " (" + to_string(it->getScrabbleScore()) + ')');
    }
    while (!isControlChar(word));

    onControl(word);
}

/**
* \brief Glossary is generated asynchronously at main. This allows user to get answers for other
* Dictionary tasks while glossary is generated on another thread in the background.
* When the user selects this menu item, if task not yet complete, ask user to try again later,
* else go ahead and write glossary to file.
*/
void CliUserInterface::writeGlossary()
{
    if (!_glossary.isLoaded())
    {
        Logger::log(Error, "Glossary not yet generated, try again in a few seconds");
        start();
    }

    Logger::log(Output, "Writing glossary to '" + _glossary.getOutputFilepath() + "'...");

    // print glossary
    for (const auto& entry : *_glossary.getGlossary())
        Logger::log(entry.second + '\n');

    // write glossary
    _glossary.write();

    Logger::log(Info, "Operation complete, wrote " + to_string(_glossary.size()) + " entries to '" + _glossary.getOutputFilepath() + '\'');
    start();
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
    const auto isValid = selection == MenuItem::SEARCH_DEFINITION_SCORE
        || selection == MenuItem::LONGEST_WORDS
        || selection == MenuItem::LOGY_WORDS
        || selection == MenuItem::RHYME_WORDS
        || selection == MenuItem::ANAGRAM_WORD
        || selection == MenuItem::ANAGRAM_STRING
        || selection == MenuItem::GLOSSARY
        || selection == MenuItem::QUIT;

    if (!isValid)
        Logger::log(Error, '\'' + selection + "' is not a valid selection, try again");

    return isValid;
}

/**
* \brief Returns true if word length is at least MIN_RHYME_LENGTH.
* \param word The word to search for rhymes.
* \return True if word length is at least MIN_RHYME_LENGTH.
*/
bool CliUserInterface::isValidRhymeWord(const string& word) const
{
    const auto isValid = word.length() >= MIN_RHYME_LENGTH;

    if (!isValid)
        Logger::log(Error, '\'' + word + "' must be at least " + to_string(MIN_RHYME_LENGTH) + " letters long, try again");

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

/**
* \brief Handles the main menu selection by the user.
* \param selection The menu item selected by the user.
*/
void CliUserInterface::onSelect(const std::string& selection)
{
    if (selection == MenuItem::SEARCH_DEFINITION_SCORE)
    {
        findDefinition();
        return;
    }
    if (selection == MenuItem::LONGEST_WORDS)
    {
        longestWords();
        return;
    }
    if (selection == MenuItem::LOGY_WORDS)
    {
        wordsEndWithLogy();
        return;
    }
    if (selection == MenuItem::RHYME_WORDS)
    {
        rhymeWords();
        return;
    }
    if (selection == MenuItem::ANAGRAM_WORD)
    {
        wordAnagrams();
        return;
    }
    if (selection == MenuItem::ANAGRAM_STRING)
    {
        stringAnagrams();
        return;
    }
    if (selection == MenuItem::GLOSSARY)
    {
        writeGlossary();
        return;
    }
    if (selection == MenuItem::QUIT)
    {
        shutdown();
    }
}

/**
* \brief Handles the control option selected by the user.
* \param control The control option selected by the user.
*/
void CliUserInterface::onControl(const std::string& control)
{
    if (control == MenuItem::BACK)
        start();
    if (control == MenuItem::QUIT)
        shutdown();
}

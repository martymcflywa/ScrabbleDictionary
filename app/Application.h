#pragma once
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryTask.h"
#include "../lib/StringExtractor.h"
#include "../lib/TextFileLoader.h"

namespace app
{
    class Application
    {
        const string _filepath;
        TextFileLoader _loader;
        DefinitionFormatter _formatter;
        DefinitionPrinter _printer;
        DictionaryTask _task;
        StringExtractor _extractor;
        Dictionary _dictionary;

    public:
        /**
         * \brief Instantiate all the interface implementations, inject dependencies where needed, then construct the Dictionary.
         */
        Application();
        /**
         * \brief Loads the dictionary.
         */
        void init();
        /**
         * \brief Show the main menu. Ask user to select from menu, then perform selected task.
         * If input is invalid, menu is shown again.
         * Retry until user picks correct input or rage quits with CTRL+C.
         */
        void mainMenu();
    private:
        /**
         * \brief Returns true if user input at main menu matches any MenuItem.
         * \param selection The input from the user at main menu.
         * \returns true if input matches any MenuItem. 
         */
        static bool isValidMenuItem(const string& selection);
        /**
         * \brief Asks user to input a word. Dictionary will attempt to find it.
         * If found, will print definition, else will notify user word is not found.
         * Repeat until user chooses to go back to main menu.
         */
        void findDefinition();
        /**
         * \brief Prints longest word/s in dictionary.
         * Then returns to main menu.
         */
        void longestWords();
        /**
         * \brief Prints words that end in 'logy' with length seven or less in dictionary.
         * Then returns to main menu.
         */
        void wordsEndWithLogy();
    };
}

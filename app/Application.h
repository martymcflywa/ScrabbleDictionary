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
        string _filepath;
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
         */
        void mainMenu();
    private:
        void findDefinition();
        void longestWord();
        void wordsEndWithLogy();
    };
}

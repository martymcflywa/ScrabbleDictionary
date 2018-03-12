#pragma once
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/StringExtractor.h"
#include "../lib/TextFileLoader.h"
#include "../lib/DictionaryTask.h"

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
         * \brief Runs the app. Ask user to select from menu, then perform selected task.
         */
        void run();
    private:
        void searchDefinition();
        void longestWord();
        void wordsEndWithLogy();
    };
}

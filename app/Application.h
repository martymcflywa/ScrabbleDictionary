#pragma once
#include "../cli/CliUserInterface.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryTask.h"
#include "../lib/StringExtractor.h"
#include "../lib/TextFileLoader.h"

using namespace cli;

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
        CliUserInterface _ui;

    public:
        /**
        * \brief Instantiate all the interface implementations, inject dependencies where needed,
        * construct the Dictionary, then user interface.
        */
        Application();
        /**
         * \brief Load the dictionary.
         */
        void init();
        /**
        * \brief Start at main menu.
        */
        void run();
    };
}

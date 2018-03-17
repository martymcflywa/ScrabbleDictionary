#pragma once
#include "../cli/CliUserInterface.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryExtractor.h"
#include "../lib/DictionaryTask.h"
#include "../lib/TextFileLoader.h"

namespace app
{
    class Application
    {
        const std::string _filepath;
        lib::TextFileLoader _loader;
        lib::DefinitionFormatter _formatter;
        lib::DefinitionPrinter _printer;
        lib::DictionaryTask _task;
        lib::DictionaryExtractor _extractor;
        lib::Dictionary _dictionary;
        cli::CliUserInterface _ui;

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

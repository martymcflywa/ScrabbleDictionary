#pragma once
#include "../cli/CliUserInterface.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryExtractor.h"
#include "../lib/DictionaryTask.h"
#include "../lib/GlossaryExtractor.h"
#include "../lib/GlossaryFormatter.h"
#include "../lib/GlossaryWriter.h"
#include "../lib/TextFileReader.h"

namespace app
{
    class Application
    {
        const std::string _dictionaryFilepath;
        lib::TextFileReader _dictionaryReader;
        lib::DefinitionFormatter _dictionaryFormatter;
        lib::DefinitionPrinter _dictionaryPrinter;
        lib::DictionaryTask _dictionaryTask;
        lib::DictionaryExtractor _dictionaryExtractor;
        lib::Dictionary _dictionary;

        std::string _usageFilepath;
        std::string _rareWordFilepath;
        std::string _glossaryFilepath;
        lib::GlossaryFormatter _glossaryFormatter;
        lib::GlossaryExtractor _glossaryExtractor;
        lib::GlossaryWriter _glossaryWriter;
        lib::Glossary _glossary;

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

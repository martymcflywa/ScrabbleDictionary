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
        lib::TextFileReader _dictionaryReader;
        lib::DefinitionFormatter _dictionaryFormatter;
        lib::DefinitionPrinter _dictionaryPrinter;
        lib::DictionaryTask _dictionaryTask;
        lib::DictionaryExtractor _dictionaryExtractor;
        lib::Dictionary _dictionary;

        lib::TextFileReader _usageReader;
        lib::TextFileReader _rareWordReader;
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
        void loadDictionary();
        void generateGlossaryAsync();
        /**
        * \brief Start at main menu.
        */
        void run();
    };
}

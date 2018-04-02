#include "stdafx.h"
#include <chrono>
#include <future>
#include "Application.h"
#include "../cli/CliUserInterface.h"
#include "../cli/Logger.h"


using namespace std;
using namespace std::chrono;
using namespace app;
using namespace cli;
using namespace lib;

/**
* \brief Instantiate all the interface implementations, inject dependencies where needed,
* construct the Dictionary, Glossary then UI.
*/
Application::Application() :
    // build the dictionary
    _dictionaryReader(TextFileReader(string(".\\dictionary2018.txt"))),
    _dictionaryFormatter(DefinitionFormatter()),
    _dictionaryPrinter(DefinitionPrinter(_dictionaryFormatter)),
    _dictionaryTask(DictionaryTask()),
    _dictionaryExtractor(DictionaryExtractor(_dictionaryPrinter, _dictionaryTask)),
    _dictionary(Dictionary(_dictionaryExtractor, _dictionaryTask)),
    // build the glossary
    _usageReader(TextFileReader(string(".\\many_english_works.txt"))),
    _rareWordReader(TextFileReader(string(".\\new_work.txt"))),
    _glossaryFormatter(GlossaryFormatter()),
    _glossaryExtractor(GlossaryExtractor()),
    _glossaryWriter(string(".\\glossary.txt")),
    _glossary(Glossary(
        _dictionary, 
        _usageReader, 
        _rareWordReader, 
        _glossaryExtractor, 
        _glossaryFormatter, 
        _glossaryWriter)),
    // build the ui
    _ui(CliUserInterface(_dictionary, _glossary))
{
}

/**
 * \brief Call this synchronously, we want this to be completely populated before doing anything else.
 */
void Application::loadDictionary()
{
    Logger::log(Info, "Loading dictionary...");

    // instrument this operation
    const auto start = steady_clock::now();

    _dictionary.loadDictionary(_dictionaryReader);

    const auto end = steady_clock::now();
    const auto delta = duration<double>(end - start);
    const auto message = "Loaded dictionary with " + to_string(_dictionary.size()) + " entries";

    Logger::log(Info, message, delta);
}

/**
 * \brief Call this asynchronously. Glossary is generated in the background on another thread 
 * while user interacts with rest of menu. Stop user from selecting glossary item in menu until this task is complete.
 * Let user know when task complete.
 */
void Application::generateGlossaryAsync()
{
    Logger::log(Info, "Generating glossary asynchronously...");

    // instrument this operation
    const auto start = steady_clock::now();

    async([&](){ _glossary.generateAsync(); }).wait();

    const auto end = steady_clock::now();
    const auto delta = duration<double>(end - start);
    const auto message = "Generated glossary with " + to_string(_glossary.size()) + " entries";

    // announce glossary is ready
    Logger::log(Task, message, delta);
}


/**
 * \brief Starts at main menu.
 */
void Application::run()
{
    _ui.start();
}

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
* construct the Dictionary and Glossary, then UI.
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
    _dictionary.loadDictionary(_dictionaryReader);
    const auto message = "Loaded dictionary with " + to_string(_dictionary.size()) + " entries";
    Logger::log(Info, message);
}

/**
 * \brief Call this asynchronously. Glossary is generated in the background on another thread 
 * while user interacts with rest of menu. Stop user from selecting glossary item in menu until this task is complete.
 * Let user know when task complete.
 */
void Application::generateGlossaryAsync()
{
    Logger::log(Task, "Generating glossary asynchronously...");

    auto glossaryTask = async([&](){ _glossary.generateAsync(); });

    // poll to check task is done
    auto taskDone = false;
    do
    {
        taskDone = glossaryTask.wait_for(milliseconds(300)) == future_status::ready;
    }
    while (!taskDone);

    // let user know glossary is ready
    Logger::log(Task, "Glossary now ready with " + to_string(_glossary.size()) + " entries");
}


/**
 * \brief Starts at main menu.
 */
void Application::run()
{
    _ui.start();
}

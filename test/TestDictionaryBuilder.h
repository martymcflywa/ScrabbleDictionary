#pragma once
#include <string>
#include "TestFileFactory.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryTask.h"
#include "../lib/StringExtractor.h"
#include "../lib/TextFileLoader.h"

class TestDictionaryBuilder
{
    const std::string FILEPATH = ".\\test.txt";
    const std::string TYPE_AND_DEF = " [n]\nSome definition.\n\n";
    std::string _content;
    TestFileFactory _fileFactory;
    lib::TextFileLoader _loader;
    lib::DefinitionFormatter _formatter;
    lib::DefinitionPrinter _printer;
    lib::DictionaryTask _task;
    lib::StringExtractor _extractor;
    lib::Dictionary _dictionary;
public:
    TestDictionaryBuilder(const std::list<std::string>& words);
    TestDictionaryBuilder(const std::string& word, const std::string& typeAndDef);
    lib::Dictionary& build();
private:
    std::string buildContent(const std::list<std::string>& words) const;
    static std::string buildContent(const std::string& word, const std::string& typeAndDef);
};

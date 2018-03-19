#pragma once
#include <string>
#include "TestReader.h"
#include "../lib/DefinitionFormatter.h"
#include "../lib/DefinitionPrinter.h"
#include "../lib/Dictionary.h"
#include "../lib/DictionaryExtractor.h"
#include "../lib/DictionaryTask.h"

class TestDictionaryBuilder
{
    const std::string TYPE_AND_DEF = " [n]\nSome definition.\n\n";
    std::string _content;
    TestReader _reader;
    lib::DefinitionFormatter _formatter;
    lib::DefinitionPrinter _printer;
    lib::DictionaryTask _task;
    lib::DictionaryExtractor _extractor;
    lib::Dictionary _dictionary;
public:
    TestDictionaryBuilder(const std::list<std::string>& words);
    TestDictionaryBuilder(const std::list<std::string>& words, const std::list<std::string>& typeAndDefs);
    TestDictionaryBuilder(const std::string& word, const std::string& typeAndDef);
    lib::Dictionary& build();
private:
    std::string buildContent(const std::list<std::string>& words) const;
    static std::string buildContent(const std::list<std::string>& words, const std::list<std::string> typeAndDefs);
    static std::string buildContent(const std::string& word, const std::string& typeAndDef);
};

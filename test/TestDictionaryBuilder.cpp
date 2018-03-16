#include "stdafx.h"
#include "TestDictionaryBuilder.h"

using namespace std;
using namespace lib;

TestDictionaryBuilder::TestDictionaryBuilder(const list<string>& words) :
    _content(buildContent(words)),
    _fileFactory(TestFileFactory(FILEPATH, _content)),
    _loader(TextFileLoader(FILEPATH)),
    _formatter(DefinitionFormatter()),
    _printer(DefinitionPrinter(_formatter)),
    _task(DictionaryTask()),
    _extractor(StringExtractor(_printer, _task)),
    _dictionary(Dictionary(_loader, _extractor))
{
}

TestDictionaryBuilder::TestDictionaryBuilder(const string& word, const string& typeAndDef) :
    _content(buildContent(word, typeAndDef)),
    _fileFactory(TestFileFactory(FILEPATH, _content)),
    _loader(TextFileLoader(FILEPATH)),
    _formatter(DefinitionFormatter()),
    _printer(DefinitionPrinter(_formatter)),
    _task(DictionaryTask()),
    _extractor(StringExtractor(_printer, _task)),
    _dictionary(Dictionary(_loader, _extractor))
{
}

Dictionary& TestDictionaryBuilder::build()
{
    _dictionary.loadDictionary();
    _loader.dispose();
    _fileFactory.cleanup();

    return _dictionary;
}

string TestDictionaryBuilder::buildContent(const list<string>& words) const
{
    string content = "";

    for (const auto word : words)
        content += word + TYPE_AND_DEF;

    return content;
}

std::string TestDictionaryBuilder::buildContent(const std::string& word, const std::string& typeAndDef)
{
    return word + typeAndDef;
}

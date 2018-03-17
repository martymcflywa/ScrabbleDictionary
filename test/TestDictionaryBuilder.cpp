#include "stdafx.h"
#include "TestDictionaryBuilder.h"

using namespace std;
using namespace lib;

TestDictionaryBuilder::TestDictionaryBuilder(const list<string>& words) :
    _content(buildContent(words)),
    _loader(TestLoader()),
    _formatter(DefinitionFormatter()),
    _printer(DefinitionPrinter(_formatter)),
    _task(DictionaryTask()),
    _extractor(DictionaryExtractor(_printer, _task)),
    _dictionary(Dictionary(_loader, _extractor, _task))
{
}

TestDictionaryBuilder::TestDictionaryBuilder(const list<string>& words, const list<string>& typeAndDefs) :
    _content(buildContent(words, typeAndDefs)),
    _loader(TestLoader()),
    _formatter(DefinitionFormatter()),
    _printer(DefinitionPrinter(_formatter)),
    _task(DictionaryTask()),
    _extractor(DictionaryExtractor(_printer, _task)),
    _dictionary(Dictionary(_loader, _extractor, _task))
{
}

TestDictionaryBuilder::TestDictionaryBuilder(const string& word, const string& typeAndDef) :
    _content(buildContent(word, typeAndDef)),
    _loader(TestLoader()),
    _formatter(DefinitionFormatter()),
    _printer(DefinitionPrinter(_formatter)),
    _task(DictionaryTask()),
    _extractor(DictionaryExtractor(_printer, _task)),
    _dictionary(Dictionary(_loader, _extractor, _task))
{
}

Dictionary& TestDictionaryBuilder::build()
{
    _loader.setTestFile(_content);
    _dictionary.loadDictionary();
    _loader.dispose();

    return _dictionary;
}

string TestDictionaryBuilder::buildContent(const list<string>& words) const
{
    string content = "";

    for (const auto word : words)
        content += word + TYPE_AND_DEF;

    return content;
}

string TestDictionaryBuilder::buildContent(const list<string>& words, const list<string> typeAndDefs)
{
    string content = "";

    for (auto wordIt = words.begin(), typeAndDefIt = typeAndDefs.begin();
        wordIt != words.end() || typeAndDefIt != typeAndDefs.end();
        ++wordIt, ++typeAndDefIt)
    {
        content += string(wordIt->c_str()) + string(typeAndDefIt->c_str());
    }
    return content;
}

string TestDictionaryBuilder::buildContent(const string& word, const string& typeAndDef)
{
    return word + typeAndDef;
}

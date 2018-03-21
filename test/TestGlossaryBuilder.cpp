#include "stdafx.h"
#include "TestGlossaryBuilder.h"
#include "../lib/GlossaryExtractor.h"
#include "TestReader.h"

using namespace std;
using namespace lib;

TestGlossaryBuilder::TestGlossaryBuilder(Dictionary& dictionary, const string& usageContent, const string& rareWordContent) :
    _dictionary(dictionary),
    _usageContent(usageContent),
    _usageReader(TestReader()),
    _rareWordContent(rareWordContent),
    _rareWordReader(TestReader()),
    _extractor(GlossaryExtractor()),
    _formatter(GlossaryFormatter()),
    _writer(TestWriter()),
    _glossary(Glossary(_dictionary, _usageReader, _rareWordReader, _extractor, _formatter, _writer))
{
}

Glossary& TestGlossaryBuilder::build()
{
    _usageReader.setTestFile(_usageContent);
    _rareWordReader.setTestFile(_rareWordContent);
    return _glossary;
}

TestWriter& TestGlossaryBuilder::getWriter()
{
    return _writer;
}

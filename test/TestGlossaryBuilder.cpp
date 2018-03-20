#include "stdafx.h"
#include "TestGlossaryBuilder.h"
#include "../lib/GlossaryExtractor.h"

using namespace lib;

TestGlossaryBuilder::TestGlossaryBuilder(Dictionary& dictionary) :
    _dictionary(dictionary),
    _extractor(GlossaryExtractor()),
    _writer(TestWriter()),
    _glossary(Glossary(_dictionary, _extractor, _writer))
{
}

Glossary& TestGlossaryBuilder::build()
{
    return _glossary;
}

TestWriter& TestGlossaryBuilder::getWriter()
{
    return _writer;
}

#include "stdafx.h"
#include "TestGlossaryBuilder.h"
#include "../lib/GlossaryExtractor.h"

using namespace lib;

TestGlossaryBuilder::TestGlossaryBuilder(lib::Dictionary& dictionary) :
    _dictionary(dictionary),
    _extractor(GlossaryExtractor())
{
}

Glossary TestGlossaryBuilder::build()
{
    return Glossary(_dictionary, _extractor);
}

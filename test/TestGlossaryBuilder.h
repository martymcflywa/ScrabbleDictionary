#pragma once
#include "../lib/Dictionary.h"
#include "../lib/GlossaryExtractor.h"
#include "../lib/Glossary.h"

class TestGlossaryBuilder
{
    lib::Dictionary& _dictionary;
    lib::GlossaryExtractor _extractor;

public:
    TestGlossaryBuilder(lib::Dictionary& dictionary);
    lib::Glossary build();
};

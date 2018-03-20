#pragma once
#include "../lib/Dictionary.h"
#include "../lib/Glossary.h"
#include "../lib/GlossaryExtractor.h"
#include "TestWriter.h"

class TestGlossaryBuilder
{
    lib::Dictionary& _dictionary;
    lib::GlossaryExtractor _extractor;
    TestWriter _writer;
    lib::Glossary _glossary;

public:
    TestGlossaryBuilder(lib::Dictionary& dictionary);
    lib::Glossary& build();
    TestWriter& getWriter();
};

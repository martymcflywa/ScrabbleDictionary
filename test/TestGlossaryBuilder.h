#pragma once
#include "../lib/Dictionary.h"
#include "../lib/Glossary.h"
#include "../lib/GlossaryExtractor.h"
#include "TestWriter.h"
#include "../lib/GlossaryFormatter.h"
#include "TestReader.h"

class TestGlossaryBuilder
{
    lib::Dictionary& _dictionary;
    std::string _usageContent;
    TestReader _usageReader;
    std::string _rareWordContent;
    TestReader _rareWordReader;
    lib::GlossaryExtractor _extractor;
    lib::GlossaryFormatter _formatter;
    TestWriter _writer;
    lib::Glossary _glossary;

public:
    TestGlossaryBuilder(lib::Dictionary& dictionary, const std::string& usageContent, const std::string& rareWordContent);
    lib::Glossary& build();
    TestWriter& getWriter();
};

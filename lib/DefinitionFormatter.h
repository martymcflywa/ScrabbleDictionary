#pragma once
#include <string>
#include "IFormat.h"

using namespace lib;

class DefinitionFormatter : public IFormat
{
public:
    string format(Word& word) override;
};

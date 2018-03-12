#pragma once
#include "IPrint.h"
#include "IFormat.h"

namespace lib
{
    class DefinitionPrinter : public IPrint
    {
        IFormat& _formatter;

    public:
        DefinitionPrinter(IFormat& formatter);
        void print(const Word& word) override;
    };
}

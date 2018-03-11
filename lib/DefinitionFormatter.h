#pragma once
#include <string>
#include "IFormat.h"

namespace lib
{
    /**
     * \brief Formats the definition when printing to console.
     */
    class DefinitionFormatter : public IFormat
    {
    public:
        string format(Word& word) override;
    };
}

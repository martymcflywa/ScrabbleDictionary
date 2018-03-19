#pragma once
#include "IFormat.h"

namespace lib
{
    /**
     * \brief Formats a Word for the glossary.
     */
    class GlossaryFormatter : public IFormat
    {
    public:
        std::string format(const Word& word) override;
    };
}

#pragma once
#include <string>

namespace lib
{
    class Word;

    /**
     * \brief IPrint interface. Implement this interface to print dictionary entries.
     * Inject this dependency to Word to decouple implementation details of printing the entries.
     * It also enables unit testing of print requirements, see TestPrinter.cpp.
     */
    class IPrint
    {
    public:
        virtual ~IPrint() = default;
        virtual std::string print(const Word& word) = 0;
    };
}

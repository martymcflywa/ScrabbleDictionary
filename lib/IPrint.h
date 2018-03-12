#pragma once

using namespace std;

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
        virtual void print(const Word& word) = 0;
    };
}

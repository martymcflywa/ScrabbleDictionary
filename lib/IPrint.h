#pragma once
#include <string>

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
        // TODO: abstract this further so it is implemented only once
        virtual string format(Word& word) = 0;

    public:
        virtual ~IPrint() = default;
        virtual void print(Word& word) = 0;
    };
}

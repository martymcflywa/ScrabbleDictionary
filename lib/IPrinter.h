#pragma once
#include <string>

using namespace std;

namespace lib
{
    class Word;

    // Dependency injecting IPrinter so output can be tested.
    class IPrinter
    {
        // TODO: abstract this further so it is implemented only once
        virtual string format(Word& word) = 0;

    public:
        virtual ~IPrinter() = default;
        virtual void print(Word& word) = 0;
    };
}

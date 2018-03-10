#pragma once
#include <string>

using namespace std;

namespace lib {

    class Word;

    /**
     * \brief IFormat interface. Implement this interface to format the output for IPrinter.
     * Inject this dependency to IPrinter to decouple implementation detail of formatting the string.
     */
    class IFormat
    {
    public:
        virtual ~IFormat() = default;
        virtual string format(Word& word) = 0;
    };
}

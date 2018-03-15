#pragma once
#include <string>

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
        virtual std::string format(const Word& word) = 0;
    };
}

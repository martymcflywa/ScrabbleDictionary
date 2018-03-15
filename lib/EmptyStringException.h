#pragma once
#include <stdexcept>

namespace lib
{
    /**
     * \brief Throw this when a string is empty.
     */
    class EmptyStringException : public std::logic_error
    {
    public:
        typedef logic_error logicError;
        EmptyStringException();
        EmptyStringException(const std::string& arg);
    };
}

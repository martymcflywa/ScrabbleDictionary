#pragma once
#include <stdexcept>

namespace lib
{
    /**
     * \brief Throw when an unsupported type is used.
     */
    class UnsupportedTypeException : public std::logic_error
    {
    public:
        typedef logic_error logicError;
        UnsupportedTypeException(const std::string& type);
    };
}

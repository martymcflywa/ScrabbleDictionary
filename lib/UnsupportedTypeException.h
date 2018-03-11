#pragma once
#include <stdexcept>

using namespace std;

namespace lib
{
    /**
     * \brief Throw when an unsupported type is used.
     */
    class UnsupportedTypeException : public logic_error
    {
    public:
        typedef logic_error logicError;
        UnsupportedTypeException(const string& type);
    };
}

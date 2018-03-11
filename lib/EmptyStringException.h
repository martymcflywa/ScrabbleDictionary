#pragma once
#include <stdexcept>

using namespace std;

namespace lib
{
    /**
     * \brief Throw this when a string is empty.
     */
    class EmptyStringException : public logic_error
    {
    public:
        typedef logic_error logicError;
        EmptyStringException();
        EmptyStringException(const string& arg);
    };
}

#pragma once
#include <stdexcept>

using namespace std;

namespace lib
{
    /**
     * \brief Throw when there's a problem reading a file.
     */
    class FileReadException : public logic_error
    {
    public:
        typedef logic_error logicError;
        FileReadException(const string& filepath);
    };
}

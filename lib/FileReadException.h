#pragma once
#include <stdexcept>

namespace lib
{
    /**
     * \brief Throw when there's a problem reading a file.
     */
    class FileReadException : public std::logic_error
    {
    public:
        typedef logic_error logicError;
        FileReadException(const std::string& filepath);
    };
}

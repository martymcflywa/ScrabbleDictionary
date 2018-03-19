#pragma once
#include <stdexcept>

namespace lib
{
    /**
     * \brief Throw when there's a problem reading/writing a file.
     */
    class FileIoException : public std::logic_error
    {
    public:
        typedef logic_error logicError;
        FileIoException(const std::string& operation, const std::string& filepath);
    };
}

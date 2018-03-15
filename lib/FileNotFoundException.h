#pragma once
#include <string>

namespace lib
{
    /**
     * \brief Throw this when file isn't found.
     */
    class FileNotFoundException : public std::logic_error
    {
    public:
        typedef logic_error logicError;
        FileNotFoundException(const std::string& filepath);
    };
}

#pragma once
#include <stdexcept>

namespace lib
{
    class UnsupportedTaskException : public std::logic_error
    {
    public:
        explicit UnsupportedTaskException(const std::string& taskType);
    };
}

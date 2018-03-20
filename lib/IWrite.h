#pragma once
#include <string>

namespace lib
{
    /**
     * \brief Implement this interface to write stuff.
     * \tparam TInput The input type that this interface will write.
     */
    template<typename TInput>
    class IWrite
    {
    public:
        virtual ~IWrite() = default;
        virtual void write(TInput) = 0;
        virtual std::string getFilepath() = 0;
    };
}

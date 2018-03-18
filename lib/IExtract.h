#pragma once

namespace lib
{
    /**
     * \brief IExtract interface. Implement this interface to extract values from a loaded dictionary source.
     * Inject this dependency to Dictionary to decouple implementation details of extracting values from some source.
     * A different source may be provided in another format (ie. not 3 lines, etc.) and could easily create a new implementation
     * of IExtract to handle that.
     * \tparam TResult The return type of IExtract::extract()
     * \tparam TInput The input type of IExtract::extract()
     */
    template<typename TResult, typename TInput>
    class IExtract
    {
    public:
        virtual ~IExtract() = default;
        virtual TResult extract(TInput content) = 0;
    };
}

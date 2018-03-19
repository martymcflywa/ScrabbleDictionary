#pragma once
#include <istream>

namespace lib
{
    /**
     * \brief IRead interface. Implement this interface to read stuff from a source.
     * Inject this dependency to decouple implementation details of reading stuff from a source.
     */
    class IRead
    {
    public:
        IRead() = default;
        virtual ~IRead() = default;
        /**
         * \brief Reads from the source thing.
         * \return A stream from the source thing.
         */
        virtual std::istream& read() = 0;
        /**
         * \brief Release the resource.
         */
        virtual void dispose() = 0;
    };
}

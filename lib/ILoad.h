#pragma once

namespace lib
{
    /**
     * \brief ILoad interface. Implement this interface to load dictionaries from source files, databases etc.
     * Inject this dependency to Dictionary to decouple implementation details of loading a source dictionary.
     */
    class ILoad
    {
    public:
        ILoad() = default;
        virtual ~ILoad() = default;
        /**
         * \brief Loads the source dictionary.
         * \return the source dictionary contents as an istream.
         */
        virtual std::istream& load() = 0;
        /**
         * \brief Close the resource.
         */
        virtual void dispose() = 0;
    };
}
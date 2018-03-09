#pragma once

using namespace std;

namespace lib
{
    /**
     * \brief ILoad interface. Implement this interface to load dictionaries from source files, databases etc.
     * Inject this dependency to Dictionary to decouple implementation details of retrieving dictionary entries from a source.
     */
    class ILoad
    {
    public:
        virtual ~ILoad() = default;
        virtual istream& load(string filepath) = 0;
    };
}
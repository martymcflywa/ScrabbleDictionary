#pragma once
#include <map>
#include "Word.h"

using namespace std;

namespace lib
{
    /**
     * \brief IExtract interface. Implement this interface to extract values from a loaded dictionary source.
     * Inject this dependency to Dictionary to decouple implementation details of extracting values from a dictionary source.
     * A different source may be provided in another format (ie. not 3 lines, etc.) and could easily create a new implementation
     * of IExtract to handle that.
     */
    class IExtract
    {
    public:
        virtual ~IExtract() = default;
        virtual map<string, Word> extract(istream& content) = 0;
    };
}

#pragma once
#include <map>
#include <list>
#include "Word.h"

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
        virtual std::map<std::string, Word> extract(std::istream& content) = 0;
        virtual std::list<std::string> getLongestWords() = 0;
        virtual std::list<std::string> getLogyWords() = 0;
    };
}

#pragma once
#include <string>

using namespace std;

namespace lib
{
    /**
     * \brief Throw this when file isn't found.
     */
    class FileNotFoundException : public logic_error
    {
    public:
        typedef logic_error logicError;
        FileNotFoundException(const string& filepath);
    };
}

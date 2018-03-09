#pragma once

using namespace std;

namespace lib
{
    // Dependency injecting ILoader to improve testability of dictionary.
    class ILoader
    {
    public:
        virtual ~ILoader() = default;
        virtual istream& load(string filepath) = 0;
    };
}
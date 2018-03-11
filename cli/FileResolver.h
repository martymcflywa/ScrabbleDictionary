#pragma once
#include <string>

using namespace std;

namespace cli
{
    class FileResolver
    {
    public:
        static string getFilepath();
    private:
        static string validate(string& filepath);
    };
}
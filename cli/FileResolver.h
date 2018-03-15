#pragma once

namespace cli
{
    class FileResolver
    {
    public:
        static std::string getFilepath();
    private:
        static std::string validate(std::string& filepath);
    };
}
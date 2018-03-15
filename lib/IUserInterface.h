#pragma once

namespace lib
{
    class IUserInterface
    {
    public:
        virtual ~IUserInterface() = default;
        virtual void mainMenu() = 0;
        virtual void findDefinition() = 0;
        virtual void longestWords() = 0;
        virtual void wordsEndWithLogy() = 0;
    };
}

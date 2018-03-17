#pragma once

namespace lib
{
    class IUserInterface
    {
    public:
        virtual ~IUserInterface() = default;
        virtual void start() = 0;
    };
}

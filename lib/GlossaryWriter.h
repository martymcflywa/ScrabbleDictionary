#pragma once
#include "IWrite.h"
#include <string>

namespace lib
{
    class GlossaryWriter : public IWrite<const std::string&>
    {
        std::string _filepath;
    public:
        GlossaryWriter(const std::string& filepath);
        void write(const std::string& content) override;
        std::string getFilepath() override;
    };
}


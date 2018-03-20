#pragma once
#include "IWrite.h"
#include <string>

namespace lib
{
    /**
    * \brief Implementation of IWrite. Responsible for writing strings to text files.
    */
    class TextFileWriter : public lib::IWrite<const std::string&>
    {
        std::string _filepath;

    public:
        TextFileWriter(const std::string& filepath);
        void write(const std::string& content) override;
    };

}
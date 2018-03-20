#include "stdafx.h"
#include "GlossaryWriter.h"
#include <fstream>
#include "FileIoException.h"

using namespace std;
using namespace lib;

GlossaryWriter::GlossaryWriter(const string& filepath) : _filepath(filepath)
{
}

void GlossaryWriter::write(const string& content)
{
    auto file = ofstream(_filepath);

    if(!file.is_open())
        throw FileIoException("writing", _filepath);

    file << content;
    file.close();
}

std::string GlossaryWriter::getFilepath()
{
    return _filepath;
}

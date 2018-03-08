#pragma once
#include <string>
#include "IPrinter.h"
#include "WordType.h"

using namespace std;

namespace lib
{
    class Word
    {
        string _word;
        Type _type;
        string _definition;
        IPrinter& _printer;

        static Type resolveType(string type);

    public:
        Word(const string word, const string type, const string definition, IPrinter& printer);

        string getWord() const;
        Type getType() const;
        string getDefinition() const;
        void printDefinition();
    };
}

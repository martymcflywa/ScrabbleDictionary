#pragma once
#include <string>
#include "IPrinter.h"
#include "WordType.h"

using namespace std;

namespace lib
{
    class Word
    {
		// keep default ctr private, params required when instantiating Word
		Word();
        string _word;
        Type _type;
        string _definition;
        IPrinter& _printer;

        static Type resolveType(const string& type);
		static string validate(const string& input);
    public:
        Word(const string& word, const string& type, const string& definition, IPrinter& printer);

        string getWord() const;
        Type getType() const;
        string getDefinition() const;
        void printDefinition();
		bool operator == (const Word& that) const;
    };
}

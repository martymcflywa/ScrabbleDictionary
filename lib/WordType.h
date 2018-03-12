#pragma once
#include <string>
#include <map>

using namespace std;

namespace lib
{
    enum Type
    {
        Verb,
        Noun,
        Adverb,
        Adjective,
        Preposition,
        ProperNoun,
        NounAndVerb,
        Misc
    };

    class WordType
    {
        static map<Type, string> _typeMap;

    public:
        static string getName(const Type& type);
    };
}


#pragma once
#include <map>
#include <string>

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
        static std::map<Type, std::string> _typeMap;

    public:
        static std::string getName(const Type& type);
    };
}


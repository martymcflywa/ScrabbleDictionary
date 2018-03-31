#pragma once
#include <string>
#include <unordered_map>

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
        static std::unordered_map<Type, std::string> _typeMap;

    public:
        static std::string getName(const Type& type);
    };
}


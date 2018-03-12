#include "stdafx.h"
#include "WordType.h"
#include "UnsupportedTypeException.h"

namespace lib
{
    map<Type, string> WordType::_typeMap =
    {
        { Verb, "Verb (v.)" },
        { Noun, "Noun (n.)" },
        { Adverb, "Adverb (adv.)" },
        { Adjective, "Adjective (adj.)" },
        { Preposition, "Preposition (prep.)" },
        { ProperNoun, "ProperNoun (pn." },
        { NounAndVerb, "NounAndVerb (n. v.)" },
        { Misc, "MiscWords (misc.)" }
    };

    string WordType::getName(const Type& type)
    {
        const auto it = _typeMap.find(type);

        if (it == _typeMap.end())
            throw UnsupportedTypeException(to_string(type));
            
        return it->second;
    }
}

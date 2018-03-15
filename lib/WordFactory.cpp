#include "stdafx.h"
#include "EmptyStringException.h"
#include "WordFactory.h"
#include <memory>

using namespace std;
using namespace lib;

shared_ptr<Word> WordFactory::build(const string& word, const string& type, const string& definition, IPrint& printer)
{
    if (word.empty())
        throw EmptyStringException("Word");
    if (type.empty())
        throw EmptyStringException("Type");
    if (definition.empty())
        throw EmptyStringException("Definition");

    return make_shared<Word>(Word(word, type, definition, printer));
}

#include "stdafx.h"
#include "Dictionary.h"
#include "../cli/Logger.h"

using namespace cli;

/**
 * \brief Constructs the Dictionary. Responsible for loading entries from a source dictionary. Using dependency injection to decouple
 * implementation details of loading and extracting.
 * \param loader Implementation of ILoad, responsible for loading dictionary entries from a source.
 * \param extractor Implementation of IExtract, responsible for extracting values from the source dictionary.
 */
Dictionary::Dictionary(ILoad& loader, IExtract& extractor) : _loader(loader), _extractor(extractor)
{
}

/**
 * \brief Loads dictionary entries from a source. Depends on ILoad and IExtract to load and extract the contents from the source.
 */
void Dictionary::loadDictionary()
{
    auto& content = _loader.load();
    _dictionary = _extractor.extract(content);
    _loader.dispose();
}

string Dictionary::getDefinition(const string& word)
{
    const auto it = _dictionary.find(word);

    if (it == _dictionary.end())
        return "Word " + word + " not found";

    return it->second.printDefinition();
}

int Dictionary::size() const
{
    return _dictionary.size();
}

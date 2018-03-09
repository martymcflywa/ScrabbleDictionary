#include "stdafx.h"
#include "Dictionary.h"
#include <regex>

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
 * \returns map<string, Word> populated with entries from the source dictionary.
 */
map<string, Word> Dictionary::loadDictionary() const
{
    auto& content = _loader.load();
    return _extractor.extract(content);
}

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
 * \brief Load dictionary entries from a source. Depends on ILoad to retrieve the contents from the source.
 * The function then iterates over each line, using regex to extract words, types and definitions.
 * The currentLine counter and isEndOfEntry() is used to group together entries which extend over multiple lines.
 * \param location The location of the dictionary source. Can be a filepath, db connection string etc. It depends on the injected ILoad.
 * \returns The dictionary as map<string, Word> where the key is the actual word itself, and the value is the Word object.
 */
map<string, Word> Dictionary::loadDictionary(const string& location) const
{
    auto& content = _loader.load(location);
    return _extractor.extract(content);
}

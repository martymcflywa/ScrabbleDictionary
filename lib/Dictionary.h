#pragma once
#include <map>
#include <regex>
#include "Word.h"
#include "ILoad.h"
#include "IExtract.h"

using namespace std;
using namespace lib;

namespace lib {

    /**
     * \brief A collection of Word objects loaded from a source (ie. text file).
     */
    class Dictionary
    {
        ILoad& _loader;
        IExtract& _extractor;

    public:
        /**
         * \brief Constructs the Dictionary. Requires injection of ILoad and IPrint.
         * \param loader the implementation of ILoad, responsible for loading dictionary entries from a source.
         * \param extractor the implementation of IExtract, responsible for extracting values from the source dictionary.
         */
        Dictionary(ILoad& loader, IExtract& extractor);
        /**
         * \brief Load dictionary entries from a source. Not concerned with what the source is, it is abstracted away into ILoad.
         * \param location The location of the dictionary source. Can be a filepath, db connection string etc.
         * The requirement depends on ILoad implementation.
         * \returns The dictionary as map<string, Word> where the key is the actual word itself, and the value is the Word object.
         */
        map<string, Word> loadDictionary(const string& location) const;
    };
}

#pragma once
#include <memory>
#include <list>
#include "../lib/Word.h"

class TestHelpers
{
public:
    /**
     * \brief Returns true if list of strings contains word.
     * \param list The list to search.
     * \param target The word to search for.
     * \returns True if the list contains the word.
     */
    static bool listContainsWord(std::list<std::string> list, const std::string& target);
    /**
     * \brief Overload which searches list of std::shared_ptr<lib::Word>
     * \param list The list to search.
     * \param target The word to search for.
     * \returns True if the list contains the word. 
     */
    static bool listContainsWord(std::list<std::shared_ptr<lib::Word>> list, const std::string& target);
    /**
    * \brief Test helper to compare smart ptr managed object equality,
    * see https://stackoverflow.com/a/38391135. Overload for shared_ptr.
    * \tparam TExpected Expected type.
    * \tparam TActual Actual type.
    * \param expected The expected shared_ptr.
    * \param actual The actual shared_ptr.
    * \returns True if both expected and actual share the same address or
    * both expected and actual objects are the same
    */
    template<class TExpected, class TActual>
    static bool isSmartPtrEqual(const std::shared_ptr<TExpected> expected, const std::shared_ptr<TActual> actual);
    /**
    * \brief Test helper to compare smart ptr managed object equality,
    * see https://stackoverflow.com/a/38391135. Overload for unique_ptr.
    * \tparam TExpected Expected type.
    * \tparam TActual Actual type.
    * \param expected The expected unique_ptr.
    * \param actual The actual unique_ptr.
    * \returns True if both expected and actual share the same address or
    * both expected and actual objects are the same
    */
    template<class TExpected, class TActual>
    static bool isSmartPtrEqual(const std::unique_ptr<TExpected> expected, const std::unique_ptr<TActual> actual);
};

inline bool TestHelpers::listContainsWord(std::list<std::string> list, const std::string& target)
{
    return find(list.begin(), list.end(), target) != list.end();
}

inline bool TestHelpers::listContainsWord(std::list<std::shared_ptr<lib::Word>> list, const std::string& target)
{
    for (const auto word : list)
    {
        if (word->getWord() == target)
            return true;
    }
    return false;
}

template <class TExpected, class TActual>
bool TestHelpers::isSmartPtrEqual(const std::shared_ptr<TExpected> expected, const std::shared_ptr<TActual> actual)
{
    if (expected == actual)
        return true;
    if (expected && actual)
        return *expected == *actual;
    return false;
}

template <class TExpected, class TActual>
bool TestHelpers::isSmartPtrEqual(const std::unique_ptr<TExpected> expected, const std::unique_ptr<TActual> actual)
{
    if (expected == actual)
        return true;
    if (expected && actual)
        return *expected == *actual;
    return false;
}
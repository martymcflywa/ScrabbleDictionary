#pragma once
#include <map>
#include "Word.h"
#include "ILoader.h"
#include <regex>

using namespace std;
using namespace lib;

namespace lib {
    class Dictionary
    {
        ILoader& _loader;
		IPrinter& _printer;
	    bool isEndOfEntry(string line) const;
		string extractWord(string line) const;
		string extractType(string line) const;
		string extractDefinition(string line) const;
		string extract(string pattern, string line, int groupIndex) const;
		Word buildWord(string word, string type, string definition) const;

		const string HEADER_PATTERN = "^(\\S+) \\[(\\w+)\\]";
		const string DEFINITION_PATTERN = "^.*";
		const string END_OF_ENTRY_PATTERN = "^\\s*$";
    public:
        Dictionary(ILoader& loader, IPrinter& printer);
        map<string, Word> loadDictionary(const string& filepath) const;
    };
}

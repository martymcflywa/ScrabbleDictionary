#include "stdafx.h"
#include "Dictionary.h"
#include <regex>

bool Dictionary::isEndOfEntry(const string line) const
{
	const regex pattern(END_OF_ENTRY_PATTERN, regex_constants::ECMAScript);
	smatch match;
	regex_match(line, match, pattern);

	return !match.empty();
}

string Dictionary::extractWord(const string line) const
{
	const auto groupIndex = 1;
	return extract(HEADER_PATTERN, line, groupIndex);
}

string Dictionary::extractType(string line) const
{
	const auto groupIndex = 2;
	return extract(HEADER_PATTERN, line, groupIndex);
}

string Dictionary::extractDefinition(const string line) const
{
	const auto groupIndex = 0;
	return extract(DEFINITION_PATTERN, line, groupIndex);
}

string Dictionary::extract(string pattern, const string line, const int groupIndex) const
{
	const regex regex(pattern, regex_constants::ECMAScript);
	smatch match;
	regex_match(line, match, regex);

	if (match.empty())
		return "";

	return match[groupIndex];
}

Word Dictionary::buildWord(string word, string type, string definition) const
{
	if (word.empty())
		throw invalid_argument("Word is empty");
	if (type.empty())
		throw invalid_argument("Type is empty");
	if (definition.empty())
		throw invalid_argument("Definition is empty");

	return Word(word, type, definition, _printer);
}


Dictionary::Dictionary(ILoader& loader, IPrinter& printer): _loader(loader), _printer(printer)
{
}

map<string, Word> Dictionary::loadDictionary(const string& filepath) const
{
    auto& content = _loader.load(filepath);
    string line;
    auto output = map<string, Word>();

	auto currentLine = 0;
	string word;
	string type;
	string definition;

    while(getline(content, line))
    {
		if (isEndOfEntry(line))
		{
			output.insert(pair<string, Word>(word, buildWord(word, type, definition)));
			currentLine = 0;
			continue;
		}

		if (currentLine == 0)
		{
			word = extractWord(line);
			type = extractType(line);
			currentLine++;
			continue;
		}
		
		definition = extractDefinition(line);
		currentLine++;
    }
    return output;
}

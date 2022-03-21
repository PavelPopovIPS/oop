#include "./dicfns.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

void DeleteUnusefulSymbols(std::string& key)
{
	const std::string DELETE_SYMBOLS = "[],";
	size_t found = key.find_first_of(DELETE_SYMBOLS);
	while (found != std::string::npos)
	{
		key.erase(found, 1);
		found = key.find_first_of(DELETE_SYMBOLS);
	}
}

std::string DeleteSpaces(std::string& string)
{
	std::istringstream strm(string);
	std::string word;
	std::string newLine;
	bool isMulti = false;

	while (strm >> word)
	{
		if (isMulti)
		{
			newLine.append(" ");
		}

		newLine.append(word);
		isMulti = true;
	}

	return newLine;
}

std::map<std::string, std::string> InitDictionary(std::string dicFileName)
{
	std::ifstream inputFileStream(dicFileName);

	std::string line;
	std::map<std::string, std::string> dictionary;

	while (std::getline(inputFileStream, line))
	{
		std::string key;
		std::string value;
		std::string translate;

		std::istringstream strm(line);
		strm >> key;

		if (key == "")
		{
			continue;
		}

		DeleteUnusefulSymbols(key);

		bool isMulti = false;
		while (strm >> value)
		{
			if (isMulti)
			{
				translate.append(", ");
			}

			DeleteUnusefulSymbols(value);
			translate.append(value);
			isMulti = true;
		}

		dictionary.insert(std::make_pair(key, translate));
	}

	inputFileStream.close();

	return dictionary;
}

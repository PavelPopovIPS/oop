#include "./dicfns.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

void DeleteBrackets(std::string& key)
{
	const std::string DELETE_SYMBOLS = "[]";
	size_t found = key.find_first_of(DELETE_SYMBOLS);
	while (found != std::string::npos)
	{
		key.erase(found, 1);
		found = key.find_first_of(DELETE_SYMBOLS);
	}
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

		DeleteBrackets(key);

		while (strm >> value)
		{
			translate.append(value);
			translate.append(" ");
		}

		dictionary.insert(std::make_pair(key, translate));
	}

	inputFileStream.close();

	return dictionary;
}

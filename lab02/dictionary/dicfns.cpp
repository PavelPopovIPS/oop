#include "./dicfns.h"

#include <fstream>
#include <map>
#include <sstream>
#include <string>

std::map<std::string, std::string> InitDictionary(std::fstream dictionaryStream)
{
	std::string line;
	std::map<std::string, std::string> dictionary;

	while (std::getline(dictionaryStream, line))
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

		while (strm >> value)
		{
			translate.append(value);
			translate.append(" ");
		}
	}

	return dictionary;
}

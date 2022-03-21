#include "./dicfns.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

std::string DeleteBrackets(std::string key)
{
	const std::string DELETE_SYMBOLS = "[]";

	size_t found = key.find_first_of(DELETE_SYMBOLS);
	while (found != std::string::npos)
	{
		key.erase(found, 1);
		found = key.find_first_of(DELETE_SYMBOLS);
	}

	return key;
}

std::string CutSpaces(const std::string& string)
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

std::string ConvertTextToLowCase(std::string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] >= 'A' && text[i] <= 'Z')
		{
			text[i] += 'z' - 'Z';
		}
	}

	return text;
}

std::pair<std::string, std::string> ParseLine(const std::string& line)
{
	std::pair<std::string, std::string> translateUnit;
	size_t begin = 0;

	size_t found = line.find("]");
	++found; //перевожу позицию в количество символов и в номер следующего элемента
	std::string key = line.substr(begin, found);
	std::string translate = line.substr(found);

	key = DeleteBrackets(key);
	translate = CutSpaces(translate);
	// std::cout << key << " -> " << translate << std::endl;

	translateUnit = std::make_pair(key, translate);
	return translateUnit;
}

std::map<std::string, std::string> InitDictionary(const std::string& dicFileName)
{
	std::map<std::string, std::string> dictionary;
	std::ifstream inputFileStream(dicFileName);

	if (!inputFileStream.is_open())
	{
		return dictionary;
	}

	std::string line;
	while (std::getline(inputFileStream, line))
	{
		if (line == "")
		{
			continue;
		}

		std::pair<std::string, std::string> translateUnit = ParseLine(line);

		dictionary.insert(translateUnit);
	}

	if (inputFileStream.bad())
	{
		throw std::runtime_error("Failed to read data from file\n");
	}

	inputFileStream.close();

	return dictionary;
}

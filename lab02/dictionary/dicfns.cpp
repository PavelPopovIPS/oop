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

std::string CutSpaces(const std::string& str)
{
	std::istringstream strm(str);
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

		if (text[i] >= 'А' && text[i] <= 'Я')
		{
			text[i] += 'я' - 'Я';
		}
	}

	return text;
}

std::pair<std::string, std::string> CreateTranslationUnit(const std::string& key, const std::string& translation)
{
	return std::make_pair(key, translation);
}

std::pair<std::string, std::string> ParseLine(const std::string& line)
{
	std::pair<std::string, std::string> translateUnit;
	size_t begin = 0;

	size_t found = line.find("]");
	++found; //перевожу позицию в количество символов и в номер следующего элемента
	std::string key = line.substr(begin, found);
	std::string translation = line.substr(found);

	key = DeleteBrackets(CutSpaces(key));
	translation = CutSpaces(translation);

	return CreateTranslationUnit(key, translation);
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

		std::pair<std::string, std::string> translationUnit = ParseLine(line);

		dictionary.insert(translationUnit);
	}

	if (inputFileStream.bad())
	{
		throw std::runtime_error("Failed to read data from file\n");
	}

	inputFileStream.close();

	return dictionary;
}

bool IsTranslationExisting(const std::map<std::string, std::string>& dictionary, const std::string& key)
{
	if (dictionary.find(key) != dictionary.end())
	{
		return true;
	}
	return false;
}

void PrintTranslation(std::map<std::string, std::string>& dictionary, const std::string& key)
{
	std::cout << dictionary[key] << std::endl;
}

void AddNewTranslation(std::map<std::string, std::string>& dictionary,
	const std::string& key,
	const std::string& originalText)
{
	std::cout << "Неизвестное слово \"" + originalText + "\". Введите перевод или пустую строку для отказа."
			  << std::endl;

	std::pair<std::string, std::string> translationUnit;
	std::string translation;
	getline(std::cin, translation);

	if (translation != "")
	{
		translationUnit = CreateTranslationUnit(key, translation);
		dictionary.insert(translationUnit);

		std::string oppositeKey = ConvertTextToLowCase(CutSpaces(translation));

		if (IsTranslationExisting(dictionary, oppositeKey))
		{
			dictionary[oppositeKey].append(", " + originalText);
		}
		else
		{
			translationUnit = CreateTranslationUnit(oppositeKey, originalText);
			dictionary.insert(translationUnit);
		}
		std::cout << "Слово \"" + originalText + "\" сохранено в словаре как \"" + translation + "\"" << std::endl;
	}
	else
	{
		std::cout << "Слово \"" + originalText + "\" проигнорировано." << std::endl;
	}
}

void SaveDictionaryToFile(const std::map<std::string, std::string>& dictionary, const std::string& dicFileName)
{
	std::ofstream outputFile(dicFileName);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("File " + dicFileName + " was not opened for writining\n");
	}

	for (auto& translationUnit : dictionary)
	{
		outputFile << "[" + translationUnit.first + "] " + translationUnit.second << std::endl;
	}

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to write to file\n");
	}

	outputFile.close();
}

void Exit(const std::map<std::string, std::string>& dictionary, size_t originalSize, const std::string& dicFileName)
{
	if (dictionary.size() != originalSize)
	{
		std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;

		std::string answer;
		getline(std::cin, answer);
		answer = ConvertTextToLowCase(CutSpaces(answer));

		if (answer == "y")
		{
			SaveDictionaryToFile(dictionary, dicFileName);
			std::cout << "Изменения сохранены. ";
		}
		else
		{
			std::cout << "Все что было нажито непосильным трудом безвозвратно потеряно. ";
		}
	}
	std::cout << "До свидания." << std::endl;
}

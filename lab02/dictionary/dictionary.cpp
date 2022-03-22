// dictionary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "./dicfns.h"
#include <iostream>
#include <map>
#include <string>
#include <windows.h>

struct Args
{
	std::string dicFileName;
};

const std::string EXIT = "...";

Args ParseArgs(int argv, char* argc[])
{
	if (argv != 2)
	{
		throw std::runtime_error("Invalid argument count\nFor use: dictionary.exe <dictionary file name>\n");
	}

	Args args;
	args.dicFileName = argc[1];
	if (args.dicFileName == "")
	{
		throw std::runtime_error("Dictionary file name can not be empty\n");
	}

	return args;
}

void PrintMap(std::map<std::string, std::string> dictionary)
{
	for (auto& item : dictionary)
	{
		std::cout << "[" << item.first << "] " << item.second << std::endl;
	}
}

int main(int argv, char* argc[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	try
	{
		Args args = ParseArgs(argv, argc);
		std::map<std::string, std::string> dictionary = InitDictionary(args.dicFileName);

		std::string originalLine;
		std::string lineWithoutSpaces;
		while (getline(std::cin, originalLine))
		{
			lineWithoutSpaces = ConvertTextToLowCase(CutSpaces(originalLine));
			std::string key = ConvertTextToLowCase(lineWithoutSpaces);

			if (key == EXIT)
			{
				std::cout << "До свидания." << std::endl;
				break;
			}

			if (IsTranslationExisting(dictionary, key))
			{
				PrintTranslation(dictionary, key);
			}
			else
			{
				AddNewTranslation(dictionary, key, originalLine);
			}
		}

		// PrintMap(dictionary);
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}

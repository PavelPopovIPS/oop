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

		std::string line;
		// while (getline(std::cin, line))
		//{
		//	std::string key = DeleteSpaces(line);

		//	std::cout << dictionary[key] << std::endl;
		//}

		PrintMap(dictionary);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}

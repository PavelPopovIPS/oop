// findText.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string fileName;
	std::string textToSearch;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: findText.exe <file name> <text to search>\n";
		return std::nullopt;
	}
	Args args;
	args.fileName = argv[1];
	args.textToSearch = argv[2];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	//Проверяем необходимое количество аргументов
	if (!args)
	{
		return 1;
	}

	// Открываем файл для чтения
	std::ifstream fileName;
	fileName.open(args->fileName);

	if (!fileName.is_open())
	{
		std::cout << "File " << args->fileName << " was not opened for reading\n";
		return 1;
	}

	if (fileName.bad())
	{
		std::cout << "Failed to read data from file\n";
		return 1;
	}

	return 0;
}

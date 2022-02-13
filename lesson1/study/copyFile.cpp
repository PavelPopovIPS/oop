// copyFile.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: CopyFile.exe <input file name> <output file name>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

void CopyStream(std::istream& input, std::ostream& output)
{
	// Копируем содержимое файла
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			break;
		}
	}
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
	std::ifstream input;
	input.open(args->inputFileName);

	if (!input.is_open())
	{
		std::cout << "File " << args->inputFileName << " was not opened for reading\n";
		return 1;
	}

	// Открываем файл для чтения
	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "File " << args->outputFileName << " was not opened for writining\n";
		return 1;
	}

	CopyStream(input, output);

	if (input.bad())
	{
		std::cout << "Failed to read data from file\n";
		return 1;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write to file\n";
		return 1;
	}

	return 0;
}

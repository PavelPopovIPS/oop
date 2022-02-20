// replace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>

struct Args
{
	std::string inputFile;
	std::string outputFile;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "replace.exe <input file> <output file> <search string> <replace string>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFile = argv[1];
	args.outputFile = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];

	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(args->inputFile);

	if (!inputFile.is_open())
	{
		std::cout << "File " << args->inputFile << " was not opened for reading\n";
		return 1;
	}

	std::ofstream outputFile;
	outputFile.open(args->outputFile);
	if (!outputFile.is_open())
	{
		std::cout << "File " << args->outputFile << " was not opened for writing\n";
		return 1;
	}

	if (inputFile.bad())
	{
		std::cout << "Failed to read data from file\n";
		return 1;
	}

	if (!outputFile.flush())
	{
		std::cout << "Failed to write to file from buffer\n";
		return 1;
	}

	return 0;
}

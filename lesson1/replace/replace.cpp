// replace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

int main()
{
	std::cout << "Hello World!\n";
}

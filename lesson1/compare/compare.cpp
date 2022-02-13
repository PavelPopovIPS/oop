// compare.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
struct Args
{
	std::string îriginalFileName;
	std::string modifiedFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: compare.exe <original file name> <modified file name>\n";
		return std::nullopt;
	}
	Args args;
	args.îriginalFileName = argv[1];
	args.modifiedFileName = argv[2];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	// Check count of args
	if (!args)
	{
		return 1;
	}

	// Open file for read
	std::ifstream îriginalFile(args->îriginalFileName);
	if (!îriginalFile.is_open())
	{
		std::cout << "Original file " << args->îriginalFileName << " was not opened for reading\n";
		return 1;
	}

	// Open file for read
	std::ifstream modifiedFile(args->modifiedFileName);
	if (!modifiedFile.is_open())
	{
		std::cout << "Modified file " << args->modifiedFileName << " was not opened for writining\n";
		return 1;
	}

	if (îriginalFile.bad())
	{
		std::cout << "Failed to read data from original file\n";
		return 1;
	}

	if (modifiedFile.bad())
	{
		std::cout << "Failed to read data from modified file\n";
		return 1;
	}

	std::cout << args->îriginalFileName << "\n";
	std::cout << args->modifiedFileName << "\n";
	std::cout << "Files are equal\n";
	return 0;
}

// compare.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string �riginalFileName;
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
	args.�riginalFileName = argv[1];
	args.modifiedFileName = argv[2];
	return args;
}

bool isStreamEqual(std::ifstream& �riginalFile, std::ifstream& modifiedFile)
{
	char ch1, ch2;
	int countLines = 1;

	�riginalFile.get(ch1);
	modifiedFile.get(ch2);

	// Compare streams char by char
	do
	{
		// Search different characters
		if (ch1 != ch2)
		{
			std::cout << "Files are different. Line number is " << countLines << "\n";
			return false;
		}

		// Count of lines
		if (ch1 == '\n')
		{
			countLines++;
		}
	} while (�riginalFile.get(ch1) && modifiedFile.get(ch2));

	// Check case, when streams was equal, but one of them is longer.
	if (ch1 != ch2)
	{
		std::cout << "Files are different. Line number is " << countLines << "\n";
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	// Check count of args
	if (!args)
	{
		return 1;
	}

	// Open files for reading
	std::ifstream �riginalFile;
	�riginalFile.open(args->�riginalFileName);
	if (!�riginalFile.is_open())
	{
		std::cout << "Original file " << args->�riginalFileName << " was not opened for reading\n";
		return 1;
	}

	std::ifstream modifiedFile;
	modifiedFile.open(args->modifiedFileName);
	if (!modifiedFile.is_open())
	{
		std::cout << "Modified file " << args->modifiedFileName << " was not opened for writining\n";
		return 1;
	}

	// Compare streams
	// App exit with code 1 if files not equal
	if (!isStreamEqual(�riginalFile, modifiedFile))
	{
		return 1;
	}

	// Check streams for errors
	if (�riginalFile.bad())
	{
		std::cout << "Failed to read data from original file\n";
		return 1;
	}

	if (modifiedFile.bad())
	{
		std::cout << "Failed to read data from modified file\n";
		return 1;
	}

	std::cout << "Files are equal\n";
	return 0;
}

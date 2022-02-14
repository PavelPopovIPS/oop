// compare.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

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

bool IsStreamsEqual(std::ifstream& îriginalFile, std::ifstream& modifiedFile)
{
	char ch1, ch2;
	int countLines = 1;

	îriginalFile.get(ch1);
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
	} while (îriginalFile.get(ch1) && modifiedFile.get(ch2));

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
	std::ifstream îriginalFile;
	îriginalFile.open(args->îriginalFileName);
	if (!îriginalFile.is_open())
	{
		std::cout << "Original file " << args->îriginalFileName << " was not opened for reading\n";
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
	// Exit with code 1 if files not equal
	if (!IsStreamsEqual(îriginalFile, modifiedFile))
	{
		return 1;
	}

	// Check streams for errors
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

	std::cout << "Files are equal\n";
	return 0;
}

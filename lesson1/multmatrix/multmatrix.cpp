// multmatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>

struct Args
{
	std::string fileMatrixFirst;
	std::string fileMatrixSecond;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: multmatrix.exe <matrix file1> <matrix file2>\n";
		return std::nullopt;
	}
	Args args;
	args.fileMatrixFirst = argv[1];
	args.fileMatrixSecond = argv[2];

	if (args.fileMatrixFirst == "" || args.fileMatrixSecond == "")
	{
		std::cout << "File name should not be empty";
		return std::nullopt;
	}

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

	// Open files for reading
	std::ifstream fileMatrixFirst;
	fileMatrixFirst.open(args->fileMatrixFirst);
	if (!fileMatrixFirst.is_open())
	{
		std::cout << "File " << args->fileMatrixFirst << " was not opened for reading\n";
		return 1;
	}

	std::ifstream fileMatrixSecond;
	fileMatrixSecond.open(args->fileMatrixSecond);
	if (!fileMatrixSecond.is_open())
	{
		std::cout << "File " << args->fileMatrixSecond << " was not opened for reading\n";
		return 1;
	}
}

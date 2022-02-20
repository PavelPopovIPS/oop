// calcbits.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <optional>
#include <string>

struct Args
{
	unsigned byte;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "replace.exe <input file> <output file> <search string> <replace string>\n";
		return std::nullopt;
	}
	Args args;

	try
	{
		if (std::stoi(argv[1]) < 0)
		{
			std::cout << "Number should be great then zero\n";
			return std::nullopt;
		}
		args.byte = static_cast<unsigned>(std::stoi(argv[1]));
	}
	catch (std::invalid_argument e)
	{
		std::cout << "You should use number\n";
		return std::nullopt;
	}
	return args;
}

int Bitcount(unsigned x)
{
	int b;
	for (b = 0; x != 0; x >>= 1)
	{
		if (x & 1)
		{
			++b;
		}
	}
	return b;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::cout << Bitcount(args->byte) << std::endl;

	return 0;
}

// flipbyte.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <bitset>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	unsigned char byte;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "rotatebyte.exe <byte>\n";
		return std::nullopt;
	}

	Args args;

	// Initialize argument
	try
	{
		int byte = std::stoi(argv[1]);
		if (byte < 0 || byte > 255)
		{
			std::cout << "Argument should be greater than zero or equal zero and less than 256\n";
			return std::nullopt;
		}
		args.byte = static_cast<unsigned char>(byte);
	}
	catch (std::invalid_argument e)
	{
		std::cout << "First argument should be number\n";
		return std::nullopt;
	}

	return args;
}

void FlipByte(unsigned char& byte)
{
	std::bitset<8> bitset1(byte);
	std::cout << bitset1 << std::endl;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}
	FlipByte(args->byte);
	// std::cout << int(args->byte) << std::endl;

	return 0;
}

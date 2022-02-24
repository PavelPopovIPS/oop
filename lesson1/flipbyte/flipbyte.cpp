// flipbyte.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <optional>
#include <string>

enum class Error
{
	InvalidArgumentCount,
	ArgumentInitialize,
	ArgumentNotNumber,
};

struct Args
{
	unsigned int byte;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw Error::InvalidArgumentCount;
		return std::nullopt;
	}

	Args args;

	try
	{
		int byte = std::stoi(argv[1]);
		if (byte < 0 || byte > 255)
		{
			throw Error::ArgumentInitialize;
			return std::nullopt;
		}
		args.byte = static_cast<unsigned int>(byte);
		return args;
	}
	catch (std::invalid_argument e)
	{
		throw Error::ArgumentNotNumber;
		return std::nullopt;
	}
}

void PrintError(Error error)
{
	switch (error)
	{
	case Error::InvalidArgumentCount: {
		std::cout << "Invalid argument count\n";
		std::cout << "For use: rotatebyte.exe <byte>\n";
		break;
	}
	case Error::ArgumentInitialize: {
		std::cout << "Argument should be greater than zero or equal zero and less than 256\n";
		break;
	}
	case Error::ArgumentNotNumber: {
		std::cout << "First argument should be number\n";
		break;
	}
	}
}

unsigned int FlipByte(unsigned int& byte)
// byte is 87654321
{
	// Разделил бит на половинки и поменял их местами
	// left is  43210000
	// right is 00008765
	unsigned int left = byte << 4;
	left &= 240; // 240 - маска в двоичной системе 11110000
	unsigned int right = byte >> 4;

	// byte is 43218765
	byte = left | right;

	// left is  21006500
	// right is 00430087
	left = byte << 2;
	left &= 204; // 11001100
	right = byte >> 2;
	right &= 51; // 00110011

	// byte is 21436587
	byte = left | right;

	// left is  10305070
	// right is 02040608
	left = byte << 1;
	left &= 170; // 10101010
	right = byte >> 1;
	right &= 85; // 01010101

	// byte is 12345678
	byte = left | right;

	return byte;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		std::cout << FlipByte(args->byte) << std::endl;
	}
	catch (Error error)
	{
		PrintError(error);
		return 1;
	}

	return 0;
}

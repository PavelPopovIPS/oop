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
	}
	catch (std::invalid_argument e)
	{
		throw Error::ArgumentNotNumber;
		return std::nullopt;
	}

	return args;
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

unsigned int FlipByte(const unsigned int& byte)
// byte is 87654321
{
	// Разделил бит на половинки и поменял их местами
	// left is  43210000
	// right is 00008765
	unsigned int left = byte << 4;
	left &= 240; // 240 - маска в двоичной системе 11110000
	unsigned int right = byte >> 4;

	//Разделил левую половину на четверти и поменял их местами
	// left1 is 21000000
	// left2 is 00430000
	unsigned char left1 = left << 2;
	unsigned char left2 = left >> 2;
	left2 &= 48; // 48 - маска в двоичной системе 00110000

	// Поменял местами биты в четвертях левой половинки
	// left1 is 12000000
	// left2 is 00340000
	left1 = (left1 << 1) | ((left1 >> 1) & 64);
	left2 = ((left2 << 1) & 32) | ((left2 >> 1) & 16);

	// Склеил левые четвертинки
	left = left1 | left2;

	//Разделил правую половину на четверти и поменял их местами
	// right1 is 00006500
	// right2 is 00000087
	unsigned char right1 = right << 2;
	right1 &= 12; // 12 - маска в двоичной системе 00001100
	unsigned char right2 = right >> 2;

	// Поменял местами биты в четвертях правой половинки
	// right1 is 00005600
	// right2 is 00000078
	right1 = ((right1 << 1) & 8) | ((right1 >> 1) & 4);
	right2 = ((right2 << 1) & 2) | (right2 >> 1);

	// Склеил правые четвертинки
	right = right1 | right2; // debug

	// Склеил половинки и вернул байт
	return left | right;
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

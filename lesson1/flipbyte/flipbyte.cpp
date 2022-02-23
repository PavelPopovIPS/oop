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

unsigned int FlipByte(const unsigned char& byte)
{
	// byte is 87654321

	unsigned int newByte;

	// Распечатал полученный байт // debug
	std::bitset<8> bitset1{ byte }; // debug
	std::cout << bitset1 << std::endl; // debug

	// Разделил бит на половинки и поменял их местами
	// left is  43210000
	// right is 00008765
	unsigned char left = byte << 4;
	unsigned char right = byte >> 4;

	// Склеил половинки // debug
	newByte = left | right; // debug
	// Распечатал склеенные половинки
	std::bitset<8> bitset6{ newByte }; // debug
	std::cout << "change 1/2 " << bitset6 << std::endl; // debug

	//Разделил левую половину на четверти и поменял их местами
	// left1 is 21000000
	// left2 is 00430000
	unsigned char left1 = left << 2;
	unsigned char left2 = left >> 2;
	left2 &= 48; // 48 - маска в двоичной системе 00110000

	// Поменял местами биты в четвертях
	// left1 is 12000000
	// left2 is 00340000
	left1 = (left1 << 1) | ((left1 >> 1) & 64);
	left2 = ((left2 << 1) & 32) | ((left2 >> 1) & 16);

	// Склеил левые четвертинки
	left = left1 | left2; // debug
	std::bitset<8> bitset4{ left }; // debug
	std::cout << bitset4 << std::endl; // debug

	//Разделил правую половину на четверти и поменял их местами
	// right1 is 00006500
	// right2 is 00000087
	unsigned char right1 = right << 2;
	right1 &= 12; // 12 - маска в двоичной системе 00001100
	unsigned char right2 = right >> 2;

	// Поменял местами биты в четвертях
	// right1 is 00005600
	// right2 is 00000078
	right1 = (right1 << 1) & 8 | ((right1 >> 1) & 4);
	right2 = ((right2 << 1) & 2) | (right2 >> 1);

	// Склеил правые четвертинки
	right = right1 | right2; // debug
	std::bitset<8> bitset5{ right }; // debug
	std::cout << bitset5 << std::endl; // debug

	// Склеил половинки и распечатал
	newByte = left | right; // debug
	std::bitset<8> bitset7{ newByte }; // debug
	std::cout << "change 1/4 " << bitset7 << std::endl; // debug

	return newByte;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	unsigned int newByte = FlipByte(args->byte);

	std::cout << newByte << std::endl;

	return 0;
}

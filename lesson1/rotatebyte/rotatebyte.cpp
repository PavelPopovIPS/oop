// rotatebyte.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <optional>
#include <string>

enum class Direction
{
	Left,
	Right
};

struct Args
{
	unsigned char byte;
	unsigned int numberBits;
	Direction direction;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "rotatebyte.exe <byte> <number of bits> <L / R>\n";
		return std::nullopt;
	}

	Args args;

	// Initialize first argument
	try
	{
		if (std::stoi(argv[1]) < 0 || std::stoi(argv[1]) > 255)
		{
			std::cout << "First argument should be greater than zero or equal zero and less than 256\n";
			return std::nullopt;
		}
		args.byte = static_cast<unsigned char>(std::stoi(argv[1]));
	}
	catch (std::invalid_argument e)
	{
		std::cout << "First argument should be number\n";
		return std::nullopt;
	}

	// Initialize second argument
	try
	{
		if (std::stoi(argv[2]) < 0)
		{
			std::cout << "Second argument should be greater then zero or equal\n";
			return std::nullopt;
		}
		args.numberBits = static_cast<unsigned int>(std::stoi(argv[2]));
	}
	catch (std::invalid_argument e)
	{
		std::cout << "You should use number\n";
		return std::nullopt;
	}

	// Initialize third argument
	std::string direction = static_cast<std::string>(argv[3]);
	if (direction == "L")
	{
		args.direction = Direction::Left;
	}
	else if (direction == "R")
	{
		args.direction = Direction::Right;
	}
	else
	{
		std::cout << "You should use L for left and R for right direction\n";
		return std::nullopt;
	}

	return args;
}

unsigned int RotateByte(const unsigned char& byte, unsigned int& numberBits, const Direction& direction)
{
	unsigned char left;
	unsigned char right;
	unsigned int newByte;

	// Сonvert numberBits to one range
	if (numberBits > 8)
	{
		numberBits %= 8;
	}

	switch (direction)
	{
	case Direction::Left: {
		left = byte << numberBits;
		right = byte >> (8 - numberBits);
		newByte = left | right;
		return newByte;
	}
	case Direction::Right: {
		left = byte >> numberBits;
		right = byte << (8 - numberBits);
		newByte = left | right;
		return newByte;
	}
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	unsigned int byte = RotateByte(args->byte, args->numberBits, args->direction);

	std::cout << byte << std::endl;

	return 0;
}

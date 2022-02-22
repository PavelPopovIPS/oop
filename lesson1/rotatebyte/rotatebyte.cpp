// rotatebyte.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <optional>
#include <string>

enum class Direction
{
	L,
	R
};

struct Args
{
	unsigned byte;
	unsigned numberBits;
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
		args.byte = static_cast<unsigned>(std::stoi(argv[1]));
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
		args.numberBits = static_cast<unsigned>(std::stoi(argv[2]));
	}
	catch (std::invalid_argument e)
	{
		std::cout << "You should use number\n";
		return std::nullopt;
	}

	// Initialize third argument
	std::string dir = static_cast<std::string>(argv[3]);
	if (dir == "L")
	{
		std::cout << dir << std::endl; // debug
		args.direction = Direction::L;
	}
	else if (dir == "R")
	{
		std::cout << dir << std::endl; // debug
		args.direction = Direction::R;
	}
	else
	{
		std::cout << "You should use L for left and R for right direction\n";
		return std::nullopt;
	}

	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::cout << args->byte << std::endl;
	std::cout << args->numberBits << std::endl;

	return 0;
}

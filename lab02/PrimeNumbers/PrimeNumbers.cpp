// PrimeNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

struct Args
{
	std::string upperBound;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::runtime_error("Invalid argument count\nFor use: PrimeNumbers.exe <upper bound>\n");
	}
	Args args;
	args.upperBound = argv[1];

	if (args.upperBound == "")
	{
		throw std::runtime_error("Number should not be empty\n");
	}

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);
		std::cout << args.upperBound << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

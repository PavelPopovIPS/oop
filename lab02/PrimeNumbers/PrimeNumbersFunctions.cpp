#include "PrimeNumbersFunctions.h"

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::runtime_error("Invalid argument count\nFor use: PrimeNumbers.exe <upper bound>\n");
	}

	Args args;
	std::string upperBoundText = argv[1];

	if (upperBoundText == "")
	{
		throw std::runtime_error("Number should not be empty\n");
	}

	try
	{
		args.upperBound = std::stoi(upperBoundText);
		if (args.upperBound < 0)
		{
			throw std::runtime_error("Number should be greater then zero\n");
		}

		return args;
	}
	catch (std::invalid_argument e)
	{
		throw std::runtime_error("Argument should be number greater then zero\n");
	}
	catch (std::out_of_range e)
	{
		throw std::runtime_error("Argument tooo big\n");
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	return std::set<int>();
}

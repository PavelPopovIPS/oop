#include "PrimeNumbersFunctions.h"

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

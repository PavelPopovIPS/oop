// PrimeNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "PrimeNumbersFunctions.h"

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);
		std::set<int> setPrimeNumbers = GeneratePrimeNumbersSet(args.upperBound);
		PrintSetSize(setPrimeNumbers);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

// PrimeNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "PrimeNumbersFunctions.h"
std::set<int>::iterator it;

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);
		std::set<int> setPrimeNumbers = GeneratePrimeNumbersSet(args.upperBound);

		/*for (it = setPrimeNumbers.begin(); it != setPrimeNumbers.end(); ++it)
		{
			std::cout << *it << std::endl;
		}*/
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

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
		if (args.upperBound < 2 || args.upperBound > 100000000)
		{
			throw std::runtime_error("Number should be greater then 1 and less then 100 000 000\n");
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
	std::set<int> setPrimeNumbers;
	std::vector<bool> numbers(upperBound, true);

	numbers[0] = numbers[1] = false;

	int p = 2;
	for (p; p < numbers.size(); ++p)
	{
		if (!numbers[p])
		{
			continue;
		}

		int n = p;
		for (n; n < numbers.size(); ++n)
		{
			if ((p * n) >= numbers.size())
			{
				break;
			}

			numbers[p * n] = false;
		}
	}

	int counter = 0;
	for (counter; counter < numbers.size(); ++counter)
	{
		if (numbers[counter])
		{
			setPrimeNumbers.insert(counter);
		}
	}

	std::cout << setPrimeNumbers.size() << std::endl;

	return setPrimeNumbers;
}

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
			throw std::runtime_error("Number should be greater then 1 and less then or equal 100 000 000\n");
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

void FindPrimeNumbers(std::vector<bool>& numbers)
{
	numbers[0] = numbers[1] = false;

	for (int i = 2; i * i < numbers.size(); ++i)
	{
		if (numbers[i])
		{
			int k = 0;
			int j = i * i + k * i;
			while (j < numbers.size())
			{
				numbers[j] = false;
				++k;
				j = i * i + k * i;
			}
		}
	}
}

void SetPrimeNumbers(std::set<int>& primeNumbersSet, const std::vector<bool>& numbers)
{
	for (int counter = 0; counter < numbers.size(); ++counter)
	{
		if (numbers[counter])
		{
			primeNumbersSet.insert(counter);
		}
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> numbers(upperBound + 1, true);
	FindPrimeNumbers(numbers);

	std::set<int> primeNumbersSet;
	SetPrimeNumbers(primeNumbersSet, numbers);

	return primeNumbersSet;
}

void PrintSet(const std::set<int>& primeNumbersSet)
{
	std::set<int>::iterator it;
	for (it = primeNumbersSet.begin(); it != primeNumbersSet.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

void PrintSetSize(const std::set<int>& primeNumbersSet)
{
	std::cout << primeNumbersSet.size() << std::endl;
}

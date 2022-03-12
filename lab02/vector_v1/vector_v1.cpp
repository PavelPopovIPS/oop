// vector_v1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string ReadInput()
{
	std::string inputStr;
	std::getline(std::cin, inputStr);

	if (inputStr.length() == 0)
	{
		throw std::runtime_error("You did not enter numbers");
	}

	return inputStr;
}

std::vector<double> ParseStringToVector(const std::string& inputStr)
{
	std::vector<double> vectr;
	std::istringstream strm(inputStr);
	for (std::string elem; std::getline(strm, elem, ' ');)
	{
		try
		{
			vectr.push_back(std::stod(elem));
		}
		catch (std::invalid_argument e) // Если принимать по ссылке, появляется варнинг
		{
			throw std::runtime_error("You should use number\n");
		}
		catch (std::out_of_range e)
		{
			throw std::runtime_error("Number is toooo big\n");
		}
	}

	return vectr;
}

double CalcPositiveElementsAverage(const std::vector<double>& vectr)
{
	double sum = 0.0;
	int count = 0;
	for (double elem : vectr)
	{
		if (elem > 0.0)
		{
			sum += elem;
			count++;
		}
	}

	if (count == 0)
	{
		throw std::runtime_error("There are no positive elements\n");
	}

	return sum / count;
}

void AddNumberToVectorElements(std::vector<double>& vectr, double positiveElementsAverage)
{
	for (int i = 0; i < vectr.size(); i++)
	{
		vectr[i] += positiveElementsAverage;
	}
}

void PrintVector(const std::vector<double>& vectr)
{
	for (double elem : vectr)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}

int main()
{
	try
	{
		std::string inputStr = ReadInput();
		std::vector<double> vectr = ParseStringToVector(inputStr);
		double positiveElementsAverage = CalcPositiveElementsAverage(vectr);
		AddNumberToVectorElements(vectr, positiveElementsAverage);
		PrintVector(vectr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}

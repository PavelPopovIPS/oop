#include "Functions.h"
#include <algorithm>
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

void AddNumberToVectorElements(std::vector<double>& vectr, double number)
{
	for (int i = 0; i < vectr.size(); i++)
	{
		vectr[i] += number;
	}
}

void PrintVector(std::vector<double>& vectr)
{
	// Сортировка элементов массива с помощью алгоритма sort и итераторов вектора
	std::sort(vectr.begin(), vectr.end());

	for (double elem : vectr)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}

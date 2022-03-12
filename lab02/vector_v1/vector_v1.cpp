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
		catch (std::invalid_argument& e)
		{
			throw std::runtime_error("You should use number\n");
		}
		catch (std::out_of_range& e)
		{
			throw std::runtime_error("Number is toooo big\n");
		}
	}

	return vectr;
}

void PrintVector(const std::vector<double>& vectr)
{
	for (double elem : vectr)
	{
		std::cout << elem << std::endl;
	}
}

int main()
{
	try
	{
		std::string inputStr = ReadInput();
		std::vector<double> vectr = ParseStringToVector(inputStr);
		PrintVector(vectr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}

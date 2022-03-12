// vector_v1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Functions.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

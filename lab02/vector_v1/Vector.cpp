// vector_v1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "VectorHandler.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
	try
	{
		std::string inputStr = ReadInput();
		std::vector<double> vectr = ParseStringToVector(inputStr);
		double positiveElementsAverage = CalcPositiveElementsAverage(vectr);
		// 1. Если передавать в параметры функцию которая выполняет необходимое поведение, можно было бы сделать код более переиспользуемым
		//  map название фуекции
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

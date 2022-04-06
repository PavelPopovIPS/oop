// PrimeNumbers_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../PrimeNumbers/PrimeNumbersFunctions.h"

SCENARIO("Тестирование ParseArgs")
{
	WHEN("передано значение верхней границы равное 10")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };
		char arg1[] = { "10" };
		char* argv[] = { arg0, arg1 };

		int argc = std::size(argv);

		THEN("аргумент корректно конвертится в число")
		{
			Args args = ParseArgs(argc, argv);

			int expectedResult = 10;

			REQUIRE(expectedResult == args.upperBound);
		}
	}
}

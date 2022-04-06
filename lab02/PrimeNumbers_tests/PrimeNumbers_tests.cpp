// PrimeNumbers_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../PrimeNumbers/PrimeNumbersFunctions.h"

SCENARIO("Тестирование ParseArgs")
{
	WHEN("передано 2 аргуметна")
	{
		const char* argv[] = { "c :\tmp\example.exe", "10" };
		int argc = std::size(argv);

		THEN("должна вернуться структура с аргументом")
		{
			std::cout << argc;
		}
	}
}

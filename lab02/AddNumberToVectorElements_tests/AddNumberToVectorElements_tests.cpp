// AddNumberToVectorElements_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN // убирает main и говорит catch запускать только этот файл. Должен быть выже include catch
#include "../../catch2/catch.hpp"
#include "../vector_v1/Functions.h"
#include <iostream>
#include <vector>

SCENARIO("Должен вернуться корректный вектор с нужными данными")
{
	std::vector<double> vectr = ParseStringToVector("12 34");
	REQUIRE(vectr[0] == 12);
	REQUIRE(vectr[1] == 34);
}

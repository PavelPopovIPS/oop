// FindMaxExFunc_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../FindMaxExFunc/Athlete.h"
#include "../FindMaxExFunc/FindMaxEx.h"

bool operator==(const Athlete& a1, const Athlete& a2)
{
	bool isName = a1.name == a2.name;
	bool isTall = a1.tall == a2.tall;
	bool isWeight = a1.weight == a2.weight;
	return (isName && isTall && isWeight);
}

TEST_CASE("Find max athlete by tall")
{
	std::vector<Athlete> athletes = {
		{ "Ivan", 180, 80 },
		{ "Elly", 161, 50 },
		{ "Paul", 170, 100 },
		{ "John", 195, 75 },
	};

	Athlete maxAthlete;

	FindMax(athletes, maxAthlete, CompareTall);
	Athlete expectedResult = { "John", 195, 75 };

	REQUIRE(maxAthlete == expectedResult);
}

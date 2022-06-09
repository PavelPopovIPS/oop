// FindMaxExFunc_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../FindMaxExFunc/Athlete.h"
#include "../FindMaxExFunc/FindMaxEx.h"

/*
bool operator==(const Athlete& a1, const Athlete& a2)
{
	bool isName = a1.name == a2.name;
	bool isTall = a1.tall == a2.tall;
	bool isWeight = a1.weight == a2.weight;
	return (isName && isTall && isWeight);
}
*/

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

TEST_CASE("Find max athlete by weight")
{
	std::vector<Athlete> athletes = {
		{ "Ivan", 180, 80 },
		{ "Elly", 161, 50 },
		{ "Paul", 170, 100 },
		{ "John", 195, 75 },
	};

	Athlete maxAthlete;
	FindMax(athletes, maxAthlete, CompareWeight);
	Athlete expectedResult = { "Paul", 170, 100 };

	REQUIRE(maxAthlete == expectedResult);
}

TEST_CASE("Search does not work in empty array")
{
	std::vector<Athlete> athletes;
	Athlete maxAthlete;
	bool result = FindMax(athletes, maxAthlete, CompareWeight);
	bool expectedResult = FALSE;

	REQUIRE(result == expectedResult);
}

TEST_CASE("Search athlete in array with one item")
{
	std::vector<Athlete> athletes = {
		{ "Ivan", 180, 80 },
	};

	Athlete maxAthlete;
	FindMax(athletes, maxAthlete, CompareWeight);

	THEN("it should be the only one")
	{
		Athlete expectedResult = { "Ivan", 180, 80 };

		REQUIRE(maxAthlete == expectedResult);
	}
}

TEST_CASE("Search among athletes of the same tall")
{
	std::vector<Athlete> athletes = {
		{ "Ivan0", 180, 80 },
		{ "Ivan1", 180, 81 },
		{ "Ivan2", 180, 82 },
		{ "Ivan3", 180, 83 },
	};

	Athlete maxAthlete;
	FindMax(athletes, maxAthlete, CompareTall);
	THEN("it should be first athlete with max tall")
	{
		Athlete expectedResult = { "Ivan0", 180, 80 };

		REQUIRE(maxAthlete == expectedResult);
	}
}

TEST_CASE("Search among athletes of the same weight")
{
	std::vector<Athlete> athletes = {
		{ "Ivan0", 180, 80 },
		{ "Ivan1", 180, 80 },
		{ "Ivan2", 180, 80 },
		{ "Ivan3", 180, 80 },
	};

	Athlete maxAthlete;
	FindMax(athletes, maxAthlete, CompareWeight);

	THEN("it should be first athlete with max weight")
	{
		Athlete expectedResult = { "Ivan0", 180, 80 };

		REQUIRE(maxAthlete == expectedResult);
	}
}

TEST_CASE("Search work with numbers by default")
{
	std::vector<int> numbers = { 1, 2, 3 };

	int number;
	FindMax(numbers, number);
	int expectedResult = 3;

	REQUIRE(number == expectedResult);
}

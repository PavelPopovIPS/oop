﻿// PrimeNumbers_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../PrimeNumbers/PrimeNumbersFunctions.h"

SCENARIO("Testing ParseArgs")
{
	WHEN("argument upperBound is 10 as text")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };
		char arg1[] = { "10" };
		char* argv[] = { arg0, arg1 };
		// явно привести к int через статик каст
		int argc = std::size(argv);

		THEN("argument should convert to number")
		{
			Args args = ParseArgs(argc, argv);

			int expectedResult = 10;

			REQUIRE(expectedResult == args.upperBound);
		}
	}

	WHEN("argument upperBound is 2 as text")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };
		char arg1[] = { "2" };
		char* argv[] = { arg0, arg1 };

		int argc = std::size(argv);

		THEN("argument should convert to number")
		{
			Args args = ParseArgs(argc, argv);

			int expectedResult = 2;

			REQUIRE(expectedResult == args.upperBound);
		}
	}

	WHEN("argument upperBound is 100000000 as text")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };
		char arg1[] = { "100000000" };
		char* argv[] = { arg0, arg1 };

		int argc = std::size(argv);

		THEN("argument should convert to number")
		{
			Args args = ParseArgs(argc, argv);

			int expectedResult = 100000000;

			REQUIRE(expectedResult == args.upperBound);
		}
	}

	WHEN("count of arguments greater then 2")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };
		char arg1[] = { "10" };
		char arg2[] = { "abc" };
		char* argv[] = { arg0, arg1, arg2 };

		int argc = std::size(argv);

		THEN("Message \"Invalid argument count\nFor use: PrimeNumbers.exe <upper bound>\n\" should be printed")
		{
			try
			{
				ParseArgs(argc, argv);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Invalid argument count\nFor use: PrimeNumbers.exe <upper bound>\n";
				REQUIRE(expectedResult == e.what());
			}
		}
	}

	WHEN("count of arguments less then 2")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };

		char* argv[] = { arg0 };

		int argc = std::size(argv);

		THEN("Message \"Invalid argument count\nFor use: PrimeNumbers.exe <upper bound>\n\" should be printed")
		{
			try
			{
				ParseArgs(argc, argv);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Invalid argument count\nFor use: PrimeNumbers.exe <upper bound>\n";
				REQUIRE(expectedResult == e.what());
			}
		}
	}

	WHEN("argument upperBound is empty string")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };
		char arg1[] = { "" };
		char* argv[] = { arg0, arg1 };

		int argc = std::size(argv);

		THEN("Message \"Number should not be empty\n\" should be printed")
		{
			try
			{
				ParseArgs(argc, argv);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Number should not be empty\n";
				REQUIRE(expectedResult == e.what());
			}
		}
	}

	WHEN("argument upperBound less then 2")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };
		char arg1[] = { "1" };
		char* argv[] = { arg0, arg1 };

		int argc = std::size(argv);

		THEN("Message \"Number should be greater then 1 and less then or equal 100 000 000\n\" should be printed")
		{
			try
			{
				ParseArgs(argc, argv);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Number should be greater then 1 and less then or equal 100 000 000\n";
				REQUIRE(expectedResult == e.what());
			}
		}
	}

	WHEN("argument upperBound greater then 100000000")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };
		char arg1[] = { "100000001" };
		char* argv[] = { arg0, arg1 };

		int argc = std::size(argv);

		THEN("Message \"Number should be greater then 1 and less then or equal 100 000 000\n\" should be printed")
		{
			try
			{
				ParseArgs(argc, argv);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Number should be greater then 1 and less then or equal 100 000 000\n";
				REQUIRE(expectedResult == e.what());
			}
		}
	}

	WHEN("argument upperBound is number out_of_range of integer number")
	{
		char arg0[] = { "c :\\tmp\\example.exe" };
		char arg1[] = { "10000000000" };
		char* argv[] = { arg0, arg1 };

		int argc = std::size(argv);

		THEN("Message \"Argument tooo big\n\" should be printed")
		{
			try
			{
				ParseArgs(argc, argv);
			}
			catch (const std::exception& e)
			{
				std::string expectedResult = "Argument tooo big\n";
				REQUIRE(expectedResult == e.what());
			}
		}
	}
}

SCENARIO("Testing FindPrimeNumbers")
{
	WHEN("upper bound is 2")
	{
		int upperBound = 2;
		std::vector<bool> numbers(upperBound + 1, true);
		FindPrimeNumbers(numbers);

		THEN("element whith index 0 should be false")
		{
			bool expectedResult = false;

			REQUIRE(expectedResult == numbers[0]);
		}

		THEN("element whith index 1 should be false")
		{
			bool expectedResult = false;

			REQUIRE(expectedResult == numbers[1]);
		}

		THEN("only element whith index 2 should be true")
		{
			bool expectedResult = true;

			REQUIRE(expectedResult == numbers[2]);
		}
	}

	WHEN("numbers is empty")
	{
		int upperBound = 0;
		std::vector<bool> numbers(upperBound, true);
		FindPrimeNumbers(numbers);

		THEN("size of numbers should be 0")
		{
			size_t expectedResult = 0;

			REQUIRE(expectedResult == numbers.size());
		}
	}

	WHEN("upper bound is 20")
	{
		int upperBound = 20;
		std::vector<bool> numbers(upperBound + 1, true);
		FindPrimeNumbers(numbers);

		THEN("certain elements should be true")
		{
			std::vector<bool> expectedResult = { 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0 };

			REQUIRE(expectedResult == numbers);
		}
	}
}

SCENARIO("Testing SetPrimeNumbers")
{
	WHEN("vector has 1 item with value equal true")
	{
		std::vector<bool> numbers = { 1 };

		std::set<int> set;
		SetPrimeNumbers(set, numbers);

		THEN("set should have numbers equal truthly vector's index")
		{
			std::set<int> expectedResult = { 0 };
			REQUIRE(expectedResult == set);
		}

		THEN("set should have 1 element")
		{
			size_t expectedResult = 1;
			REQUIRE(expectedResult == set.size());
		}
	}

	WHEN("vector has truthly items")
	{
		std::vector<bool> numbers = { 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0 };

		std::set<int> set;
		SetPrimeNumbers(set, numbers);

		THEN("set should have numbers equal truthly vector's index")
		{
			std::set<int> expectedResult = { 2, 3, 5, 7, 11, 13, 17, 19 };
			REQUIRE(expectedResult == set);
		}

		THEN("set should have 8 elements")
		{
			size_t expectedResult = 8;
			REQUIRE(expectedResult == set.size());
		}
	}

	WHEN("vector has only falthly items")
	{
		std::vector<bool> numbers = { 0, 0 };

		std::set<int> set;
		SetPrimeNumbers(set, numbers);

		THEN("set should be empty")
		{
			std::set<int> expectedResult = {};
			REQUIRE(expectedResult == set);
		}

		THEN("set should have 0 elements")
		{
			size_t expectedResult = 0;
			REQUIRE(expectedResult == set.size());
		}
	}

	WHEN("vector is empty")
	{
		std::vector<bool> numbers = {};

		std::set<int> set;
		SetPrimeNumbers(set, numbers);

		THEN("set should be empty")
		{
			std::set<int> expectedResult = {};
			REQUIRE(expectedResult == set);
		}

		THEN("set should have 0 elements")
		{
			size_t expectedResult = 0;
			REQUIRE(expectedResult == set.size());
		}
	}
}

SCENARIO("Testing GeneratePrimeNumbersSet")
{
	WHEN("set upper bound 30")
	{
		int upperBound = 30;
		std::set<int> result = GeneratePrimeNumbersSet(upperBound);

		THEN("set shoul have ")
		{
		}
	}
}

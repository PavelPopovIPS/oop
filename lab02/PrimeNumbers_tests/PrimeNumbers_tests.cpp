// PrimeNumbers_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

		int argc = static_cast<int>(std::size(argv));

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

		int argc = static_cast<int>(std::size(argv));

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

		int argc = static_cast<int>(std::size(argv));

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

		int argc = static_cast<int>(std::size(argv));

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

		int argc = static_cast<int>(std::size(argv));

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

		int argc = static_cast<int>(std::size(argv));

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

		int argc = static_cast<int>(std::size(argv));

		// тестирование сообщений лучше через выбрасывание типов ошибок
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

		int argc = static_cast<int>(std::size(argv));

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

		int argc = static_cast<int>(std::size(argv));

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

SCENARIO("Generate sets with prime numbers")
{
	WHEN("upperBound is equal 2")
	{
		int upperBound = 2;
		std::set<int> result = GeneratePrimeNumbersSet(upperBound);

		THEN("set should have only one element")
		{
			size_t expectedResult = 1;

			REQUIRE(expectedResult == result.size());
		}

		THEN("set should have only numer 2")
		{
			std::set<int> expectedResult = { 2 };

			REQUIRE(expectedResult == result);
		}
	}

	WHEN("upperBound is equal 20")
	{
		int upperBound = 20;
		std::set<int> result = GeneratePrimeNumbersSet(upperBound);

		THEN("set should have 8 elements")
		{
			size_t expectedResult = 8;

			REQUIRE(expectedResult == result.size());
		}

		THEN("set should have prime numers 2, 3, 5, 7, 11, 13, 17, 19")
		{
			std::set<int> expectedResult = { 2, 3, 5, 7, 11, 13, 17, 19 };

			REQUIRE(expectedResult == result);
		}
	}
}

SCENARIO("Generate empty set")
{
	WHEN("upperBound is equal 1")
	{
		int upperBound = 1;
		std::set<int> result = GeneratePrimeNumbersSet(upperBound);

		THEN("set should be empty")
		{
			std::set<int> expectedResult = {};

			REQUIRE(expectedResult == result);
		}
	}

	WHEN("upperBound is equal 0")
	{
		int upperBound = 0;
		std::set<int> result = GeneratePrimeNumbersSet(upperBound);

		THEN("set should be empty")
		{
			std::set<int> expectedResult = {};

			REQUIRE(expectedResult == result);
		}
	}
}

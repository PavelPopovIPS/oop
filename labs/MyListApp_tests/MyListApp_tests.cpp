// MyListApp_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../MyListApp/CMyList.h"
#include <string>

SCENARIO("create list conteiner for diferent types")
{
	WHEN("create list container for int")
	{
		CMyList<int> list;

		THEN("added element should be 2")
		{
			list.push_back(2);
			auto it = list.begin();
			int result = *it;
			int expectedResult = 2;
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("create list container for string")
	{
		CMyList<std::string> list;

		THEN("added element should be abc")
		{
			list.push_back("abc");
			auto it = list.begin();
			std::string result = *it;
			std::string expectedResult = "abc";
			REQUIRE(result == expectedResult);
		}
	}
}

SCENARIO("add element to front of list")
{
	WHEN("add element to empty list")
	{
		CMyList<int> list;
		list.push_front(3);

		THEN("list should have 1 element")
		{
			size_t result = list.size();
			size_t expectedResult = 1;
			REQUIRE(result == expectedResult);
		}

		THEN("element should be 3")
		{
			auto it = list.begin();
			int result = *it;
			int expectedResult = 3;
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("add element to list with 1 element")
	{
		CMyList<int> list;
		list.push_front(3);
		list.push_front(1);

		THEN("list should have 2 elements")
		{
			size_t result = list.size();
			size_t expectedResult = 2;
			REQUIRE(result == expectedResult);
		}

		THEN("first element should be 1")
		{
			auto it = list.begin();
			int result = *it;
			int expectedResult = 1;
			REQUIRE(result == expectedResult);
		}
	}
}

SCENARIO("add element to end of list")
{
	WHEN("add element to empty list")
	{
		CMyList<int> list;
		list.push_back(3);

		THEN("list should have 1 element")
		{
			size_t result = list.size();
			size_t expectedResult = 1;
			REQUIRE(result == expectedResult);
		}

		THEN("element should be 3")
		{
			auto it = list.begin();
			int result = *it;
			int expectedResult = 3;
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("add element to list with 1 element")
	{
		CMyList<int> list;
		list.push_back(3);
		list.push_back(1);

		THEN("list should have 2 elements")
		{
			size_t result = list.size();
			size_t expectedResult = 2;
			REQUIRE(result == expectedResult);
		}

		THEN("last element should be 1")
		{
			auto it = list.begin();
			++it;
			int result = *it;
			int expectedResult = 1;
			REQUIRE(result == expectedResult);
		}
	}
}

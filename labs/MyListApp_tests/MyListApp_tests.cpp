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

		THEN("element should be equal 3")
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

		THEN("first element should be equal 1")
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

		THEN("element should be equal 3")
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

		THEN("last element should be equal 1")
		{
			auto it = list.end();
			--it;
			int result = *it;
			int expectedResult = 1;
			REQUIRE(result == expectedResult);
		}
	}
}

SCENARIO("insert element to list")
{
	WHEN("insert element to empty list")
	{
		CMyList<int> list;
		auto it = list.begin();

		list.insert(it, 5);

		THEN("list should have 1 element")
		{
			size_t result = list.size();
			size_t expectedResult = 1;
			REQUIRE(result == expectedResult);
		}

		THEN("element should be equal 5")
		{
			auto it = list.begin();
			int result = *it;
			int expectedResult = 5;
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("insert element to start position")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.begin();

		list.insert(it, 5);

		THEN("list should have 4 elements")
		{
			size_t result = list.size();
			size_t expectedResult = 4;
			REQUIRE(result == expectedResult);
		}

		THEN("first element should be equal 5")
		{
			auto it = list.begin();
			int result = *it;
			int expectedResult = 5;
			REQUIRE(result == expectedResult);
		}

		THEN("sequence should be 5 1 2 3")
		{
			auto it = list.begin();
			std::vector<int> result;

			for (it = list.begin(); it != list.end(); ++it)
			{
				result.push_back(*it);
			}

			std::vector<int> expectedResult = { 5, 1, 2, 3 };
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("insert element to last position")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.end();

		list.insert(it, 5);

		THEN("list should have 4 elements")
		{
			size_t result = list.size();
			size_t expectedResult = 4;
			REQUIRE(result == expectedResult);
		}

		THEN("last element should be equal 5")
		{
			auto it = list.end();
			--it;
			int result = *it;
			int expectedResult = 5;
			REQUIRE(result == expectedResult);
		}

		THEN("sequence should be 1 2 3 5")
		{
			auto it = list.begin();
			std::vector<int> result;

			for (it = list.begin(); it != list.end(); ++it)
			{
				result.push_back(*it);
			}

			std::vector<int> expectedResult = { 1, 2, 3, 5 };
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("insert element to center")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.begin();
		++it;

		list.insert(it, 5);

		THEN("list should have 4 elements")
		{
			size_t result = list.size();
			size_t expectedResult = 4;
			REQUIRE(result == expectedResult);
		}

		THEN("sequence should be 1 5 2 3")
		{
			auto it = list.begin();

			std::vector<int> result;

			for (it = list.begin(); it != list.end(); ++it)
			{
				result.push_back(*it);
			}

			std::vector<int> expectedResult = { 1, 5, 2, 3 };
			REQUIRE(result == expectedResult);
		}
	}
}

SCENARIO("erase element from list")
{
	WHEN("erase element to empty list")
	{
		CMyList<int> list;
		auto it = list.begin();

		list.erase(it);

		THEN("list should be empty")
		{
			size_t result = list.size();
			size_t expectedResult = 0;
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("erase element from start position")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.begin();

		list.erase(it);

		THEN("list should have 2 elements")
		{
			size_t result = list.size();
			size_t expectedResult = 2;
			REQUIRE(result == expectedResult);
		}

		THEN("sequence should be 2 3")
		{
			auto it = list.begin();
			std::vector<int> result;

			for (it = list.begin(); it != list.end(); ++it)
			{
				result.push_back(*it);
			}

			std::vector<int> expectedResult = { 2, 3 };
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("erase element from last position")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.end();

		list.erase(it);

		THEN("list should have 3 elements")
		{
			size_t result = list.size();
			size_t expectedResult = 3;
			REQUIRE(result == expectedResult);
		}

		THEN("sequence should be 1 2 3")
		{
			auto it = list.begin();
			std::vector<int> result;

			for (it = list.begin(); it != list.end(); ++it)
			{
				result.push_back(*it);
			}

			std::vector<int> expectedResult = { 1, 2, 3 };
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("erase last element")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.end();
		--it;
		list.erase(it);

		THEN("list should have 2 elements")
		{
			size_t result = list.size();
			size_t expectedResult = 2;
			REQUIRE(result == expectedResult);
		}

		THEN("sequence should be 1 2")
		{
			auto it = list.begin();
			std::vector<int> result;

			for (it = list.begin(); it != list.end(); ++it)
			{
				result.push_back(*it);
			}

			std::vector<int> expectedResult = { 1, 2 };
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("erase element from center")
	{
		CMyList<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);

		auto it = list.begin();
		++it;

		list.erase(it);

		THEN("list should have 2 elements")
		{
			size_t result = list.size();
			size_t expectedResult = 2;
			REQUIRE(result == expectedResult);
		}

		THEN("sequence should be 1 3")
		{
			auto it = list.begin();

			std::vector<int> result;

			for (it = list.begin(); it != list.end(); ++it)
			{
				result.push_back(*it);
			}

			std::vector<int> expectedResult = { 1, 3 };
			REQUIRE(result == expectedResult);
		}
	}
}

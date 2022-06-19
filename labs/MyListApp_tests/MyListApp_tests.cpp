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
			list.PushBack(2);
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
			list.PushBack("abc");
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
		list.PushFront(3);

		THEN("list should have 1 element")
		{
			size_t result = list.Size();
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
		list.PushFront(3);
		list.PushFront(1);

		THEN("list should have 2 elements")
		{
			size_t result = list.Size();
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
		list.PushBack(3);

		THEN("list should have 1 element")
		{
			size_t result = list.Size();
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
		list.PushBack(3);
		list.PushBack(1);

		THEN("list should have 2 elements")
		{
			size_t result = list.Size();
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

SCENARIO("Insert element to list")
{
	WHEN("Insert element to empty list")
	{
		CMyList<int> list;
		auto it = list.begin();

		list.Insert(it, 5);

		THEN("list should have 1 element")
		{
			size_t result = list.Size();
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

	WHEN("Insert element to start position")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);

		auto it = list.begin();

		list.Insert(it, 5);

		THEN("list should have 4 elements")
		{
			size_t result = list.Size();
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

	WHEN("Insert element to last position")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);

		auto it = list.end();

		list.Insert(it, 5);

		THEN("list should have 4 elements")
		{
			size_t result = list.Size();
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

	WHEN("Insert element to center")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);

		auto it = list.begin();
		++it;

		list.Insert(it, 5);

		THEN("list should have 4 elements")
		{
			size_t result = list.Size();
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

		THEN("list should be empty")
		{
			try
			{
				list.Erase(it);
				REQUIRE(FALSE);
			}
			catch (std::exception& e)
			{
				std::string expectedMsg = "List is empty\n";
				std::string msg = e.what();
				REQUIRE(msg == expectedMsg);
			}

			size_t result = list.Size();
			size_t expectedResult = 0;
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("erase element from start position")
	{
		CMyList<int> list;
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);

		auto it = list.begin();

		list.Erase(it);

		THEN("list should have 2 elements")
		{
			size_t result = list.Size();
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
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);

		auto it = list.end();

		THEN("list should have 3 elements")
		{
			try
			{
				list.Erase(it);
				REQUIRE(FALSE);
			}
			catch (std::exception& e)
			{
				std::string expectedMsg = "Element not exist\n";
				std::string msg = e.what();
				REQUIRE(msg == expectedMsg);
			}

			size_t result = list.Size();
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
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);

		auto it = list.end();
		--it;
		list.Erase(it);

		THEN("list should have 2 elements")
		{
			size_t result = list.Size();
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
		list.PushBack(1);
		list.PushBack(2);
		list.PushBack(3);

		auto it = list.begin();
		++it;

		list.Erase(it);

		THEN("list should have 2 elements")
		{
			size_t result = list.Size();
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

SCENARIO("Size of list depends on elements count")
{
	WHEN("list is empty")
	{
		CMyList<int> list;

		THEN("Size equal 0")
		{
			size_t result = list.Size();

			size_t expectedResult = 0;
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("list contains any elements")
	{
		CMyList<int> list;
		list.PushBack(2);
		list.PushFront(1);

		THEN("count added elements should be equal Size of list")
		{
			size_t result = list.Size();

			size_t expectedResult = 2;
			REQUIRE(result == expectedResult);
		}
	}
}

SCENARIO("copy list")
{
	WHEN("list was copied")
	{
		CMyList<int> list;
		list.PushBack(2);
		list.PushBack(3);
		list.PushBack(4);

		CMyList<int> list2 = list;

		THEN("new list sequence should be 2 3 4")
		{
			auto it = list2.begin();

			std::vector<int> result;

			for (it = list2.begin(); it != list2.end(); ++it)
			{
				result.push_back(*it);
			}

			std::vector<int> expectedResult = { 2, 3, 4 };
			REQUIRE(result == expectedResult);
		}

		THEN("size of new list should be 3")
		{
			size_t result = list2.Size();

			size_t expectedResult = 3;
			REQUIRE(result == expectedResult);
		}
	}
}

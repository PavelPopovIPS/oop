// MyListApp_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../MyListApp/CMyList.h"

SCENARIO("create list conteiner for diferent types")
{
	WHEN("create list container for int")
	{
		CMyList<int> list;

		THEN("shoul have ability to add int to list")
		{
			list.push_back(2);
			REQUIRE(TRUE);
		}

		THEN("added element should be 2")
		{
			list.push_back(2);
			auto it = list.begin();
			int result = *it;
			int expectedResult = 2;
			REQUIRE(result == expectedResult);
		}
	}
}

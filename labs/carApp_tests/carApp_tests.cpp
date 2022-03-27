// carApp_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../carApp/Car.h"
#include "../carApp/stdafx.h"

#include <iostream>

SCENARIO("Testing propertie IsTurnedOn()")
{
	GIVEN("class Car")
	{
		Car car;

		WHEN("car engine in default state")
		{
			bool result = car.IsTurnedOn();

			THEN("engine is Turn Off")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("engine was turned on - TurnOnEngine()")
		{
			car.TurnOnEngine();
			bool result = car.IsTurnedOn();

			THEN("engine state should be turn on")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("engine was turned off - TurnOffEngine()")
		{
			car.TurnOffEngine();
			bool result = car.IsTurnedOn();

			THEN("engine state should be turn off")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}
		}
	}
}

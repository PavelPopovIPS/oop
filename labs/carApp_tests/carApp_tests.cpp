// carApp_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../carApp/Car.h"
#include "../carApp/stdafx.h"

#include <iostream>

SCENARIO("Testing property IsTurnedOn()")
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

SCENARIO("Testing property GetDirection()")
{
	GIVEN("class Car")
	{
		Car car;

		WHEN("car is turn off by default")
		{
			Direction result = car.GetDirection();

			THEN("direction state should be Stop")
			{
				Direction expectedResult = Direction::Stop;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("car was turn on")
		{
			car.TurnOnEngine();
			Direction result = car.GetDirection();

			THEN("direction state should be Stop")
			{
				Direction expectedResult = Direction::Stop;
				REQUIRE(result == expectedResult);
			}
		}
	}

	// TODO: Написать тесты для направления Forward и Back
}

SCENARIO("Testing property GetGear()")
{
	GIVEN("class Car")
	{
		Car car;

		WHEN("car is turn off by default")
		{
			int result = car.GetGear();

			THEN("gear state should be zero (0)")
			{
				int expectedResult = 0;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("car was turned on")
		{
			car.TurnOnEngine();
			int result = car.GetGear();

			THEN("gear state should be zero (0)")
			{
				int expectedResult = 0;
				REQUIRE(result == expectedResult);
			}
		}
	}

	// TODO: Написать тесты для остальных передач
}

SCENARIO("Testing property GetSpeed()")
{
	GIVEN("class Car")
	{
		Car car;

		WHEN("car is turn off by default")
		{
			int result = car.GetSpeed();

			THEN("speed state should be zero (0)")
			{
				int expectedResult = 0;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("car was turn on")
		{
			car.TurnOnEngine();
			int result = car.GetSpeed();

			THEN("speed state should be zero (0)")
			{
				int expectedResult = 0;
				REQUIRE(result == expectedResult);
			}
		}
	}

	// TODO: Написать тесты для интервалов скорости и максимальной скорости
}

SCENARIO("Testing method TurnOnEngine()")
{
	GIVEN("class Car")
	{
		Car car;

		WHEN("car was turn off by default")
		{
			bool result = car.TurnOnEngine();

			THEN("TurnOnEngine() return true ")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("car was turn on")
		{
			bool result = car.TurnOnEngine();

			THEN("TurnOnEngine() return true result again")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}
	}
}

SCENARIO("Testing method TurnOffEngine()")
{
	GIVEN("class Car")
	{
		Car car;

		WHEN("car was turn off by default")
		{
			bool result = car.TurnOffEngine();

			THEN("TurnOffEngine() return true ")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("car is turn on, gear is zero, speed is zero and direction is Stop")
		{
			bool result = car.TurnOnEngine();

			THEN("TurnOffEngine() return true state")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}
	}

	// TODO: Написать тесты для случчаев когда передача не нейтраль, скорость не ноль и направление не стоп
}

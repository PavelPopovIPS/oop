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
	GIVEN("class Car for default states")
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

	GIVEN("class car for gear changing")
	{
		Car car;

		WHEN("engine is turn off and set 0 gear (neutral)")
		{
			car.SetGear(0);
			int result = car.GetGear();

			THEN("GetGear() should return 0")
			{
				int expectedResult = 0;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("engine is turn off and set gear not equal 0(neutral)")
		{
			car.SetGear(-1);
			int result = car.GetGear();

			THEN("GetGear() should return 0")
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

// Проверяю возможность вставить передачу на определенной скорости
SCENARIO("Testing method SetGear()")
{
	GIVEN("class car and engine is turn off")
	{
		Car car;

		WHEN("set 0 gear (neutral)")
		{
			bool result = car.SetGear(0);

			THEN("SetGear() should return true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}

		WHEN("set gear not equal 0(neutral)")
		{
			bool result = car.SetGear(1);

			THEN("SetGear() should return false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}
		}
	}

	GIVEN("engine is turn on and speed 0")
	{
		Car car;
		car.TurnOnEngine();

		WHEN("set gear -1")
		{
			bool returnResult = car.SetGear(-1);

			THEN("SetGear() should return true")
			{
				bool expectedResult = true;
				REQUIRE(returnResult == expectedResult);
			}

			int state = car.GetGear();
			THEN("GetGear() should return -1")
			{
				int expectedResult = -1;
				REQUIRE(state == expectedResult);
			}
		}
	}

	GIVEN("engine is turn on, gear is -1 and speed 10")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);

		WHEN("set gear 0 and set gear -1 again")
		{
			bool result = car.SetGear(0);

			THEN("SetGear() should return true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			result = car.SetGear(-1);
			int resultGear = car.GetGear();

			THEN("SetGear() should return false and GetGear() should return 0")
			{
				bool expectedResult = false;
				int expectedGear = 0;
				REQUIRE(result == expectedResult);
				REQUIRE(resultGear == expectedGear);
			}
		}

		WHEN("set gear 0, set speed 0 and set gear -1 again")
		{
			car.SetGear(0);
			car.SetSpeed(0);
			bool result = car.SetGear(-1);
			int resultGear = car.GetGear();

			THEN("SetGear() should return true and GetGear() should return -1")
			{
				bool expectedResult = true;
				int expectedGear = -1;
				REQUIRE(result == expectedResult);
				REQUIRE(resultGear == expectedGear);
			}
		}

		WHEN("set gear 0 and set gear 1")
		{
			car.SetGear(0);
			bool result = car.SetGear(1);
			int resultGear = car.GetGear();

			THEN("SetGear() should return false and GetGear() should return 0")
			{
				bool expectedResult = false;
				int expectedGear = 0;
				REQUIRE(result == expectedResult);
				REQUIRE(resultGear == expectedGear);
			}
		}
	}

	GIVEN("engine is turn on and speed 0")
	{
		Car car;
		car.TurnOnEngine();

		WHEN("set gear equal 0")
		{
			bool returnResult = car.SetGear(0);

			THEN("SetGear() should return true")
			{
				bool expectedResult = true;
				REQUIRE(returnResult == expectedResult);
			}

			int state = car.GetGear();
			THEN("GetGear() should return 0")
			{
				int expectedResult = 0;
				REQUIRE(state == expectedResult);
			}
		}
	}

	GIVEN("engine is turn on and speed 0")
	{
		Car car;
		car.TurnOnEngine();

		WHEN("set gear equal 1")
		{
			bool returnResult = car.SetGear(1);

			THEN("SetGear() should return true")
			{
				bool expectedResult = true;
				REQUIRE(returnResult == expectedResult);
			}

			int state = car.GetGear();
			THEN("GetGear() should return 1")
			{
				int expectedResult = 1;
				REQUIRE(state == expectedResult);
			}
		}
	}
}

SCENARIO("Проверка включения первой скорости на разных скоростях")
{
}

// Проверяю ограничения скорости для определенной передачи
SCENARIO("Testing method SetSpeed()")
{
	GIVEN("class car and engine is turn off")
	{
		Car car;

		WHEN("set speed 10")
		{
			bool result = car.SetSpeed(10);

			THEN("SetSpeed() should return false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}
		}
	}

	GIVEN("turn on car and gear is -1 and speed is zero")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);

		WHEN("set speed -1")
		{
			bool statusResult = car.SetSpeed(-1);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be false, direction should be Stop, speed should be zero")
			{
				bool expectedResult = false;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 0")
		{
			bool statusResult = car.SetSpeed(0);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be true, direction should be Stop, speed should be zero")
			{
				bool expectedResult = true;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 1")
		{
			bool statusResult = car.SetSpeed(1);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be true, direction should be Back, speed should be 1")
			{
				bool expectedResult = true;
				Direction expectedDirection = Direction::Back;
				int expectedSpeed = 1;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 20")
		{
			bool statusResult = car.SetSpeed(20);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be true, direction should be Back, speed should be 20")
			{
				bool expectedResult = true;
				Direction expectedDirection = Direction::Back;
				int expectedSpeed = 20;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 21")
		{
			bool statusResult = car.SetSpeed(21);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be false, direction should be Stop, speed should be 0")
			{
				bool expectedResult = false;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 20, set speed 21")
		{
			bool statusResult = car.SetSpeed(20);
			statusResult = car.SetSpeed(21);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be false, direction should be Stop, speed should be 20")
			{
				bool expectedResult = false;
				Direction expectedDirection = Direction::Back;
				int expectedSpeed = 20;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 20, set speed 0")
		{
			bool statusResult = car.SetSpeed(20);
			statusResult = car.SetSpeed(0);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();
			int gearResult = car.GetGear();

			THEN("status should be true, direction should be Stop, speed should be 0, gear should be -1")
			{
				bool expectedResult = true;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				int expectedGear = -1;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
				REQUIRE(gearResult == expectedGear);
			}
		}

		WHEN("set speed 20, set gear 0, set speed 0")
		{
			bool statusResult = car.SetSpeed(20);
			statusResult = car.SetGear(0);
			statusResult = car.SetSpeed(0);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();
			int gearResult = car.GetGear();

			THEN("status should be true, direction should be Stop, speed should be 0, gear should be 0")
			{
				bool expectedResult = true;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				int expectedGear = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
				REQUIRE(gearResult == expectedGear);
			}
		}

		WHEN("set speed 10, set gear 0, set speed 15")
		{
			bool statusResult = car.SetSpeed(10);
			statusResult = car.SetGear(0);
			statusResult = car.SetSpeed(15);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();
			int gearResult = car.GetGear();

			THEN("status should be false, direction should be Back, speed should be 10, gear should be 0")
			{
				bool expectedResult = false;
				Direction expectedDirection = Direction::Back;
				int expectedSpeed = 10;
				int expectedGear = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
				REQUIRE(gearResult == expectedGear);
			}
		}
	}

	GIVEN("turn on car and gear is zero and speed is zero")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(0);

		WHEN("set speed 0")
		{
			bool statusResult = car.SetSpeed(0);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be true, direction should be Stop, speed should be zero")
			{
				bool expectedResult = true;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 10")
		{
			bool statusResult = car.SetSpeed(10);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be false, direction should be Stop, speed should be zero")
			{
				bool expectedResult = false;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}
	}

	GIVEN("turn on car and gear is 1 and speed is zero")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);

		WHEN("set speed -1")
		{
			bool statusResult = car.SetSpeed(-1);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be false, direction should be Stop, speed should be zero")
			{
				bool expectedResult = false;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 0")
		{
			bool statusResult = car.SetSpeed(0);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be true, direction should be Stop, speed should be zero")
			{
				bool expectedResult = true;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 1")
		{
			bool statusResult = car.SetSpeed(1);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be true, direction should be Forward, speed should be 1")
			{
				bool expectedResult = true;
				Direction expectedDirection = Direction::Forward;
				int expectedSpeed = 1;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 30")
		{
			bool statusResult = car.SetSpeed(30);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be true, direction should be Forward, speed should be 30")
			{
				bool expectedResult = true;
				Direction expectedDirection = Direction::Forward;
				int expectedSpeed = 30;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 31")
		{
			bool statusResult = car.SetSpeed(31); //всегда создается новый объект
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be false, direction should be Forward, speed should be 30")
			{
				bool expectedResult = false;
				Direction expectedDirection = Direction::Stop;
				int expectedSpeed = 0;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}

		WHEN("set speed 30, set speed 31")
		{
			bool statusResult = car.SetSpeed(30);
			statusResult = car.SetSpeed(31);
			Direction directionResult = car.GetDirection();
			int speedResult = car.GetSpeed();

			THEN("status should be false, direction should be Forward, speed should be 30")
			{
				bool expectedResult = false;
				Direction expectedDirection = Direction::Forward;
				int expectedSpeed = 30;
				REQUIRE(statusResult == expectedResult);
				REQUIRE(directionResult == expectedDirection);
				REQUIRE(speedResult == expectedSpeed);
			}
		}
	}
}

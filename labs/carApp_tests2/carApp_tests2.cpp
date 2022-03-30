﻿// carApp_tests2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../carApp/Car.h"
#include "../carApp/stdafx.h"

SCENARIO("1. Проверка метода TurnOnEngine()")
{
	SECTION("1.1 Возвращает true, если двигатель включился")
	{
		Car car;

		WHEN("двигатель включился")
		{
			bool result = car.TurnOnEngine();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}
	}

	SECTION("1.2 Возвращает true, если уже был включен.")
	{
		Car car;
		car.TurnOnEngine();

		WHEN("двигатель включается, во включенном состоянии")
		{
			bool result = car.TurnOnEngine();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}
	}

	SECTION("1.3 После включения двигателя, машина находится на нейтральной передаче, в состоянии покоя, скорость 0,")
	{
		Car car;
		car.TurnOnEngine();

		WHEN("двигатель включается")
		{
			bool state = car.IsTurnedOn();
			Direction direction = car.GetDirection();
			int gear = car.GetGear();
			int speed = car.GetSpeed();

			THEN("состояние двигателя - включено")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}

			THEN("машина находится в состоянии покоя")
			{
				Direction expectedResult = Direction::Stop;
				REQUIRE(direction == expectedResult);
			}

			THEN("машина находится на нейтрали")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("скорость 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("2. Проверка метода TurnOffEngine()")
{

	SECTION("2.1 Выключить двигатель, если он включен и текущая передача – нейтральная, а автомобиль стоит, Скорость  равна нулю - вернется true")
	{
		Car car;
		car.TurnOnEngine();

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("2.2 состояния двигателя выключено")
			{
				bool expectedResult = false;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.3 Выключить двигатель, если он уже выключен")
	{
		Car car;

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("состояния двигателя выключено")
			{
				bool expectedResult = false;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.4 Выключить двигатель, если передача задняя")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("состояния двигателя включено")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.5 Выключить двигатель, если передача первая")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("состояния двигателя включено")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.6 Выключить двигатель, если передача нейтральная и скорость ненулевая")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(1);
		car.SetGear(0);

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("состояния двигателя включено")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}

			THEN("скорость равна заданному значению")
			{
				int expectedResult = 1;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("3 Проверка SetGear() и SetSpeed() - При вЫключенном двигателе")
{
	SECTION("3.1 При выключенном двигателе включается только нейтраль")
	{
		Car car;

		WHEN("включаю нейтраль")
		{
			bool result = car.SetGear(0);
			int gear = car.GetGear();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("3.2 При вЫключенном двигателе задняя передача (-1) не включается")
	{
		Car car;

		WHEN("включаю заднюю передачу")
		{
			bool result = car.SetGear(-1);
			int gear = car.GetGear();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("3.3 При вЫключенном двигателе первая передача не включается")
	{
		Car car;

		WHEN("включаю первую передачу")
		{
			bool result = car.SetGear(1);
			int gear = car.GetGear();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("3.4 При вЫключенном двигателе отрицательная скорость не выставляется")
	{
		Car car;

		WHEN("выставляю скорость меньше нуля")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость на нуле")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("3.5 При вЫключенном двигателе скорость не выставляется")
	{
		Car car;

		WHEN("выставляю скорость больше нуля")
		{
			bool result = car.SetSpeed(1);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость на нуле")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("4.1 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Задняя передача ")
{
	SECTION("4.1.1 На задний ход (-1) можно переключиться на нулевой скорости")
	{
		Car car;
		car.TurnOnEngine();

		WHEN("включаю заднюю передачу")
		{
			bool result = car.SetGear(-1);
			int gear = car.GetGear();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена задняя скорость")
			{
				int expectedResult = -1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.1.2 Можно стоять на месте задав скорость 0, направление будет stop")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);

		WHEN("задаю скорость 0")
		{
			bool result = car.SetSpeed(0);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость равна 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина стоит на месте")
			{
				Direction expectedResult = Direction::Stop;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.3 Можно развить скорость 1, направление будет back")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);

		WHEN("задаю скорость 1")
		{
			bool result = car.SetSpeed(1);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость равна 1")
			{
				int expectedResult = 1;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается назад")
			{
				Direction expectedResult = Direction::Back;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.4 Можно развить скорость 20, направление будет back")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);

		WHEN("задаю скорость 20")
		{
			bool result = car.SetSpeed(20);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость равна 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается назад")
			{
				Direction expectedResult = Direction::Back;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.5 При движении назад на нейтральной передаче не допускается включать заднюю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);

		WHEN("включаю заднюю передачу")
		{
			bool result = car.SetGear(-1);
			int gear = car.GetGear();
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("скорость равна 10")
			{
				int expectedResult = 10;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается назад")
			{
				Direction expectedResult = Direction::Back;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.6 Переключившись на заднем ходу на нейтральную передачу на ненулевой скорости, скорость можно уменьшать")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);

		WHEN("уменьшаю скорость")
		{
			bool result = car.SetSpeed(8);
			int speed = car.GetSpeed();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость равна 8")
			{
				int expectedResult = 8;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1.7 Переключившись на заднем ходу на нейтральную передачу на ненулевой скорости переключиться на переднюю передачу можно только после остановки")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);
		car.SetSpeed(0);

		WHEN("включаю первую скорость")
		{
			bool result = car.SetGear(1);
			int gear = car.GetGear();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("Включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.1[Негативный сценарий 1] Нельзя развить скорость меньше 0 ")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);

		WHEN("задаю отрицательную скорость")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1[Негативный сценарий 2] Нельзя развить скорость больше 20 ")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);

		WHEN("задаю скорость больше 20")
		{
			bool result = car.SetSpeed(21);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1[Негативный сценарий 3] Переключившись на заднем ходу на нейтральную передачу на ненулевой скорости переключиться на переднюю нельзя")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(15);
		car.SetGear(0);

		WHEN("задаю первую передачу")
		{
			bool result = car.SetGear(1);
			int gear = car.GetGear();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("Включена нейтральная передача")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.1[Негативный сценарий 4] Переключившись на заднем ходу на нейтральную передачу на ненулевой скорости, скорость нельзя увеличить")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);

		WHEN("увеличиваю скорость")
		{
			bool result = car.SetSpeed(15);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость остается неизменной")
			{
				int expectedResult = 10;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1[Негативный сценарий 5] Нельзя задавать скорость меньше -1")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(20);

		WHEN("увеличиваю скорость")
		{
			bool result = car.SetGear(-2);
			int gear = car.GetGear();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("передача заняя")
			{
				int expectedResult = -1;
				REQUIRE(gear == expectedResult);
			}
		}
	}
}

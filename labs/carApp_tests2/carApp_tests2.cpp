// carApp_tests2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

SCENARIO("4.1 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Задняя передача")
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

SCENARIO("4.2 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Нейтраль")
{
	SECTION("4.2.1 На нейтрали можно переключиться на нейтраль")
	{
		Car car;
		car.TurnOnEngine();

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

	SECTION("4.2.2 Переключиться на нейтраль с 1й скорости и остановиться")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(15);

		WHEN("включаю нейтраль и останавливаюсь")
		{
			car.SetGear(0);
			car.SetSpeed(0);

			int gear = car.GetGear();
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("скорость 0")
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
}

SCENARIO("4.3 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Первая передача(1) - скорость 0 – 30")
{
	SECTION("4.3.1 Можно стоять на месте задав скорость 0, направление будет stop")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);

		WHEN("задаю скорость 0")
		{
			bool result = car.SetSpeed(0);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 0")
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

	SECTION("4.3.2 Можно развить скорость 1, направление будет forward")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);

		WHEN("задаю скорость 1")
		{
			bool result = car.SetSpeed(1);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 1")
			{
				int expectedResult = 1;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается вперед")
			{
				Direction expectedResult = Direction::Forward;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.3 На нулевой скорости можно включить заднюю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);

		WHEN("включаю заднюю передачу")
		{
			bool result = car.SetGear(-1);
			int gear = car.GetGear();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена задняя передача")
			{
				int expectedResult = -1;
				REQUIRE(gear == expectedResult);
			}

			THEN("машина стоит на месте")
			{
				Direction expectedResult = Direction::Stop;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.4 Можно развить скорость 30")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);

		WHEN("задаю скорость 30")
		{
			bool result = car.SetSpeed(30);
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 30")
			{
				int expectedResult = 30;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3.5 При скорости 30 можно переключиться с 3й на 1ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);

		WHEN("включить первую передачу")
		{
			bool result = car.SetGear(1);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3.6 При скорости 20 можно переключиться с 2й на 1ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(20);

		WHEN("включить первую передачу")
		{
			bool result = car.SetGear(1);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3.7 На нейтрали можно уменьшить скорость с 30 до 20")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(0);

		WHEN("уменьшить скорость до 20")
		{
			bool result = car.SetSpeed(20);
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3.8 На нейтрали нельзя увеличить скорость")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(0);

		WHEN("увеличить скорость до 25")
		{
			bool result = car.SetSpeed(25);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3.9 На первой скорости можно остановиться")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);

		WHEN("останавливаюсь")
		{
			bool result = car.SetSpeed(0);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 0")
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

	SECTION("4.3.10 На нейтрали уменьшить скорость со 40 до 20 и переключиться на 1ю")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(0);
		car.SetSpeed(20);

		WHEN("Уменьшить скорость")
		{
			bool result = car.SetGear(1);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передавча")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3.11 На скорости можно переключиться с нейтрали на 1ю передачу ")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(0);

		WHEN("включить превую передачу")
		{
			bool result = car.SetGear(1);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3[Негативный сценарий 1] Нельзя развить скорость меньше 0")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);

		WHEN("задать скорость меньше 0")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("останется нулевая скорость")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3[Негативный сценарий 2] Нельзя развить скорость меньше больше 30")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);

		WHEN("задать скорость больше 30")
		{
			bool result = car.SetSpeed(31);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("останется нулевая скорость")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3[Негативный сценарий 3] Нельзя переключиться на заднюю передачу (-1) на ненулевой скорости")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);

		WHEN("переключиться на заднюю передачу")
		{
			bool result = car.SetGear(-1);
			int gear = car.GetGear();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3[Негативный сценарий 4] При скорости 31 нельзя переключиться со 2й на 1ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(31);

		WHEN("переключиться со 2й на 1ю передачу")
		{
			bool result = car.SetGear(1);
			int gear = car.GetGear();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}
}

SCENARIO("4.4 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Вторая передача (2) - скорость 20 – 50")
{
	SECTION("4.4.1 При скорости 20 можно переключиться с 1й на 2ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);

		WHEN("переключиться со 1й на 2ю передачу")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.2 При скорости 30 можно переключиться с 1й на 2ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);

		WHEN("переключиться со 1й на 2ю передачу")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.3 При скорости 30 можно переключиться с 3й на 2ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);

		WHEN("переключиться со 3й на 2ю передачу")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.4 При скорости 50 можно переключиться с 3й на 2ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(50);

		WHEN("переключиться со 3й на 2ю передачу")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.5 При скорости 40 можно переключиться с 4й на 2ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(40);
		car.SetGear(4);

		WHEN("переключиться со 4й на 2ю передачу")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.6 При скорости 50 можно переключиться с 5й на 2ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(5);

		WHEN("переключиться со 5й на 2ю передачу")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.7 Можно переключиться со второй на вторую передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);

		WHEN("переключиться на 2ю передачу")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.8 Можно развить скорость 20 направление будет forward")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);

		WHEN("уменьшить скорость до 20")
		{
			bool result = car.SetSpeed(20);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}

			THEN("движение вперед")
			{
				Direction expectedResult = Direction::Forward;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.4.9 Можно развить скорость 50 направление будет forward")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);

		WHEN("увеличить скорость до 50")
		{
			bool result = car.SetSpeed(50);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 50")
			{
				int expectedResult = 50;
				REQUIRE(speed == expectedResult);
			}

			THEN("движение вперед")
			{
				Direction expectedResult = Direction::Forward;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.4.10 Можно переключиться на нейтраль")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);

		WHEN("включить нейтраль")
		{
			bool result = car.SetGear(0);
			int gear = car.GetGear();

			THEN("метод вернет true")
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

	SECTION("4.4.11 Можно переключиться с нейтрали на 2ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetGear(0);

		WHEN("включить вторую передачу")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.12 На нейтрали можно уменьшить скорость")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(0);

		WHEN("уменьшить скорость")
		{
			bool result = car.SetSpeed(25);
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 25")
			{
				int expectedResult = 25;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4.13 На нейтрали нельзя увеличить скорость")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(0);

		WHEN("увеличить скорость")
		{
			bool result = car.SetSpeed(45);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 1] При нулевой передаче и нулевой скорости нельзя включить 2ю передачу")
	{
		Car car;
		car.TurnOnEngine();

		WHEN("включить вторую передачу")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет false")
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

	SECTION("4.4[Негативный сценарий 2] Со второй передачи нельзя переключиться на заднюю передачу (-1)")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(25);
		car.SetGear(2);

		WHEN("включить заднюю передачу")
		{
			bool result = car.SetGear(-1);
			int gear = car.GetGear();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая скорость")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 3] На второй передаче нельзя развить скорость меньше 20")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(25);
		car.SetGear(2);

		WHEN("уменьшить скорость до 19")
		{
			bool result = car.SetSpeed(19);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 25")
			{
				int expectedResult = 25;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 4] На второй передаче нельзя развить скорость больше 50")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(25);
		car.SetGear(2);

		WHEN("увеличить скорость до 51")
		{
			bool result = car.SetSpeed(51);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 25")
			{
				int expectedResult = 25;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 5] При скорости 19 нельзя переключиться с 1й на 2ю передачу ")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(19);

		WHEN("переключить передачу на вторую")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 6] При скорости 51 нельзя переключиться с 3й на 2ю передачу")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(3);
		car.SetSpeed(51);

		WHEN("переключить передачу на вторую")
		{
			bool result = car.SetGear(2);
			int gear = car.GetGear();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}
}

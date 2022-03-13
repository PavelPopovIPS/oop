// AddNumberToVectorElements_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN // убирает main и говорит catch запускать только этот файл. Должен быть выже include catch
#include "../../catch2/catch.hpp"
#include "../vector_v1/VectorHandler.h"
#include <string>
#include <vector>

SCENARIO("Тестирование ParseStringToVector")
{
	WHEN("передается пустая строка")
	{
		std::string emptyStr = "";

		THEN("должно выбросится исключение с сообщением")
		{
			try
			{
				ParseStringToVector(emptyStr);
			}
			catch (const std::exception& e)
			{
				std::string errorMsg = e.what();
				REQUIRE(errorMsg == "You did not enter numbers\n");
			}
		}
	}

	WHEN("передается строка с одним положительным числом")
	{
		std::vector<double> vectr = ParseStringToVector("12");

		THEN("в векторе должен быть один элемент с нужным значением")
		{
			REQUIRE(vectr.size() == 1.0);
			REQUIRE(vectr[0] == 12.0);
		}
	}

	WHEN("передается строка с двумя double числами")
	{
		std::vector<double> vectr = ParseStringToVector("1.11 -5.37");

		THEN("в векторе должно быть 2 элемент с double числами")
		{
			REQUIRE(vectr.size() == 2.0);
			REQUIRE(vectr[0] == 1.11);
			REQUIRE(vectr[1] == -5.37);
		}
	}

	WHEN("передается строка с буквенными символами")
	{
		std::string emptyStr = "abc";

		THEN("должно выбросится исключение с сообщением")
		{
			try
			{
				ParseStringToVector(emptyStr);
			}
			catch (const std::exception& e)
			{
				std::string errorMsg = e.what();
				REQUIRE(errorMsg == "You should use number\n");
			}
		}
	}
}

SCENARIO("Тестирование CalcPositiveElementsAverage")
{
	WHEN("передается вектор с 1 положительными числом")
	{
		std::vector<double> vectr = { 5.0 };

		THEN("должно вернуться это же число")
		{
			REQUIRE(CalcPositiveElementsAverage(vectr) == 5.0);
		}
	}

	WHEN("передается вектор с двумя положительными числами")
	{
		std::vector<double> vectr = { 5.0, 3.4 };

		THEN("должно вернуться среднее арифметическое этих двух чисел")
		{
			REQUIRE(CalcPositiveElementsAverage(vectr) == 4.2);
		}
	}

	WHEN("передается вектор с положительными и отрицательными числами")
	{
		std::vector<double> vectr = { -1, 5.0, -10.34, 3.4 };

		THEN("должно вернуться среднее арифметическое всех положительных чисел")
		{
			REQUIRE(CalcPositiveElementsAverage(vectr) == 4.2);
		}
	}

	WHEN("передается вектор у которого все элементы с отрицательными числами")
	{
		std::vector<double> vectr = { -1, -5.0, -10.34, -3.4 };

		THEN("должно выброситься исключение с сообщением")
		{
			try
			{
				CalcPositiveElementsAverage(vectr);
			}
			catch (const std::exception& e)
			{
				std::string errorMsg = e.what();
				REQUIRE(errorMsg == "There are no positive elements\n");
			}
		}
	}

	WHEN("передается вектор у которого все элементы равны нулям")
	{
		std::vector<double> vectr = { 0, 0, 0 };

		THEN("должно выброситься исключение с сообщением")
		{
			try
			{
				CalcPositiveElementsAverage(vectr);
			}
			catch (const std::exception& e)
			{
				std::string errorMsg = e.what();
				REQUIRE(errorMsg == "There are no positive elements\n");
			}
		}
	}
}
SCENARIO("Тестирование AddNumberToVectorElements")
{
	WHEN("передается вектор и какое либо число")
	{
		std::vector<double> vectr = { 0, 1 };
		double number = 2;

		AddNumberToVectorElements(vectr, number);

		THEN("к каждому элементу вектора должно быть прибавлено переданное число")
		{
			REQUIRE(vectr.size() == 2);
			REQUIRE(vectr[0] == 2);
			REQUIRE(vectr[1] == 3);
		}
	}

	WHEN("передается вектор и какое либо число")
	{
		std::vector<double> vectr = { 0, 1, -1 };
		double number = 2.3;

		AddNumberToVectorElements(vectr, number);

		THEN("к каждому элементу вектора должно быть прибавлено переданное число")
		{
			REQUIRE(vectr.size() == 3);

			REQUIRE(round(vectr[0] * 10) / 10 == 2.3);
			REQUIRE(round(vectr[1] * 10) / 10 == 3.3);
			REQUIRE(round(vectr[2] * 10) / 10 == 1.3);
		}
	}
}

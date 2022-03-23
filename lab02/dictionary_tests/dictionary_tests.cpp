// dictionary_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../dictionary/dicfns.h"

SCENARIO("Проверка DeleteBrackets")
{
	WHEN("передается пустая строка")
	{
		std::string result = DeleteBrackets("");

		THEN("дожна вернуться пустая строка")
		{
			REQUIRE(result == "");
		}
	}

	WHEN("передается строка содержащая только квадратные скобки")
	{
		std::string result = DeleteBrackets("[]");

		THEN("дожна вернуться пустая строка")
		{
			REQUIRE(result == "");
		}
	}

	WHEN("передается строка содержащая текст, обернутый в кобки")
	{
		std::string result = DeleteBrackets("[text]");

		THEN("дожна вернуться строка с текстом без скобок")
		{
			REQUIRE(result == "text");
		}
	}

	WHEN("передается строка содержащая квадратные скобки в тексте")
	{
		std::string result = DeleteBrackets("te[]xt");

		THEN("дожна вернуться строка с текстом без скобок")
		{
			REQUIRE(result == "text");
		}
	}

	WHEN("передается строка содержащая только текст")
	{
		std::string result = DeleteBrackets("text");

		THEN("дожна вернуться строка с текстом")
		{
			REQUIRE(result == "text");
		}
	}
}

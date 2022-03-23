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

SCENARIO("Проверка функции CutSpaces")
{
	WHEN("передается пустая строка")
	{
		std::string result = CutSpaces("");

		THEN("дожна вернуться пустая строка")
		{
			REQUIRE(result == "");
		}
	}

	WHEN("передается текст без пробелов")
	{
		std::string result = CutSpaces("text");

		THEN("должен вернуться текст без пробелов")
		{
			REQUIRE(result == "text");
		}
	}

	WHEN("передается текст c пробелами между слов")
	{
		std::string result = CutSpaces("text1 text2");

		THEN("должен вернуться текст c пробелами между слов")
		{
			REQUIRE(result == "text1 text2");
		}
	}

	WHEN("передается текст c пробелами до и после слова")
	{
		std::string result = CutSpaces("     text      ");

		THEN("должен вернуться текст без пробелов")
		{
			REQUIRE(result == "text");
		}
	}

	WHEN("передается текст c пробелами до, между и после слов")
	{
		std::string result = CutSpaces("     text1      text2       ");

		THEN("должен вернуться текст с одним пробелом между словами")
		{
			REQUIRE(result == "text1 text2");
		}
	}
}

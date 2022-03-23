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

SCENARIO("Проверка функции ConvertTextToLowCase")
{
	WHEN("передается пустая строка")
	{
		std::string result = ConvertTextToLowCase("");

		THEN("должна вернуться пустая строка")
		{
			REQUIRE(result == "");
		}
	}

	WHEN("передается текст из латинских символов в нижнем регистре")
	{
		std::string result = ConvertTextToLowCase("text");

		THEN("должна вернуться текст из латинских символов в нижнем регистре")
		{
			REQUIRE(result == "text");
		}
	}

	WHEN("передается текст из латинских символов в нижнем и верхнем регистре")
	{
		std::string result = ConvertTextToLowCase("TeXt");

		THEN("должна вернуться текст из латинских символов в нижнем регистре")
		{
			REQUIRE(result == "text");
		}
	}

	WHEN("передается текст содержащий все буквы латинского алфавита в верхнем регистре")
	{
		std::string result = ConvertTextToLowCase("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

		THEN("должна вернуться текст содержащий все буквы латинского алфавита в нижнем регистре")
		{
			REQUIRE(result == "abcdefghijklmnopqrstuvwxyz");
		}
	}

	WHEN("передается текст из кириллицы в нижнем регистре")
	{
		std::string result = ConvertTextToLowCase("текст");

		THEN("должна вернуться текст из кириллицы в нижнем регистре")
		{
			REQUIRE(result == "текст");
		}
	}

	WHEN("передается текст из кириллицы в нижнем и верхнем регистре")
	{
		std::string result = ConvertTextToLowCase("ТеКсТ");

		THEN("должна вернуться текст из кириллицы в нижнем регистре")
		{
			REQUIRE(result == "текст");
		}
	}

	WHEN("передается текст содержащий все буквы русского алфавита в верхнем регистре")
	{
		std::string result = ConvertTextToLowCase("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");

		THEN("должна вернуться текст содержащий все буквы латинского алфавита в нижнем регистре")
		{
			REQUIRE(result == "абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
		}
	}

	WHEN("передается русский и английский текст в разном регистре")
	{
		std::string result = ConvertTextToLowCase("СлоВо Ёжик на АнГлийСкоМ - heDgEhOG");

		THEN("должна вернуться текст содержащий все буквы латинского алфавита в нижнем регистре")
		{
			REQUIRE(result == "слово ёжик на английском - hedgehog");
		}
	}
}

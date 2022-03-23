// dictionary_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../dictionary/dicfns.h"
#include <string>

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

		THEN("должен вернуться текст из латинских символов в нижнем регистре")
		{
			REQUIRE(result == "text");
		}
	}

	WHEN("передается текст из латинских символов в нижнем и верхнем регистре")
	{
		std::string result = ConvertTextToLowCase("TeXt");

		THEN("должен вернуться текст из латинских символов в нижнем регистре")
		{
			REQUIRE(result == "text");
		}
	}

	WHEN("передается текст содержащий все буквы латинского алфавита в верхнем регистре")
	{
		std::string result = ConvertTextToLowCase("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

		THEN("должен вернуться текст содержащий все буквы латинского алфавита в нижнем регистре")
		{
			REQUIRE(result == "abcdefghijklmnopqrstuvwxyz");
		}
	}

	WHEN("передается текст из кириллицы в нижнем регистре")
	{
		std::string result = ConvertTextToLowCase("текст");

		THEN("должен вернуться текст из кириллицы в нижнем регистре")
		{
			REQUIRE(result == "текст");
		}
	}

	WHEN("передается текст из кириллицы в нижнем и верхнем регистре")
	{
		std::string result = ConvertTextToLowCase("ТеКсТ");

		THEN("должен вернуться текст из кириллицы в нижнем регистре")
		{
			REQUIRE(result == "текст");
		}
	}

	WHEN("передается текст содержащий все буквы русского алфавита в верхнем регистре")
	{
		std::string result = ConvertTextToLowCase("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");

		THEN("должен вернуться текст содержащий все буквы русского алфавита в нижнем регистре")
		{
			REQUIRE(result == "абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
		}
	}

	WHEN("передается русский и английский текст в разном регистре")
	{
		std::string result = ConvertTextToLowCase("СлоВо Ёжик на АнГлийСкоМ - heDgEhOG");

		THEN("должен вернуться русский и английский текст в нижнем регистре")
		{
			REQUIRE(result == "слово ёжик на английском - hedgehog");
		}
	}
}

SCENARIO("Проверка функции CreateTranslationUnit")
{
	WHEN("передается пара key и translation")
	{
		std::string key = "cat";
		std::string translation = "кошка";
		std::pair<std::string, std::string> result = CreateTranslationUnit(key, translation);

		THEN("должнен вернуться объект pair из заданных ключа и перевода")
		{
			REQUIRE(result.first == key);
			REQUIRE(result.second == translation);
		}
	}
}

SCENARIO("Проверка функции ParseLine")
{
	WHEN("передается строка в формате хранения данных с одним переводом")
	{
		std::string line = "[cat] кошка";
		std::pair<std::string, std::string> result = ParseLine(line);

		THEN("должнен вернуться объект pair из заданных ключа в квадратных скобках и перевода")
		{
			REQUIRE(result.first == "cat");
			REQUIRE(result.second == "кошка");
		}
	}

	WHEN("передается строка в формате хранения данных с несколькими переводами через запятую")
	{
		std::string line = "[cat] кот, кошка, кошечка";
		std::pair<std::string, std::string> result = ParseLine(line);

		THEN("должнен вернуться объект pair из заданных ключа в квадратных скобках и строки с переводами")
		{
			REQUIRE(result.first == "cat");
			REQUIRE(result.second == "кот, кошка, кошечка");
		}
	}

	WHEN("передается строка в формате хранения данных в которой key - русское слово, в переводе - английское")
	{
		std::string line = "[кот] cat";
		std::pair<std::string, std::string> result = ParseLine(line);

		THEN("должнен вернуться объект pair из заданных ключа в квадратных скобках и строки с переводами")
		{
			REQUIRE(result.first == "кот");
			REQUIRE(result.second == "cat");
		}
	}
}

SCENARIO("Проверка функции InitDictionary")
{
	WHEN("передается название файла на несуществующий словарик")
	{
		std::string fileName = "dic-not-exist.txt";
		std::map<std::string, std::string> result = InitDictionary(fileName);

		THEN("вернется пустой контейнер map")
		{
			REQUIRE(result.size() == 0);
		}
	}

	WHEN("передается название файла на пустой словарик")
	{
		std::string fileName = "dic-empty.txt";
		std::map<std::string, std::string> result = InitDictionary(fileName);

		THEN("вернется пустой контейнер map")
		{
			REQUIRE(result.size() == 0);
		}
	}

	WHEN("передается название файла с данными словаря из 2х элементов")
	{
		std::string fileName = "dic.txt";
		std::map<std::string, std::string> result = InitDictionary(fileName);

		THEN("вернется контейнер map с 2мя элементами и нужными полями")
		{
			REQUIRE(result.size() == 2);
			REQUIRE(result["red"] == "красный");
			REQUIRE(result["кот"] == "cat");
		}
	}

	WHEN("передается название файла с данными словаря из 2х элементов и пустыми строками")
	{
		std::string fileName = "dic-empty-lines.txt";
		std::map<std::string, std::string> result = InitDictionary(fileName);

		THEN("вернется контейнер map с 2мя элементами и нужными полями")
		{
			REQUIRE(result.size() == 2);
			REQUIRE(result["red"] == "красный");
			REQUIRE(result["кот"] == "cat");
		}
	}
}

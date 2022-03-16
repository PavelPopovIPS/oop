// HtmlEncode_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../string/HtmlEncode.h"
#include <string>

SCENARIO("Тестирование HtmlEncode")
{
	WHEN("передается пустая строка")
	{
		std::string emptyStr = "";

		THEN("должна вернуться пустая строка")
		{
			REQUIRE(HtmlEncode(emptyStr) == "");
		}
	}	
	
	WHEN("передается строка с допустимыми символами")
	{
		std::string str = "abc123";

		THEN("должна вернуться строка с такими же символами")
		{
			REQUIRE(HtmlEncode(str) == "abc123");
		}
	}	

	WHEN("передается один символ Стрелка влево(<)")
	{
		std::string str = "<";

		THEN("символ должен быть закодирован")
		{
			REQUIRE(HtmlEncode(str) == "&lt;");
		}
	}

	WHEN("передается один символ Стрелка вправо(>)")
	{
		std::string str = ">";

		THEN("символ должен быть закодирован")
		{
			REQUIRE(HtmlEncode(str) == "&gt;");
		}
	}

	WHEN("передается один символ двойная кавычка(\")")
	{
		std::string str = "\"";

		THEN("символ должен быть закодирован")
		{
			REQUIRE(HtmlEncode(str) == "&quot;");
		}
	}

	WHEN("передается один символ апостроф(\')")
	{
		std::string str = "\'";

		THEN("символ должен быть закодирован")
		{
			REQUIRE(HtmlEncode(str) == "&apos;");
		}
	}

	WHEN("передается один символ амперсанд(&)")
	{
		std::string str = "&";

		THEN("символ должен быть закодирован")
		{
			REQUIRE(HtmlEncode(str) == "&amp;");
		}
	}

	WHEN("передаются все запрещенные символы")
	{
		std::string str = "<>\"\'&";

		THEN("все символы должны быть закодированы")
		{
			REQUIRE(HtmlEncode(str) == "&lt;&gt;&quot;&apos;&amp;");
		}
	}

	WHEN("передается строка с запрещенными и допустимыми символами")
	{
		std::string str = "Cat <says> \"Meow\". M&M\'s ";

		THEN("кодируются только нужные символы")
		{
			REQUIRE(HtmlEncode(str) == "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s ");
		}
	}
}

SCENARIO("Тестирование ReplaceText")
{
	WHEN("передается строка с нужным символом, номером позиции этого символа и строкой, на которую должен замениться указанный символ")
	{
		std::string str = "Hello world";
		size_t found = 4;
		const std::string replaceStr = "123";

		ReplaceText(str, found, replaceStr);

		THEN("символ заменится на новую строку")
		{
			REQUIRE(str == "Hell123 world");
		}
	}
}
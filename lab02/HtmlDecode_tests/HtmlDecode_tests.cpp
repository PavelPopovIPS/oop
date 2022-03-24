// HtmlDecode_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../HtmlDecode/HtmlDecode.h"
#include <string>

SCENARIO("Тестирование HtmlDecode")
{
	WHEN("передается пустая строка")
	{
		std::string emptyStr = "";

		THEN("должна вернуться пустая строка")
		{
			REQUIRE(HtmlDecode(emptyStr) == "");
		}
	}

	WHEN("передается строка c закодированным символом LEFT_ARROW_CODE (&lt;)")
	{
		std::string str = "&lt;";

		THEN("должна вернуться строка, содержащая стрелку влево (<)")
		{
			REQUIRE(HtmlDecode(str) == "<");
		}
	}

	WHEN("передается строка c закодированным символом RIGHT_ARROW_CODE (&gt;)")
	{
		std::string str = "&gt;";

		THEN("должна вернуться строка, содержащая стрелку вправо (>)")
		{
			REQUIRE(HtmlDecode(str) == ">");
		}
	}

	WHEN("передается строка c закодированным символом QUOTES_CODE (&quot;)")
	{
		std::string str = "&quot;";

		THEN("должна вернуться строка, содержащая кавычку (\")")
		{
			REQUIRE(HtmlDecode(str) == "\"");
		}
	}

	WHEN("передается строка c закодированным символом APOSTROPHE_CODE (&apos;)")
	{
		std::string str = "&apos;";

		THEN("должна вернуться строка, содержащая апостраф (\')")
		{
			REQUIRE(HtmlDecode(str) == "\'");
		}
	}

	WHEN("передается строка c закодированным символом AMPERSAND_CODE (&amp;)")
	{
		std::string str = "&amp;";

		THEN("должна вернуться строка, содержащая асперсанд (&)")
		{
			REQUIRE(HtmlDecode(str) == "&");
		}
	}

	WHEN("передается строка cодержащая несколько закодированных символов")
	{
		std::string str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";

		THEN("должна вернуться строка с раскодированными символами")
		{
			REQUIRE(HtmlDecode(str) == "Cat <says> \"Meow\". M&M\'s");
		}
	}

	WHEN("передается строка не содержащая закодированные символы")
	{
		std::string str = "abc123";

		THEN("должна вернуться эта же строка, без изменений")
		{
			REQUIRE(HtmlDecode(str) == "abc123");
		}
	}

	WHEN("передается строка cодержащая только код амперсанда")
	{
		std::string str = "&amp";

		THEN("должна вернуться эта же строка, без изменений")
		{
			REQUIRE(HtmlDecode(str) == "&amp");
		}
	}

	WHEN("передается строка cодержащая амперсанд и закодированный символ после амперсанда")
	{
		std::string str = "&&amp;";

		THEN("должна вернуться строка, содержащая 2 амперсанда")
		{
			REQUIRE(HtmlDecode(str) == "&&");
		}
	}
}

SCENARIO("Тестирование ReplaceText")
{
	WHEN("передается строка с позицией заменяемого закодированного символа")
	{
		std::string str = "10&gt;1";
		std::string code = "&gt;";
		size_t found = 2;
		ReplaceText(str, found, code.length(), ">");

		THEN("в строке должен замениться код на нужный символ")
		{
			REQUIRE(str == "10>1");
		}
	}
}

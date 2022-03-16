// HtmlEncode_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../string/HtmlEncode.h"
#include <string>

SCENARIO("������������ HtmlEncode")
{
	WHEN("���������� ������ ������")
	{
		std::string emptyStr = "";

		THEN("������ ��������� ������ ������")
		{
			REQUIRE(HtmlEncode(emptyStr) == "");
		}
	}	
	
	WHEN("���������� ������ � ����������� ���������")
	{
		std::string str = "abc123";

		THEN("������ ��������� ������ � ������ �� ���������")
		{
			REQUIRE(HtmlEncode(str) == "abc123");
		}
	}	

	WHEN("���������� ���� ������ ������� �����(<)")
	{
		std::string str = "<";

		THEN("������ ������ ���� �����������")
		{
			REQUIRE(HtmlEncode(str) == "&lt;");
		}
	}

	WHEN("���������� ���� ������ ������� ������(>)")
	{
		std::string str = ">";

		THEN("������ ������ ���� �����������")
		{
			REQUIRE(HtmlEncode(str) == "&gt;");
		}
	}

	WHEN("���������� ���� ������ ������� �������(\")")
	{
		std::string str = "\"";

		THEN("������ ������ ���� �����������")
		{
			REQUIRE(HtmlEncode(str) == "&quot;");
		}
	}

	WHEN("���������� ���� ������ ��������(\')")
	{
		std::string str = "\'";

		THEN("������ ������ ���� �����������")
		{
			REQUIRE(HtmlEncode(str) == "&apos;");
		}
	}

	WHEN("���������� ���� ������ ���������(&)")
	{
		std::string str = "&";

		THEN("������ ������ ���� �����������")
		{
			REQUIRE(HtmlEncode(str) == "&amp;");
		}
	}

	WHEN("���������� ��� ����������� �������")
	{
		std::string str = "<>\"\'&";

		THEN("��� ������� ������ ���� ������������")
		{
			REQUIRE(HtmlEncode(str) == "&lt;&gt;&quot;&apos;&amp;");
		}
	}

	WHEN("���������� ������ � ������������ � ����������� ���������")
	{
		std::string str = "Cat <says> \"Meow\". M&M\'s ";

		THEN("���������� ������ ������ �������")
		{
			REQUIRE(HtmlEncode(str) == "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s ");
		}
	}
}
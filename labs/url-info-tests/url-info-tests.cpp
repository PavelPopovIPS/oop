#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../url-info/HttpUrl.h"
#include "../url-info/UrlParsingError.h"

SCENARIO("Protocol should be define")
{
	WHEN("protocol is http://")
	{
		CHttpUrl httpUrl("http://ispring.ru");

		THEN("it should be define as http")
		{
			Protocol expectedResult = Protocol::HTTP;
			REQUIRE(httpUrl.GetProtocol() == expectedResult);
		}
	}

	WHEN("protocol is https://")
	{
		CHttpUrl httpUrl("https://ispring.ru");

		THEN("it should be define as https")
		{
			Protocol expectedResult = Protocol::HTTPS;
			REQUIRE(httpUrl.GetProtocol() == expectedResult);
		}
	}
}

SCENARIO("Try parse incorrect protocol")
{
	WHEN("there is no protocol")
	{
		THEN("it should throw exception CUrlParsingError")
		{
			try
			{
				CHttpUrl httpUrl("ispring.ru");
				REQUIRE(FALSE);
			}
			catch (CUrlParsingError& e)
			{
				std::string expectedResult = "Protocol was not defined\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("there is incorrect protocol")
	{
		THEN("it should throw exception CUrlParsingError")
		{
			try
			{
				CHttpUrl httpUrl("http:ispring.ru");
				REQUIRE(FALSE);
			}
			catch (CUrlParsingError& e)
			{
				std::string expectedResult = "Protocol was not defined\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("url is empty")
	{
		THEN("it should throw exception CUrlParsingError")
		{
			try
			{
				CHttpUrl httpUrl("");
				REQUIRE(FALSE);
			}
			catch (CUrlParsingError& e)
			{
				std::string expectedResult = "Protocol was not defined\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}
}

SCENARIO("Document should be define")
{
	WHEN("document is exist")
	{
		CHttpUrl httpUrl("http://ispring.ru/index.html");

		THEN("document is /index.html")
		{
			std::string expectedResult = "/index.html";
			REQUIRE(httpUrl.GetDocument() == expectedResult);
		}
	}

	WHEN("document is not exist")
	{
		CHttpUrl httpUrl("http://ispring.ru");

		THEN("document is /")
		{
			std::string expectedResult = "/";
			REQUIRE(httpUrl.GetDocument() == expectedResult);
		}
	}

	WHEN("document is /")
	{
		CHttpUrl httpUrl("http://ispring.ru/");

		THEN("document is /")
		{
			std::string expectedResult = "/";
			REQUIRE(httpUrl.GetDocument() == expectedResult);
		}
	}
}

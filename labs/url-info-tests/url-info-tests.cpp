#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../url-info/HttpUrl.h"
#include "../url-info/UrlParsingError.h"

SCENARIO("Protocol should be define")
{
	WHEN("protocol is http://")
	{
		std::string url = "http://ispring.ru";

		THEN("it should be define as http")
		{
			Protocol result = ParseProtocol(url);

			Protocol expectedResult = Protocol::HTTP;
			REQUIRE(result == expectedResult);
		}

		THEN("url should be without protocol")
		{
			Protocol result = ParseProtocol(url);

			std::string expectedResult = "ispring.ru";
			REQUIRE(url == expectedResult);
		}
	}

	WHEN("protocol is https://")
	{
		std::string url = "https://ispring.ru";

		THEN("it should be define as https")
		{
			Protocol result = ParseProtocol(url);

			Protocol expectedResult = Protocol::HTTPS;
			REQUIRE(result == expectedResult);
		}

		THEN("url should be without protocol")
		{
			Protocol result = ParseProtocol(url);

			std::string expectedResult = "ispring.ru";
			REQUIRE(url == expectedResult);
		}
	}
}

SCENARIO("Try parse incorrect protocol")
{
	WHEN("there is no protocol")
	{
		std::string url = "ispring.ru";

		THEN("it should throw exception CUrlParsingError")
		{
			try
			{
				Protocol result = ParseProtocol(url);
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
		std::string url = "http:ispring.ru";

		THEN("it should throw exception CUrlParsingError")
		{
			try
			{
				Protocol result = ParseProtocol(url);
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
		std::string url = "";

		THEN("it should throw exception CUrlParsingError")
		{
			try
			{
				Protocol result = ParseProtocol(url);
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

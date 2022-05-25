#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../url-info/HttpUrl.h"
#include "../url-info/UrlParsingError.h"

//	CHttpUrl(std::string const& url);
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

SCENARIO("Define port")
{
	WHEN("there is port and no document")
	{
		CHttpUrl httpUrl("http://ispring.ru:1");

		THEN("port is 1")
		{
			unsigned short expectedResult = 1;
			REQUIRE(httpUrl.GetPort() == expectedResult);
		}
	}

	WHEN("there are port and  document")
	{
		CHttpUrl httpUrl("http://ispring.ru:65535/index.html");

		THEN("port is 65536")
		{
			unsigned short expectedResult = 65535;
			REQUIRE(httpUrl.GetPort() == expectedResult);
		}
	}

	WHEN("port is not exist")
	{
		THEN("for http port is 80")
		{
			CHttpUrl httpUrl("http://ispring.ru/index.html");

			unsigned short expectedResult = 80;
			REQUIRE(httpUrl.GetPort() == expectedResult);
		}

		THEN("for https port is 443")
		{
			CHttpUrl httpUrl("https://ispring.ru/index.html");

			unsigned short expectedResult = 443;
			REQUIRE(httpUrl.GetPort() == expectedResult);
		}
	}

	WHEN("port is not exist, only symbol :,it means that port not exist")
	{
		THEN("for http port is 80")
		{
			CHttpUrl httpUrl("http://ispring.ru:/index.html");

			unsigned short expectedResult = 80;
			REQUIRE(httpUrl.GetPort() == expectedResult);
		}

		THEN("for https port is 443")
		{
			CHttpUrl httpUrl("https://ispring.ru:/index.html");

			unsigned short expectedResult = 443;
			REQUIRE(httpUrl.GetPort() == expectedResult);
		}
	}

	WHEN("port is 0")
	{
		THEN("should be error")
		{
			try
			{
				CHttpUrl httpUrl("http://ispring.ru:0/index.html");
				REQUIRE(FALSE);
			}
			catch (CUrlParsingError& e)
			{
				std::string expectedResult = "Port should be between 1 and 65535\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("port is 65536")
	{
		THEN("should be error")
		{
			try
			{
				CHttpUrl httpUrl("http://ispring.ru:65536");
				REQUIRE(FALSE);
			}
			catch (CUrlParsingError& e)
			{
				std::string expectedResult = "Port should be between 1 and 65535\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("port is alphabet")
	{
		THEN("should be error")
		{
			try
			{
				CHttpUrl httpUrl("http://ispring.ru:abc");
				REQUIRE(FALSE);
			}
			catch (CUrlParsingError& e)
			{
				std::string expectedResult = "Port was not correct\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("port is too long")
	{
		THEN("should be error")
		{
			try
			{
				CHttpUrl httpUrl("http://ispring.ru:99999999999999999999999999999999999999");
				REQUIRE(FALSE);
			}
			catch (CUrlParsingError& e)
			{
				std::string expectedResult = "Port was not correct\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}
}

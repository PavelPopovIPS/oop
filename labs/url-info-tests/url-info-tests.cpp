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

SCENARIO("Define domain")
{
	WHEN("domain is correct whithout document and port")
	{
		CHttpUrl httpUrl("http://ispring.ru");

		THEN("domain is ispring.ru")
		{
			std::string expectedResult = "ispring.ru";
			REQUIRE(httpUrl.GetDomain() == expectedResult);
		}
	}

	WHEN("domain is correct whith document and port")
	{
		CHttpUrl httpUrl("http://www.ispring.ru:50/document/index.html");

		THEN("domain is www.ispring.ru")
		{
			std::string expectedResult = "www.ispring.ru";
			REQUIRE(httpUrl.GetDomain() == expectedResult);
		}
	}

	WHEN("domain does not exist")
	{
		THEN("should be throw error")
		{
			try
			{
				CHttpUrl httpUrl("http://:50/document/index.html");
			}
			catch (CUrlParsingError& e)
			{
				std::string expectedResult = "Domain can not be empty\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}

	WHEN("domain contains reserved symbols")
	{
		THEN("should be throw error")
		{
			try
			{
				CHttpUrl httpUrl("http://www.ispring>ru");
			}
			catch (CUrlParsingError& e)
			{
				std::string expectedResult = "Domain contains incorrect symbols\n";
				REQUIRE(e.what() == expectedResult);
			}
		}
	}
}

// methods
SCENARIO("Object should return url correct url")
{
	WHEN("url is long http://www.ispring.ru:31/document/index.html")
	{
		CHttpUrl httpUrl("http://www.ispring.ru:31/document/index.html");

		THEN("url should be same")
		{
			std::string result = httpUrl.GetURL();
			std::string expectedResult = "http://www.ispring.ru:31/document/index.html";
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("url is short with symbol / at the end http://www.ispring.ru")
	{
		CHttpUrl httpUrl("http://www.ispring.ru");

		THEN("url should be with symbol / at the end http://www.ispring.ru/")
		{
			std::string result = httpUrl.GetURL();
			std::string expectedResult = "http://www.ispring.ru/";
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("port has : http://www.ispring.ru:")
	{
		CHttpUrl httpUrl("http://www.ispring.ru:");

		THEN("url should be with symbol / at the end http://www.ispring.ru/")
		{
			std::string result = httpUrl.GetURL();
			std::string expectedResult = "http://www.ispring.ru/";
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("port is standard 80 for http protocol http://www.ispring.ru:80/")
	{
		CHttpUrl httpUrl("http://www.ispring.ru:80/");

		THEN("url should be without standard port http://www.ispring.ru/")
		{
			std::string result = httpUrl.GetURL();
			std::string expectedResult = "http://www.ispring.ru/";
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("port is standard 443 for https protocol https://www.ispring.ru:443/")
	{
		CHttpUrl httpUrl("https://www.ispring.ru:443/");

		THEN("url should be without standard port https://www.ispring.ru/")
		{
			std::string result = httpUrl.GetURL();
			std::string expectedResult = "https://www.ispring.ru/";
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("port is not standard for https protocol https://www.ispring.ru:80")
	{
		CHttpUrl httpUrl("https://www.ispring.ru:80");

		THEN("url should containe port https://www.ispring.ru:80/")
		{
			std::string result = httpUrl.GetURL();
			std::string expectedResult = "https://www.ispring.ru:80/";
			REQUIRE(result == expectedResult);
		}
	}

	WHEN("port is not standard for http protocol http://www.ispring.ru:443")
	{
		CHttpUrl httpUrl("http://www.ispring.ru:443");

		THEN("url should containe port http://www.ispring.ru:443/")
		{
			std::string result = httpUrl.GetURL();
			std::string expectedResult = "http://www.ispring.ru:443/";
			REQUIRE(result == expectedResult);
		}
	}
}

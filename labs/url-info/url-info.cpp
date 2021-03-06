// url-info.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "HttpUrl.h"
#include <iostream>
#include <string>

void PrintUrl(const CHttpUrl& httpUrl)
{
	std::cout << "URL is: " << httpUrl.GetURL() << std::endl;

	std::cout << "Protocol is: ";

	if (httpUrl.GetProtocol() == Protocol::HTTP)
	{
		std::cout << "http" << std::endl;
	}

	if (httpUrl.GetProtocol() == Protocol::HTTPS)
	{
		std::cout << "https" << std::endl;
	}

	std::cout << "Domain is: " << httpUrl.GetDomain() << std::endl;
	std::cout << "Port is: " << httpUrl.GetPort() << std::endl;
	std::cout << "Document is: " << httpUrl.GetDocument() << std::endl;
	std::cout << std::endl;
}

int main()
{
	std::string url;

	while (std::getline(std::cin, url))
	{
		try
		{
			CHttpUrl httpUrl(url);
			PrintUrl(httpUrl);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}

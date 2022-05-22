// url-info.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "HttpUrl.h"
#include <iostream>
#include <string>

int main()
{
	std::string url;

	while (std::getline(std::cin, url))
	{
		ParseProtocol(url);
		ParseDocument(url);

		std::cout << "url: " << url << std::endl;
		std::cout << std::endl;
	}

	return 0;
}

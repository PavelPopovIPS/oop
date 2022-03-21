// dictionary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>
#include "./dicfns.h"

struct Args
{
	std::string dicFileName;
};

Args ParseArgs(int argv, char* argc[])
{
	if (argv != 2)
	{
		throw std::runtime_error("Invalid argument count\nFor use: dictionary.exe <dictionary file name>\n";
	}
}


std::map<std::string, std::string> InitDictionary()
{
}

int main(int argv, char* argc[])
{
	try
	{
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

// dictionary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "./dicfns.h"
#include <iostream>
#include <map>
#include <string>

struct Args
{
	std::string dicFileName;
};

Args ParseArgs(int argv, char* argc[])
{
	if (argv != 2)
	{
		throw std::runtime_error("Invalid argument count\nFor use: dictionary.exe <dictionary file name>\n");
	}

	Args args;
	args.dicFileName = argc[1];
	if (args.dicFileName == "")
	{
		throw std::runtime_error("Dictionary file name can not be empty\n");
	}

	return args;
}

int main(int argv, char* argc[])
{
	try
	{
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}

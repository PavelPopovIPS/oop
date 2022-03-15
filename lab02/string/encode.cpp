// string.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "HtmlEncode.h"
#include <iostream>
#include <string>

std::string ReadInput()
{
	std::string text;
	std::getline(std::cin, text);
	return text;
}

void PrintText(std::string& text)
{
	std::cout << text << std::endl;
}

int main()
{
	try
	{
		std::string text = ReadInput();
		std::string encodeText = HtmlEncode(text);
		PrintText(encodeText);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}

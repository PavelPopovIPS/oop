// wordCount.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

std::string ReadInput()
{
	std::string text;
	std::getline(std::cin, text);
	return text;
}

int main()
{
	std::string text = ReadInput();
}

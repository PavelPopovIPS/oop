// MyListApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CMyList.h"
#include <iostream>
#include <string>

int main()
{
	CMyList<int> listNum;
	listNum.push_front(2);
	listNum.push_back(4);
	listNum.push_back(5);
	auto itnum = listNum.begin();
	++itnum;
	listNum.insert(itnum, 3);

	std::cout << "List of numbers:" << std::endl;
	for (itnum = listNum.begin(); itnum != listNum.end(); ++itnum)
	{
		std::cout << *itnum << std::endl;
	}
	std::cout << "Size is " << listNum.size() << std::endl;

	std::cout << std::endl;

	CMyList<std::string> listStr;
	listStr.push_front("a");
	listStr.push_back("c");
	auto itstr = listStr.begin();
	++itstr;
	listStr.insert(itstr, "b");

	std::cout << "List of strings:" << std::endl;
	for (itstr = listStr.begin(); itstr != listStr.end(); ++itstr)
	{
		std::cout << *itstr << std::endl;
	}
	std::cout << "Size is " << listStr.size() << std::endl;
}

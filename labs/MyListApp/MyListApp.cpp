// MyListApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CMyList.h"
#include <iostream>
#include <list>
#include <string>

int main()
{
	CMyList<int> listNum;
	listNum.PushFront(2);
	listNum.PushBack(4);
	listNum.PushBack(5);
	auto itnum = listNum.begin();
	itnum++;
	listNum.Insert(itnum, 3);

	std::cout << "List of numbers:" << std::endl;
	for (itnum = listNum.begin(); itnum != listNum.end(); ++itnum)
	{
		std::cout << *itnum << std::endl;
	}
	std::cout << "Size is " << listNum.Size() << std::endl;

	std::cout << std::endl;

	CMyList<std::string> listStr;
	listStr.PushFront("a");
	listStr.PushBack("c");
	auto itstr = listStr.begin();
	++itstr;
	listStr.Insert(itstr, "b");

	std::cout << "List of strings:" << std::endl;
	for (itstr = listStr.begin(); itstr != listStr.end(); ++itstr)
	{
		std::cout << *itstr << std::endl;
	}
	std::cout << "Size is " << listStr.Size() << std::endl;

	std::cout << std::endl;

	CMyList<std::string> listStr2;
	listStr2.PushFront("a");
	listStr2.PushBack("c");
	auto itstr2 = listStr2.rbegin();
}

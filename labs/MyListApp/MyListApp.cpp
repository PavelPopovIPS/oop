// MyListApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CMyList.h"
#include <iostream>
#include <sstream>
#include <string>

int main()
{
	CMyList<int> list;
	list.Push_front(5);
	list.Push_front(3);
	list.Push_front(1);
	list.Push_back(7);
	list.Push_back(8);
	std::cout << list;
	std::cout << std::endl
			  << std::endl;

	CMyList<const char*> strList;
	strList.Push_front("ab");
	strList.Push_back("cd");
	std::cout << strList;
}

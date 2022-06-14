// MyListApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CMyList.h"
#include <iostream>
#include <list>
#include <sstream>
#include <string>

int main()
{
	CMyList<int> list;
	list.push_front(3);
	list.push_front(5);
	// auto it = list.begin();

	for (auto it = list.begin(); it != list.end(); ++it)
	{
		std::cout << "Main *it is " << *it << std::endl;
	}
	std::cout << "size " << list.size() << std::endl;
}

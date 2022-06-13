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
	list.push_back(5);
	list.push_back(7);
	list.push_back(10);

	auto it = list.begin();
	++it;
	++it;
	list.insert(it, 4);
	for (it = list.begin(); it != list.end(); ++it)
	{
		std::cout << "Main *it2 is " << *it << std::endl;
	}
	std::cout << "Main *it2 is " << *it << std::endl;
	std::cout << "size " << list.size() << std::endl;
}

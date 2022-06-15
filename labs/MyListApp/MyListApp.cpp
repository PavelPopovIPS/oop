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
	list.push_back(2);
	list.push_back(4);
	list.push_back(5);
	auto it = list.begin();
	++it;
	list.insert(it, 3);

	list.erase(it);

	for (it = list.begin(); it != list.end(); ++it)
	{
		std::cout << "Main *it is " << *it << std::endl;
	}
	std::cout << "size " << list.size() << std::endl;
	auto it2 = list.rend();
	std::cout << "Main *it2 is " << *it2 << std::endl;

	// std::list<int> l;
	// auto it = l.begin();
	// l.insert(it, 2);
	// it = l.begin();

	// std::cout << "std list " << *it << std::endl;
}

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
	list.push_front(5);
	// list.push_front(3);
	auto it = list.begin();
	int x = *it;
	int x2 = *it;
	// std::cout << "Main get value1 is " << it.getValue() << std::endl;
	// std::cout << "Main get value2 is " << it.getValue() << std::endl;
	std::cout << "Main x is " << x << std::endl;
	std::cout << "Main x2 is " << x2 << std::endl;
	std::cout << "Main *it is " << (*it) << std::endl;
	std::cout << "Main Size is " << list.Size() << std::endl;

	// std::list<int> stdlist;
	// stdlist.push_front(1);
	// stdlist.push_front(2);
	// auto it = stdlist.begin();
	// it++;
	// it++;
	// std::cout << *it;
}

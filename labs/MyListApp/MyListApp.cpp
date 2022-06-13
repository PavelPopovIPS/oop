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
	auto it = list.begin();
	auto it2 = list.end();

	std::cout << "Main *it is " << *it << std::endl;
	std::cout << "Main *it2 is " << *it2 << std::endl;
	std::cout << "size " << list.size() << std::endl;

	// std::list<int> stdlist;
	// stdlist.push_front(1);
	// stdlist.push_front(2);
	// auto stdit = stdlist.begin();
	// stdit++;
	// std::cout << *stdit;
}

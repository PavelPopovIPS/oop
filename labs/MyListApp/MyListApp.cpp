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
	auto it = list.begin();
	auto x = *it;
	auto x2 = *it;

	std::cout << "Main x is " << x << std::endl;
	std::cout << "Main x2 is " << x2 << std::endl;
	std::cout << "Main *it is " << *it << std::endl;

	// std::list<int> stdlist;
	// stdlist.push_front(1);
	// stdlist.push_front(2);
	// auto stdit = stdlist.begin();
	// stdit++;
	// std::cout << *stdit;
}

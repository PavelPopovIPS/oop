// MyListApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CMyList.h"
#include <iostream>
#include <sstream>

int main()
{
	CMyList<int> list;
	list.Push_front(1);
	list.Push_front(5);

	std::cout << list;
}

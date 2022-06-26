// examTasks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

struct Person
{
	std::string firstName;
	std::string lastName;
	unsigned short age;
};

int main()
{
	// 1 +
	std::vector<int> v{ 11, 17, 23, 57, 6, 19, 7 };
	auto result = std::find_if(v.begin(), v.end(), [](int i) { return i % 2 == 0; });
	std::cout << *result << std::endl;

	// 2 +
	std::sort(v.begin(), v.end());

	int findElem = 38;
	if (std::binary_search(v.begin(), v.end(), findElem))
	{
		std::cout << "Found " << findElem << std::endl;
	}
	else
	{
		std::cout << "Not found!" << std::endl;
	}

	// 3
	std::vector<Person> people = {
		{ "Ivan", "Ivanov", 35 },
		{ "Petr", "Petrov", 15 },
		{ "John", "Johnson", 45 },
	};

	std::vector<std::string> peopleInfo;
	std::transform(people.begin(), people.end(), std::back_inserter(peopleInfo),
		[](Person& person) { return person.firstName + " " + person.lastName; });

	for (auto& raw : peopleInfo)
	{
		std::cout << raw << std::endl;
	}

	// 4
	// n_th_elements

	// 5
	std::vector<int> b{ 11, 17, 23, 57, 6, 19, 7 };
	std::partial_sort(b.rbegin(), b.rbegin() + 3, b.rend(), std::greater<int>());

	auto it = b.rbegin();
	for (int i = 0; i < 3; i++)
	{
		std::cout << *it << std::endl;
		it++;
	}
}

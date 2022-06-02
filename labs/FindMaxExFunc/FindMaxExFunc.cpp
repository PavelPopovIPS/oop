// FindMaxExFunc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <functional>
#include <iostream>
#include <string>
#include <vector>

struct Athlete
{
	std::string name;
	size_t tall;
	size_t weight;
};

// using LessFn = std::function<bool(const Athlete&, const Athlete&)>;

template <typename T, typename Less = std::less<T>>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.size() == 0) // empty()
	{
		return false;
	}

	maxValue = arr[0];

	for (auto& item : arr)
	{
		if (less(item, maxValue))
		{
			maxValue = item;
		}
	}

	return true;
}

bool CompareAthletes(const Athlete& a1, const Athlete& a2)
{
	if (a1.name < a2.name)
	{
		return true;
	}

	if (a1.tall < a2.tall)
	{
		return true;
	}

	if (a1.weight < a2.weight)
	{
		return true;
	}

	return false;
}

int main()
{
	std::vector<Athlete> athletes = {
		{ "Ivan", 180, 80 },
		{ "Peter", 161, 50 },
		{ "Paul", 170, 100 },
		{ "John", 175, 75 },
	};

	Athlete maxAthlete;

	std::cout << FindMax(athletes, maxAthlete, CompareAthletes) << std::endl;
	std::cout << maxAthlete.name;

	std::vector<int> numbers;
	int number;
	if (FindMax(numbers, number, std::greater<int>()))
	{
	}
}

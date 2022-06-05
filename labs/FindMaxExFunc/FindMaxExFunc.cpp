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

	bool operator<(const Athlete& athlete) const
	{
		return std::tie(name, tall, weight) < std::tie(athlete.name, athlete.tall, athlete.weight);
	}
};

template <typename T, typename Less = std::less<T>>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = Less())
{
	if (arr.empty())
	{
		return false;
	}

	auto pmaxValue = &arr[0];

	for (auto& item : arr)
	{
		if (less(*pmaxValue, item))
		{
			pmaxValue = &item;
		}
	}

	maxValue = *pmaxValue;
	return true;
}

bool CompairAthletes(const Athlete& a1, const Athlete& a2)
{
	return (a1 < a2);
}

bool CompareTall(const Athlete& a1, const Athlete& a2)
{
	return (a1.tall < a2.tall);
}

bool CompareWeight(const Athlete& a1, const Athlete& a2)
{
	return (a1.weight < a2.weight);
}

int main()
{
	std::vector<Athlete> athletes = {
		{ "Ivan", 180, 80 },
		{ "Elly", 161, 50 },
		{ "Paul", 170, 100 },
		{ "John", 195, 75 },
	};

	Athlete maxAthlete;

	FindMax(athletes, maxAthlete, CompareTall);
	std::cout << "The highest athlete is " << maxAthlete.name << std::endl;
	std::cout << "Tall is " << maxAthlete.tall << std::endl;
	std::cout << std::endl;

	FindMax(athletes, maxAthlete, CompareWeight);
	std::cout << "The heaviest athlete is " << maxAthlete.name << std::endl;
	std::cout << "Weight is " << maxAthlete.weight << std::endl;

	// std::vector<int> numbers = { 1, 2, 3 };
	// int number;

	// FindMax(numbers, number);
	// std::cout << number << std::endl;
}

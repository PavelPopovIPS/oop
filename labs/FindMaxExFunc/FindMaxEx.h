#pragma once

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

bool CompairAthletes(const Athlete& a1, const Athlete& a2);
bool CompareTall(const Athlete& a1, const Athlete& a2);
bool CompareWeight(const Athlete& a1, const Athlete& a2);

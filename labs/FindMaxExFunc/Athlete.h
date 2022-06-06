#pragma once

#include "stdafx.h"

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

bool CompairAthletes(const Athlete& a1, const Athlete& a2);
bool CompareTall(const Athlete& a1, const Athlete& a2);
bool CompareWeight(const Athlete& a1, const Athlete& a2);

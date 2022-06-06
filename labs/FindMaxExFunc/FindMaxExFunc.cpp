// FindMaxExFunc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Athlete.h"
#include "FindMaxEx.h"

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
}

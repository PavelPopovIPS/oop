#pragma once
#include <iostream>
#include <set>
#include <string>

struct Args
{
	int upperBound;
};

Args ParseArgs(int argc, char* argv[]);
std::set<int> GeneratePrimeNumbersSet(int upperBound);

#pragma once
#include <iostream>
#include <set>
#include <string>
#include <vector>

struct Args
{
	int upperBound;
};

Args ParseArgs(int argc, char* argv[]);
std::set<int> GeneratePrimeNumbersSet(int upperBound);

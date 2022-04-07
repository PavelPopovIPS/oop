#pragma once
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <vector>

struct Args
{
	int upperBound;
};

Args ParseArgs(int argc, char* argv[]);
std::vector<bool> SiftNumbers(int upperBound);
std::set<int> GetPrimeNumbersSet(const std::vector<bool>& numbers);
std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintSet(const std::set<int>& primeNumbersSet);
void PrintSetSize(const std::set<int>& primeNumbersSet);

#pragma once

#include <functional>
#include <string>
#include <vector>

typedef std::function<void(std::vector<double>& vectr, double number)> ActionFunction;
std::string ReadInput();
std::vector<double> ParseStringToVector(const std::string& inputStr);
double CalcPositiveElementsAverage(const std::vector<double>& vectr);
void AddNumberToVectorElements(std::vector<double>& vectr, double number);
void Map(ActionFunction const& actionFn, std::vector<double>& vectr, double number);
void SortVector(std::vector<double>& vectr);
void PrintVector(std::vector<double>& vectr);

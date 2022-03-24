#pragma once

#include <string>
#include <vector>

std::string ReadInput();
std::vector<double> ParseStringToVector(const std::string& inputStr);
double CalcPositiveElementsAverage(const std::vector<double>& vectr);
void AddNumberToVectorElements(std::vector<double>& vectr, double number);
void SortVector(std::vector<double>& vectr);
void PrintVector(std::vector<double>& vectr);

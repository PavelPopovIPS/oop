#pragma once
#include <fstream>
#include <map>
#include <string>

std::string CutSpaces(const std::string& string);
std::string ConvertTextToLowCase(std::string text);
std::map<std::string, std::string> InitDictionary(const std::string& dicFileName);

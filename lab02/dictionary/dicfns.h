#pragma once
#include <fstream>
#include <map>
#include <string>

std::string CutSpaces(const std::string& string);
std::map<std::string, std::string> InitDictionary(const std::string& dicFileName);

#pragma once
#include <fstream>
#include <map>
#include <string>

std::string DeleteSpaces(std::string& string);
std::map<std::string, std::string> InitDictionary(std::string dicFileName);

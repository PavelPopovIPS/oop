#pragma once
#include <fstream>
#include <map>

std::map<std::string, std::string> InitDictionary(std::fstream dictionaryStream);

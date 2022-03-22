#pragma once
#include <fstream>
#include <map>
#include <string>

std::string CutSpaces(const std::string& string);
std::string ConvertTextToLowCase(std::string text);
std::map<std::string, std::string> InitDictionary(const std::string& dicFileName);
void PrintTranslation(std::map<std::string, std::string>& dictionary, std::string& key);
bool IsTranslationExisting(std::map<std::string, std::string>& dictionary, std::string& key);
void AddNewTranslation(std::map<std::string, std::string>& dictionary,
	const std::string& key,
	const std::string& originalLine);

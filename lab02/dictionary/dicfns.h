#pragma once
#include <fstream>
#include <map>
#include <string>

std::string DeleteBrackets(std::string key);
std::string CutSpaces(const std::string& string);
std::string ConvertTextToLowCase(std::string text);
std::pair<std::string, std::string> CreateTranslationUnit(const std::string& key, const std::string& translation);
std::pair<std::string, std::string> ParseLine(const std::string& line);
std::map<std::string, std::string> InitDictionary(const std::string& dicFileName);
bool IsTranslationExisting(const std::map<std::string, std::string>& dictionary, const std::string& key);
void PrintTranslation(std::map<std::string, std::string>& dictionary, const std::string& key);
void AddNewTranslation(std::map<std::string, std::string>& dictionary,
	const std::string& key,
	const std::string& originalText);
void Exit(const std::map<std::string, std::string>& dictionary, size_t originalSize, const std::string& dicFileName);

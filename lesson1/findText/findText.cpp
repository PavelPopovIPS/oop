// findText.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream> //необходим для работы со строками в файле
#include <string>
#include <vector>

struct Args
{
	std::string fileName;
	std::string textToSearch;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: findText.exe <file name> <text to search>\n";
		return std::nullopt;
	}
	Args args;
	args.fileName = argv[1];
	args.textToSearch = argv[2];

	if (args.textToSearch == "")
	{
		std::cout << "Text to search should not be empty";
		return std::nullopt;
	}

	return args;
}

std::vector<int> FindText(std::ifstream& file, std::string& text)
{
	std::string line;
	std::vector<int> lineList = {};
	int lineNumber = 1;
	bool isTextFound = false;

	// Read file line by line
	while (std::getline(file, line))
	{
		// Search text in line
		if (line.find(text) != std::string::npos)
		{
			lineList.push_back(lineNumber);
			isTextFound = true;
			lineNumber++;
		}
	}
	return lineList;
}

void PrintLineList(std::vector<int>& lineList)
{
	for (int lineNumber : lineList)
	{
		std::cout << lineNumber << std::endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	// Check count of args
	if (!args)
	{
		return 1;
	}

	// Open files for reading
	std::ifstream file;
	file.open(args->fileName);
	if (!file.is_open())
	{
		std::cout << "File " << args->fileName << " was not opened for reading\n";
		return 1;
	}

	// Search text
	std::vector result = FindText(file, args->textToSearch);

	if (file.bad())
	{
		std::cout << "Failed to read data from file\n";
		return 1;
	}

	if (result.size() == 0)
	{
		std::cout << "Text not found\n";
		return 1;
	}

	PrintLineList(result);

	return 0;
}

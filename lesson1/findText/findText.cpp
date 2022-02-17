// findText.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream> //необходим для работы со строками в файле
#include <string>

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

//----Разобраться где использовать константные ссылки
// Попробуй использовать для возврадаемого значаение std::vector<Int>
// push_back() для вставки
std::string FindText(std::ifstream& file, std::string& text)
{
	int lineCount = 1;
	std::string lineList = "";
	bool isTextFound = false;

	// Read file line by line
	for (std::string line; std::getline(file, line); lineCount++)
	{
		// Search text in line
		if (line.find(text) != std::string::npos)
		{
			lineList += std::to_string(lineCount);
			isTextFound = true;
		}
	}

	// Check flag that text was found
	// --Не стоит мешать логику программы и вывод
	if (!isTextFound)
	{
		std::cout << "Text not found\n";
	}

	return lineList;
}

void PrintLineList(std::string& lineList)
{
	for (auto ch : lineList)
	{
		std::cout << ch << std::endl;
	}
}

int main(int argc, char* argv[])
{
	// ------Есть две штуковины они меняют кодировки вывода в стандартый поторк
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
	std::string result = FindText(file, args->textToSearch);

	if (file.bad())
	{
		std::cout << "Failed to read data from file\n";
		return 1;
	}

	if (result == "")
	{
		return 1;
	}

	PrintLineList(result);

	return 0;
}

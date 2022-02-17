// findText.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream> //��������� ��� ������ �� �������� � �����
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
	return args;
}

//----����������� ��� ������������ ����������� ������
std::string FindText(std::ifstream& file, std::string& text)
{
	int lineCount = 1;
	std::string lineList;
	bool isTextFound = false;

	// Read file line by line
	// ----------����������� ��� getLine ���������� bool
	for (std::string line; std::getline(file, line); lineCount++)
	{
		// Search text in line
		if (line.find(text) != std::string::npos)
		{
			// 1.�������� ������ ��������� �� ������
			lineList.append(lineCount);
			isTextFound = true;
		}
	}

	// Check flag that text was found
	if (!isTextFound)
	{
		std::cout << "Text not found\n";
		return false;
	}

	return true;
}

void PrintLineList(std::string& lineList)
{
	std::cout << lineList[1] << "\n";
}

int main(int argc, char* argv[])
{
	// ------���� ��� ��������� ��� ������ ��������� ������ � ���������� ������
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
	// Exit with code 1 if text not found

	// 2. �������� ��� ���������
	if (!IsTextExist(file, args->textToSearch))
	{
		return 1;
	}

	if (file.bad())
	{
		std::cout << "Failed to read data from file\n";
		return 1;
	}

	return 0;
}

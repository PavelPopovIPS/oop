// replace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFile;
	std::string outputFile;
	std::string searchText;
	std::string replaceText;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "replace.exe <input file> <output file> <search string> <replace string>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFile = argv[1];
	args.outputFile = argv[2];
	args.searchText = argv[3];
	args.replaceText = argv[4];

	return args;
}

std::string ReplaceText(std::string& line, std::string& searchText, std::string& replaceText)
{
	size_t startPos = 0;
	size_t searchTextPos = 0;
	size_t lenSubline = 0;
	std::string newLine = "";

	// Собираем новую строку из кусочков строки line с заменой текста
	while (searchTextPos < line.length())
	{
		// Поиск позиции искомого текста относительно начала строки
		searchTextPos = line.find(searchText, startPos);

		// Вычисляю длину строки, которую буду точно вставлять в новую строку
		lenSubline = searchTextPos - startPos;

		//И вставляю ее в новую строку ? беззнаковое size_t searchTextPos = 18446744073709551615, а не -1
		newLine.append(line, startPos, lenSubline);

		if (searchTextPos != std::string::npos)
		{
			newLine.append(replaceText);

			// Нужно пересчитать позицию, с которой продолжится поиск искомого текста в текущей строке
			startPos = searchTextPos + searchText.length();
		}
	}

	return newLine;
}

void CopyFileWithReplace(std::ifstream& inputFile, std::ofstream& outputFile, std::string& searchText, std::string& replaceText)
{
	std::string line;

	while (std::getline(inputFile, line))
	{
		// outputFile << newLine << std::endl;
		std::cout << ReplaceText(line, searchText, replaceText) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(args->inputFile);

	if (!inputFile.is_open())
	{
		std::cout << "File " << args->inputFile << " was not opened for reading\n";
		return 1;
	}

	std::ofstream outputFile;
	outputFile.open(args->outputFile);
	if (!outputFile.is_open())
	{
		std::cout << "File " << args->outputFile << " was not opened for writing\n";
		return 1;
	}

	std::string searchText = args->searchText;
	std::string replaceText = args->replaceText;

	CopyFileWithReplace(inputFile, outputFile, searchText, replaceText);

	if (inputFile.bad())
	{
		std::cout << "Failed to read data from file\n";
		return 1;
	}

	if (!outputFile.flush())
	{
		std::cout << "Failed to write to file from buffer\n";
		return 1;
	}

	std::cout << "Text was replaced\n";
	return 0;
}

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
	std::string line;
	std::string newLine;
	size_t startLinePos = 0;
	size_t endLinePos = 0;

	std::getline(inputFile, line);
	std::cout << line << std::endl;

	while (startLinePos < line.length())
	{
		endLinePos = line.find(searchText, startLinePos);
		// endLinePos -= startLinePos;
		std::cout << endLinePos << std::endl;

		// —обираем строку с новой подстрокой ? беззнаковое size_t endLinePos = 18446744073709551615, а не -1
		newLine.append(line, startLinePos, endLinePos - startLinePos);
		std::cout << newLine << std::endl;

		if (endLinePos != std::string::npos)
		{
			newLine.append(replaceText);
			std::cout << newLine << std::endl;

			// Ќужно пересчитать позиции строки, в которой продолжитс€ поиск
			startLinePos = endLinePos + searchText.length();
			std::cout << startLinePos << std::endl;
		}
		else
		{
			break;
		}
	}

	// outputFile << newLine << std::endl;
	std::cout << newLine << std::endl;

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

	return 0;
}

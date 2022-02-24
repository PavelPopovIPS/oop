// multmatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string fileMatrixFirst;
	std::string fileMatrixSecond;
};

struct Matrix
{
	double firstLine[3];
	double secondLine[3];
	double thirdLine[3];
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argument count\n";
		std::cout << "Usage: multmatrix.exe <matrix file1> <matrix file2>\n";
		return std::nullopt;
	}
	Args args;
	args.fileMatrixFirst = argv[1];
	args.fileMatrixSecond = argv[2];

	if (args.fileMatrixFirst == "" || args.fileMatrixSecond == "")
	{
		std::cout << "File name should not be empty";
		return std::nullopt;
	}

	return args;
}
std::optional<double> ConvertStringToNumer(std::string text)
{
	try
	{
		return std::stod(text);
	}
	catch (std::invalid_argument e)
	{
		std::cout << text << " is not number\n";
		return std::nullopt;
	}
}

std::optional<Matrix> GetMatrix(std::ifstream& fileMatrix)
{
	Matrix matrix;
	std::string line;
	std::string delimiter = "\t";

	while (std::getline(fileMatrix, line))
	{
		size_t searchTextPos = 0;
		std::string elem;
		while (searchTextPos < line.length())
		{
			// Поиск позиции искомого текста относительно начала строки
			searchTextPos = line.find(delimiter);

			if (searchTextPos != std::string::npos)
			{
				elem = line.substr(0, searchTextPos);
				auto num = ConvertStringToNumer(elem);

				if (!num)
				{
					return std::nullopt;
				}
				std::cout << std::stod(elem) << " ";
				// Нужно удалить обработанный текст из полученной строки
				line.erase(0, searchTextPos + delimiter.length());
			}
		}
		std::cout << std::stod(line) << std::endl;
	}

	return matrix;
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
	std::ifstream fileMatrixFirst;
	fileMatrixFirst.open(args->fileMatrixFirst);
	if (!fileMatrixFirst.is_open())
	{
		std::cout << "File " << args->fileMatrixFirst << " was not opened for reading\n";
		return 1;
	}

	std::ifstream fileMatrixSecond;
	fileMatrixSecond.open(args->fileMatrixSecond);
	if (!fileMatrixSecond.is_open())
	{
		std::cout << "File " << args->fileMatrixSecond << " was not opened for reading\n";
		return 1;
	}

	GetMatrix(fileMatrixFirst);

	return 0;
}

// multmatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

enum class Error
{
	InvalidArgumentCount,
	ArgumentInitialize,
	ArgumentNotNumber,
	EmptyFileName,
	ContainTextMatrix,
};

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
		throw Error::InvalidArgumentCount;
		return std::nullopt;
	}
	Args args;
	args.fileMatrixFirst = argv[1];
	args.fileMatrixSecond = argv[2];

	if (args.fileMatrixFirst == "" || args.fileMatrixSecond == "")
	{
		throw Error::EmptyFileName;
		return std::nullopt;
	}

	return args;
}

void PrintError(Error error)
{
	switch (error)
	{
	case Error::InvalidArgumentCount: {
		std::cout << "Invalid argument count\n";
		std::cout << "For use: rotatebyte.exe <byte>\n";
		break;
	}
	case Error::ArgumentInitialize: {
		std::cout << "Argument should be greater than zero or equal zero and less than 256\n";
		break;
	}
	case Error::ArgumentNotNumber: {
		std::cout << "First argument should be number\n";
		break;
	}
	case Error::EmptyFileName: {
		std::cout << "File name should not be empty";
		break;
	}
	case Error::ContainTextMatrix: {
		std::cout << "Matrix should not contan text\n";
		break;
	}
	}
}

double ConvertStringToNumer(std::string text)
{
	try
	{
		return std::stod(text);
	}
	catch (std::invalid_argument e)
	{
		throw Error::ContainTextMatrix;
		return NULL;
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
				double num = ConvertStringToNumer(line.substr(0, searchTextPos));

				std::cout << num << " ";
				// Нужно удалить обработанный текст из полученной строки
				line.erase(0, searchTextPos + delimiter.length());
			}
		}
		std::cout << ConvertStringToNumer(line) << std::endl;
	}

	return matrix;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

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
	}
	catch (Error error)
	{
		PrintError(error);
		return 1;
	}

	return 0;
}

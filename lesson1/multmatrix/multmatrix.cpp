// multmatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum class Error
{
	InvalidArgumentCount,
	ArgumentInitialize,
	ArgumentNotNumber,
	EmptyFileName,
	MatrixContainText,
	FileNotOpen,
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
	case Error::MatrixContainText: {
		std::cout << "Matrix should not contain text\n";
		break;
	}
	case Error::FileNotOpen: {
		std::cout << "File was not opened for reading\n";
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
		throw Error::MatrixContainText;
		return NULL;
	}
}

std::vector<double> ParseMatrixRow(const std::string& line)
{
	std::string delimiter = "\t";
	size_t startPos = 0;
	size_t searchTextPos = 0;
	size_t lenSubline = 0;
	std::vector<double> numbers = {};

	while (searchTextPos < line.length())
	{
		// Поиск позиции разделителя относительно начала строки
		searchTextPos = line.find(delimiter, startPos);

		// Вычисляю длину строки, которую буду конвертировать в double
		lenSubline = searchTextPos - startPos;

		// Получение строки, которую буду конвертировать в double
		std::string s = line.substr(startPos, lenSubline);

		// Конвертирую строку в double
		double n = ConvertStringToNumer(s);
		std::cout << n << " ";

		// Нужно пересчитать позицию, с которой продолжится поиск искомого текста в текущей строке
		startPos = searchTextPos + delimiter.length();
	}

	return numbers;
}

std::optional<Matrix> GetMatrix(std::ifstream& fileMatrix)
{
	Matrix matrix;
	std::string line;

	while (std::getline(fileMatrix, line))
	{
		ParseMatrixRow(line);
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
			throw Error::FileNotOpen;
			return 1;
		}

		std::ifstream fileMatrixSecond;
		fileMatrixSecond.open(args->fileMatrixSecond);
		if (!fileMatrixSecond.is_open())
		{
			throw Error::FileNotOpen;
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

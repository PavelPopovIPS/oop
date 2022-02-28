﻿// multmatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum class Error
{
	InvalidArgumentCount,
	EmptyFileName,
	MatrixContainText,
	FileNotOpen,
	MatrixColumnsCount,
	MatrixRowCount,
	FailedToReadData,
};

struct Args
{
	std::string fileMatrix;
};

struct Matrix3x3
{
	double pos[3][3];
};

struct Matrix2x2
{
	double pos[2][2];
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw Error::InvalidArgumentCount;
		return std::nullopt;
	}
	Args args;
	args.fileMatrix = argv[1];

	if (args.fileMatrix == "")
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
		std::cout << "For use: multmatrix.exe <matrix file>\n";
		break;
	}
	case Error::EmptyFileName: {
		std::cout << "File name should not be empty";
		break;
	}
	case Error::MatrixContainText: {
		std::cout << "Matrix should contain only numbers\n";
		break;
	}
	case Error::FileNotOpen: {
		std::cout << "File was not opened for reading\n";
		break;
	}
	case Error::MatrixColumnsCount: {
		std::cout << "Matrix should contain 3 columns\n";
		break;
	}
	case Error::MatrixRowCount: {
		std::cout << "Matrix should contain 3 rows\n";
		break;
	}
	case Error::FailedToReadData: {
		std::cout << "Failed to read data from file\n";
		break;
	}
	default: {
		std::cout << "Some error was occurred\n";
		break;
	}
	}
}

double ConvertStringToNumer(const std::string& text)
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

		// Добавляю полученное значение в массив
		numbers.push_back(n);

		// Нужно пересчитать позицию, с которой продолжится поиск искомого текста в текущей строке
		startPos = searchTextPos + delimiter.length();
	}

	return numbers;
}

std::optional<Matrix3x3> GetMatrix(std::ifstream& fileMatrix)
{
	Matrix3x3 matrix;
	std::string line;
	std::vector<double> numbers;
	size_t rowCount = 0;

	while (std::getline(fileMatrix, line))
	{
		rowCount++;

		// Если в матрице больше 3х строк
		if (rowCount > 3)
		{
			throw Error::MatrixRowCount;
			return std::nullopt;
		}

		numbers = ParseMatrixRow(line);

		// Если в матрице не соответствует условию по количеству столбцов
		if (numbers.size() != 3)
		{
			throw Error::MatrixColumnsCount;
			return std::nullopt;
		}

		for (int i = 0; i < 3; i++)
		{
			matrix.pos[rowCount - 1][i] = numbers[i];
		}
	}

	// Если в матрице меньше 3х строк
	if (rowCount < 3)
	{
		throw Error::MatrixRowCount;
		return std::nullopt;
	}

	return matrix;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (double num : matrix.pos[i])
		{
			// Манипуляторы контролируют точность чисел при выводе из потока
			std::cout << std::fixed << std::setprecision(3) << num << "\t";
		}
		std::cout << std::endl;
	}
}

// Matrix3x3 InvertMatrix(const Matrix3x3& matrixA)
//{
//	Matrix3x3 matrixNew;
//
//	return matrixNew;
// }

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		// Open files for reading
		std::ifstream fileMatrix;
		fileMatrix.open(args->fileMatrix);
		if (!fileMatrix.is_open())
		{
			throw Error::FileNotOpen;
			return 1;
		}

		auto matrix = *GetMatrix(fileMatrix);

		PrintMatrix(matrix);

		if (fileMatrix.bad())
		{
			throw Error::FailedToReadData;
			return 1;
		}
	}
	catch (Error error)
	{
		PrintError(error);
		return 1;
	}

	return 0;
}

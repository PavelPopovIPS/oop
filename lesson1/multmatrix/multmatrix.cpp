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
	EmptyFileName,
	MatrixContainText,
	FileNotOpen,
	MatrixColumnsCount,
	MatrixRowCount,
};

struct Args
{
	std::string fileMatrixFirst;
	std::string fileMatrixSecond;
};

struct Matrix
{
	double pos[3][3];
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
		std::cout << "For use: multmatrix.exe <matrix file1> <matrix file2>\n";
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

std::optional<Matrix> GetMatrix(std::ifstream& fileMatrix)
{
	Matrix matrix;
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

void PrintMatrix(const Matrix& matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << matrix.pos[i][j] << " ";
		}
		std::cout << std::endl;
	}
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

		auto matrixFirst = *GetMatrix(fileMatrixFirst);

		PrintMatrix(matrixFirst);
	}
	catch (Error error)
	{
		PrintError(error);
		return 1;
	}

	return 0;
}

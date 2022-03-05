﻿// multmatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <array>
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
	MatrixDeterminantZero,
};

struct Args
{
	std::string fileMatrix; // matrixFile
};

// struct Matrix3x3
//{
//	double pos[3][3]; // items
// };

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

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
	case Error::MatrixDeterminantZero: {
		std::cout << "Matrix determinant equal Zero. There is no invert matrix\n";
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

// пусть принимает istream&
std::optional<Matrix3x3> GetMatrix(std::ifstream& fileMatrix)
{
	Matrix3x3 matrix;
	std::string line;
	std::vector<double> numbers;
	size_t rowCount = 0;

	while (std::getline(fileMatrix, line))
	{
		/*
		std::istringstream strm(line);
		if (strm >> matrix[rowIndex][0] >> matrix[rowIndex][1] >> matrix[rowIndex][1])
		{
			// успех
		}
		else
		{
			// ошибка
		}
		*/
		rowCount++;

		// Если в матрице больше 3х строк
		if (rowCount > 3)
		{
			/*
			try
			{
				throw std::runtime_error("Error !!!!");
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			*/
			throw Error::MatrixRowCount;
			return std::nullopt; // после throw инструкция не выполняется
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
			matrix[rowCount - 1][i] = numbers[i];
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
	for (auto& row : matrix /* int i = 0; i < 3; i++*/)
	{
		for (double num : /* matrix[i]*/ row)
		{
			// Манипуляторы контролируют точность чисел при выводе из потока
			std::cout << std::fixed << std::setprecision(3) << num << "\t";
		}
		std::cout << std::endl;
	}
}

// Назвать Swap либо использовать std::swap()
void SwapElements(double& a, double& b)
{
	double tmp = 0;

	tmp = a;
	a = b;
	b = tmp;
}

double GetMatrixDeterminant(const Matrix3x3& matrix)
{
	double determinant = 0;
	determinant += matrix[0][0] * matrix[1][1] * matrix[2][2]; // 1
	determinant += matrix[2][0] * matrix[0][1] * matrix[1][2]; // 2
	determinant += matrix[1][0] * matrix[2][1] * matrix[0][2]; // 3
	determinant -= matrix[2][0] * matrix[1][1] * matrix[0][2]; // 4
	determinant -= matrix[0][0] * matrix[2][1] * matrix[1][2]; // 5
	determinant -= matrix[1][0] * matrix[0][1] * matrix[2][2]; // 6

	return determinant;
}

Matrix3x3 GetMinorMatrix(const Matrix3x3& matrix)
{
	Matrix3x3 minorMatrix;

	minorMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];
	minorMatrix[0][1] = matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2];
	minorMatrix[0][2] = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];

	minorMatrix[1][0] = matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2];
	minorMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[2][0] * matrix[0][2];
	minorMatrix[1][2] = matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1];

	minorMatrix[2][0] = matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2];
	minorMatrix[2][1] = matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2];
	minorMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

	return minorMatrix;
}

// Вроде так называется CofactorMatrix либо AdjugateMatrix
Matrix3x3 GetAlgebraicAdditionsMatrix(const Matrix3x3& matrix /*minorMatrix*/)
{
	Matrix3x3 algebraicAdditionsMatrix = matrix;

	// Меняем знаки у определенных элементов
	algebraicAdditionsMatrix[1][0] *= -1;
	algebraicAdditionsMatrix[0][1] *= -1;
	algebraicAdditionsMatrix[1][2] *= -1;
	algebraicAdditionsMatrix[2][1] *= -1;

	return algebraicAdditionsMatrix;
}

Matrix3x3 GetTransposedMatrix(const Matrix3x3& matrix)
{
	Matrix3x3 transposedMatrix = matrix;

	SwapElements(transposedMatrix[1][0], transposedMatrix[0][1]);
	SwapElements(transposedMatrix[2][0], transposedMatrix[0][2]);
	SwapElements(transposedMatrix[2][1], transposedMatrix[1][2]);

	return transposedMatrix;
}

// Matrix3x3 GetScaledMatrix(matrix, coeff);
// double det;
// Matrix3xx invertedMatrix = GetScaledMatrix(m, 1.0 / det);
// double передавать по значению
Matrix3x3 GetInvertMatrix(const double& determinant, const Matrix3x3& matrix)
{
	Matrix3x3 invertMatrix = matrix;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			invertMatrix[i][j] /= determinant;
		}
	}

	return invertMatrix;
}

// возвращает матрицу либо nullopt, если матрица вырожденная
std::optional<Matrix3x3> Invert(const Matrix3x3& sourceMatrix)
{
	return std::nullopt;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		// Сделай функцию, которая бы читала бы матрицу из файла, с указанным именем
		// Open files for reading
		std::ifstream fileMatrix;
		fileMatrix.open(args->fileMatrix);
		if (!fileMatrix.is_open())
		{
			throw Error::FileNotOpen;
			return 1;
		}

		auto matrix = *GetMatrix(fileMatrix);

		// 1. Находим определитель матрицы
		double matrixDeterminant = GetMatrixDeterminant(matrix);

		//Если определитель матрицы равен НУЛЮ – обратной матрицы не существует.
		if (matrixDeterminant == 0)
		{
			throw Error::MatrixDeterminantZero;
			return 1;
		}

		// 2. Находим матрицу миноров
		Matrix3x3 minorMatrix = GetMinorMatrix(matrix);

		// 3. Находим матрицу алгебраических дополнений
		Matrix3x3 algebraicAdditionsMatrix = GetAlgebraicAdditionsMatrix(minorMatrix);

		// 4. Находим транспонированную матрицу алгебраических дополнений
		Matrix3x3 transposedMatrix = GetTransposedMatrix(algebraicAdditionsMatrix);

		// 5. Вычисление обратной матрицы
		Matrix3x3 invertMatrix = GetInvertMatrix(matrixDeterminant, transposedMatrix);

		PrintMatrix(invertMatrix);

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

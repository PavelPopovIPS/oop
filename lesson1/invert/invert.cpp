// multmatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

enum class Error
{
	InvalidArgumentCount,
	EmptyFileName,
	FileNotOpen,
	MatrixColumnsCountOrTextContain,
	MatrixRowCount,
	FailedToReadData,
	MatrixDeterminantZero,
};

struct Args
{
	std::string fileMatrixName;
};

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw Error::InvalidArgumentCount;
	}
	Args args;
	args.fileMatrixName = argv[1];

	if (args.fileMatrixName == "")
	{
		throw Error::EmptyFileName;
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
	case Error::FileNotOpen: {
		std::cout << "File was not opened for reading\n";
		break;
	}
	case Error::MatrixColumnsCountOrTextContain: {
		std::cout << "Matrix do not have 3 columns or contain text\n";
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

std::optional<Matrix3x3> ReadMatrixFromFile(std::string fileMatrixName)
{
	std::ifstream fileMatrix;
	fileMatrix.open(fileMatrixName);

	if (!fileMatrix.is_open())
	{
		throw Error::FileNotOpen;
	}

	Matrix3x3 matrix;
	std::string line;
	std::vector<double> numbers;
	size_t rowCount = 0;

	while (std::getline(fileMatrix, line))
	{
		if (rowCount > 2)
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
		}

		std::istringstream strm(line);

		if (strm >> matrix[rowCount][0] >> matrix[rowCount][1] >> matrix[rowCount][2])
		{
			rowCount++;
		}
		else
		{
			throw Error::MatrixColumnsCountOrTextContain;
		}
	}

	// Если в матрице меньше 3х строк
	if (rowCount < 3)
	{
		throw Error::MatrixRowCount;
	}

	if (fileMatrix.bad())
	{
		throw Error::FailedToReadData;
	}

	return matrix;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	for (auto& row : matrix)
	{
		for (double num : row)
		{
			// Манипуляторы контролируют точность чисел при выводе из потока
			std::cout << std::fixed << std::setprecision(3) << num << "\t";
		}
		std::cout << std::endl;
	}
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

	std::swap(transposedMatrix[1][0], transposedMatrix[0][1]);
	std::swap(transposedMatrix[2][0], transposedMatrix[0][2]);
	std::swap(transposedMatrix[2][1], transposedMatrix[1][2]);

	return transposedMatrix;
}

// Matrix3x3 GetScaledMatrix(matrix, coeff);
// double det;
// Matrix3x3 invertedMatrix = GetScaledMatrix(matrix, 1.0 / det);
// double передавать по значению
Matrix3x3 GetInvertMatrix(const double determinant, const Matrix3x3& matrix)
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
std::optional<Matrix3x3> InvertMatrix(const Matrix3x3& sourceMatrix)
{
	// 1. Находим определитель матрицы
	double matrixDeterminant = GetMatrixDeterminant(matrix);

	//Если определитель матрицы равен НУЛЮ – обратной матрицы не существует.
	if (matrixDeterminant == 0)
	{
		throw Error::MatrixDeterminantZero;
	}

	// 2. Находим матрицу миноров
	Matrix3x3 minorMatrix = GetMinorMatrix(matrix);

	// 3. Находим матрицу алгебраических дополнений
	Matrix3x3 algebraicAdditionsMatrix = GetAlgebraicAdditionsMatrix(minorMatrix);

	// 4. Находим транспонированную матрицу алгебраических дополнений
	Matrix3x3 transposedMatrix = GetTransposedMatrix(algebraicAdditionsMatrix);

	// 5. Вычисление обратной матрицы
	Matrix3x3 invertMatrix = GetInvertMatrix(matrixDeterminant, transposedMatrix);
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		auto matrix = *ReadMatrixFromFile(args->fileMatrixName);
		auto invertMatrix = *InvertMatrix(matrix);
		PrintMatrix(invertMatrix);
	}
	catch (Error error)
	{
		PrintError(error);
		return 1;
	}

	return 0;
}

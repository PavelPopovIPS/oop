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

struct Args
{
	std::string fileMatrixName;
};

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::runtime_error("Invalid argument count\nFor use: multmatrix.exe <matrix file>\n");
	}
	Args args;
	args.fileMatrixName = argv[1];

	if (args.fileMatrixName == "")
	{
		throw std::runtime_error("File name should not be empty\n");
	}

	return args;
}

Matrix3x3 ReadMatrixFromFile(std::string fileMatrixName)
{
	std::ifstream fileMatrix;
	fileMatrix.open(fileMatrixName);

	if (!fileMatrix.is_open())
	{
		throw std::runtime_error("File was not opened for reading\n");
	}

	Matrix3x3 sourceMatrix;
	std::string line;
	size_t rowCount = 0;

	while (std::getline(fileMatrix, line))
	{
		// Если в матрице больше 3х строк
		if (rowCount > 2)
		{
			throw std::runtime_error("Matrix should contain 3 rows. You use more then 3");
		}

		std::istringstream strm(line);

		if (strm >> sourceMatrix[rowCount][0] >> sourceMatrix[rowCount][1] >> sourceMatrix[rowCount][2])
		{
			rowCount++;
		}
		else
		{
			throw std::runtime_error("Matrix do not have 3 columns or contain text\n");
		}
	}

	// Если в матрице меньше 3х строк
	if (rowCount < 3)
	{
		throw std::runtime_error("Matrix should contain 3 rows. You use less then 3");
	}

	if (fileMatrix.bad())
	{
		throw std::runtime_error("Failed to read data from file\n");
	}

	return sourceMatrix;
}

double CalcDeterminant(const Matrix3x3& sourceMatrix)
{
	double determinant = 0;
	determinant += sourceMatrix[0][0] * sourceMatrix[1][1] * sourceMatrix[2][2]; // 1
	determinant += sourceMatrix[2][0] * sourceMatrix[0][1] * sourceMatrix[1][2]; // 2
	determinant += sourceMatrix[1][0] * sourceMatrix[2][1] * sourceMatrix[0][2]; // 3
	determinant -= sourceMatrix[2][0] * sourceMatrix[1][1] * sourceMatrix[0][2]; // 4
	determinant -= sourceMatrix[0][0] * sourceMatrix[2][1] * sourceMatrix[1][2]; // 5
	determinant -= sourceMatrix[1][0] * sourceMatrix[0][1] * sourceMatrix[2][2]; // 6

	return determinant;
}

Matrix3x3 CalcMinorMatrix(const Matrix3x3& sourceMatrix)
{
	Matrix3x3 minorMatrix;

	minorMatrix[0][0] = sourceMatrix[1][1] * sourceMatrix[2][2] - sourceMatrix[2][1] * sourceMatrix[1][2];
	minorMatrix[0][1] = sourceMatrix[1][0] * sourceMatrix[2][2] - sourceMatrix[2][0] * sourceMatrix[1][2];
	minorMatrix[0][2] = sourceMatrix[1][0] * sourceMatrix[2][1] - sourceMatrix[2][0] * sourceMatrix[1][1];

	minorMatrix[1][0] = sourceMatrix[0][1] * sourceMatrix[2][2] - sourceMatrix[2][1] * sourceMatrix[0][2];
	minorMatrix[1][1] = sourceMatrix[0][0] * sourceMatrix[2][2] - sourceMatrix[2][0] * sourceMatrix[0][2];
	minorMatrix[1][2] = sourceMatrix[0][0] * sourceMatrix[2][1] - sourceMatrix[2][0] * sourceMatrix[0][1];

	minorMatrix[2][0] = sourceMatrix[0][1] * sourceMatrix[1][2] - sourceMatrix[1][1] * sourceMatrix[0][2];
	minorMatrix[2][1] = sourceMatrix[0][0] * sourceMatrix[1][2] - sourceMatrix[1][0] * sourceMatrix[0][2];
	minorMatrix[2][2] = sourceMatrix[0][0] * sourceMatrix[1][1] - sourceMatrix[1][0] * sourceMatrix[0][1];

	return minorMatrix;
}

Matrix3x3 CalcCoFactorMatrix(Matrix3x3 minorMatrix)
{
	// Меняем знаки у определенных элементов
	minorMatrix[1][0] *= -1;
	minorMatrix[0][1] *= -1;
	minorMatrix[1][2] *= -1;
	minorMatrix[2][1] *= -1;

	return minorMatrix;
}

Matrix3x3 CalcTransposedMatrix(Matrix3x3 coFactorMatrix)
{
	std::swap(coFactorMatrix[1][0], coFactorMatrix[0][1]);
	std::swap(coFactorMatrix[2][0], coFactorMatrix[0][2]);
	std::swap(coFactorMatrix[2][1], coFactorMatrix[1][2]);

	return coFactorMatrix;
}

// почитать как происходит деление double
Matrix3x3 CalcScaledMatrix(const Matrix3x3& transposedMatrix, const double inverseDeterminant)
{
	Matrix3x3 invertMatrix = transposedMatrix;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			invertMatrix[i][j] *= inverseDeterminant;
		}
	}

	return invertMatrix;
}

Matrix3x3 InvertMatrix(const Matrix3x3& sourceMatrix)
{
	// 1. Находим определитель матрицы
	double determinant = CalcDeterminant(sourceMatrix);

	//Если определитель матрицы равен НУЛЮ – обратной матрицы не существует.
	if (determinant == 0)
	{
		throw std::runtime_error("Matrix determinant equal Zero. There is no invert matrix\n");
	}

	// 2. Находим матрицу миноров
	Matrix3x3 minorMatrix = CalcMinorMatrix(sourceMatrix);

	// 3. Находим матрицу алгебраических дополнений
	Matrix3x3 coFactorMatrix = CalcCoFactorMatrix(minorMatrix);

	// 4. Находим транспонированную матрицу алгебраических дополнений
	Matrix3x3 transposedMatrix = CalcTransposedMatrix(coFactorMatrix);

	// 5. Вычисление обратной матрицы
	Matrix3x3 invertMatrix = CalcScaledMatrix(transposedMatrix, 1.0 / determinant);

	return invertMatrix;
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

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);
		Matrix3x3 sourceMatrix = ReadMatrixFromFile(args.fileMatrixName);
		Matrix3x3 invertMatrix = InvertMatrix(sourceMatrix);
		PrintMatrix(invertMatrix);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}

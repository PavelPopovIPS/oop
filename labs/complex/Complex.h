#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <math.h>
#include <string>

class CComplex
{
public:
	// инициализация комплексного числа значениями действительной и мнимой частей
	CComplex(double real = 0, double image = 0);

	// возвращает действительную часть комплексного числа
	double Re() const;

	// возвращает мнимую часть комплексного числа
	double Im() const;

	// возвращает модуль комплексного числа
	double GetMagnitude() const;

	// возвращает аргумент комплексного числа
	double GetArgument() const;

	CComplex operator+(const CComplex& complex) const;
	CComplex operator-(const CComplex& complex) const;
	CComplex operator*(const CComplex& complex) const;
	CComplex operator/(const CComplex& complex) const;

	CComplex const operator+() const;
	CComplex const operator-() const;
	CComplex& operator+=(const CComplex& complex);
	CComplex& operator-=(const CComplex& complex);
	CComplex& operator*=(const CComplex& complex);
	CComplex& operator/=(const CComplex& complex);
	bool operator==(const CComplex& complex) const;
	bool operator!=(const CComplex& complex) const;

private:
	double m_real;
	double m_image;
};

CComplex operator+(double number, const CComplex& complex);
CComplex operator-(double number, const CComplex& complex);
CComplex operator*(double number, const CComplex& complex);
CComplex operator/(double number, const CComplex& complex);
bool operator==(double number, const CComplex& complex);
bool operator!=(double number, const CComplex& complex);
std::ostream& operator<<(std::ostream& stream, const CComplex& complex);
std::istream& operator>>(std::istream& stream, CComplex& complex);

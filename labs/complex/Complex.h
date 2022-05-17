#pragma once

#include <cmath>
#include <iostream>
#include <math.h>

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

	//Почему const после типа?
	CComplex const operator+() const;
	CComplex const operator-() const;
	CComplex& operator+=(const CComplex& complex);
	CComplex& operator-=(const CComplex& complex);
	CComplex& operator*=(const CComplex& complex);
	CComplex& operator/=(const CComplex& complex);
	bool operator==(const CComplex& complex) const;

private:
	double m_real;
	double m_image;
};

CComplex operator+(double number, const CComplex& complex);
CComplex operator-(double number, const CComplex& complex);
CComplex operator*(double number, const CComplex& complex);
CComplex operator/(double number, const CComplex& complex);

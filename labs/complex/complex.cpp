#include "Complex.h"

CComplex::CComplex(double real, double image)
	: m_real(real)
	, m_image(image)
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return sqrt(pow(Re(), 2) + pow(Im(), 2));
}

// TODO доделать высчитывание аргумента
double CComplex::GetArgument() const
{
	if (Re() == 0 && Im() == 0)
	{
		throw std::runtime_error("Complex number can not be 0\n");
	}

	if (Re() > 0 && Im() > 0)
	{
		return atan(Im() / Re());
	}

	throw std::runtime_error("Complex number position was not define\n");
}

CComplex CComplex::operator+(const CComplex& complex) const
{
	return CComplex(Re() + complex.Re(), Im() + complex.Im());
}

CComplex CComplex::operator-(const CComplex& complex) const
{
	return CComplex(Re() - complex.Re(), Im() - complex.Im());
}

CComplex CComplex::operator*(const CComplex& complex) const
{
	return CComplex(Re() * complex.Re() - Im() * complex.Im(), Im() * complex.Re() + Re() * complex.Im());
}

CComplex CComplex::operator/(const CComplex& complex) const
{
	if (complex == 0)
	{
		throw std::runtime_error("Denominator can not be zero\n");
	}

	double tmpDenominator = pow(complex.Re(), 2) + pow(complex.Im(), 2);
	double tmpRe = (Re() * complex.Re() + Im() * complex.Im()) / tmpDenominator;
	double tmpIm = (Im() * complex.Re() - Re() * complex.Im()) / tmpDenominator;

	return CComplex(tmpRe, tmpIm);
}

CComplex const CComplex::operator+() const
{
	return *this;
}

CComplex const CComplex::operator-() const
{
	return CComplex(-Re(), -Im());
}

CComplex& CComplex::operator+=(const CComplex& complex)
{
	m_real += complex.m_real;
	m_image += complex.m_image;

	return *this;
}

CComplex& CComplex::operator-=(const CComplex& complex)
{
	m_real -= complex.m_real;
	m_image -= complex.m_image;

	return *this;
}

CComplex& CComplex::operator*=(const CComplex& complex)
{
	*this = *this * complex;
	return *this;
}

bool CComplex::operator==(const CComplex& complex) const
{
	return (Re() == complex.Re()) && (Im() == complex.Im());
}

CComplex operator+(double number, const CComplex& complex)
{
	CComplex n(number);
	return n + complex;
}

CComplex operator-(double number, const CComplex& complex)
{
	CComplex n(number);
	return n - complex;
}

CComplex operator*(double number, const CComplex& complex)
{
	CComplex n(number);
	return n * complex;
}

CComplex operator/(double number, const CComplex& complex)
{
	CComplex n(number);
	return n / complex;
}

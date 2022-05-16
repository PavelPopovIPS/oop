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

CComplex operator+(double number, const CComplex& complex)
{
	return CComplex(number + complex.Re(), complex.Im());
}

bool CComplex::operator==(const CComplex& complex) const
{
	return (Re() == complex.Re()) && (Im() == complex.Im());
}


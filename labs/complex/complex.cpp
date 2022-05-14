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

#include "Sphere.h"

CSphere::CSphere(double density, double radius)
	: CSolidBody("Sphere", density)
	, m_radius(radius)
{
	if (density <= 0)
	{
		throw std::runtime_error("Density can not be equal zero or less then zero");
	}

	if (radius <= 0)
	{
		throw std::runtime_error("Radius can not be equal zero or less then zero");
	}
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (1.33) * M_PI * pow(GetRadius(), 3);
}

void CSphere::AppendProperties(std::ostream& strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl;
}

#include "Sphere.h"

CSphere::CSphere(double density, double radius)
	: CSolidBody("Sphere", density)
	, m_radius(radius)
{
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

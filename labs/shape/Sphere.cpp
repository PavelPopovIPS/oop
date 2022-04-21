#include "Sphere.h"

CSphere::CSphere(double density, double radius)
	: CBody("Sphere", density)
	, m_radius(radius)
{
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (4.0 / 3.0) * M_PI * pow(GetRadius(), 3);
}

void CSphere::AppendProperties(std::ostream& strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl;
}

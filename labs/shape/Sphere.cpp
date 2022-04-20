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
	// return (4 / 3) * M_PI * pow(m_radius, 3);
	return 1.33 * M_PI * pow(m_radius, 3);
}

void CSphere::AppendProperties(std::ostream& strm) const
{
	strm << "\tradius = " << GetRadius() << std::endl;
}

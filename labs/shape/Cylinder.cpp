#include "Cylinder.h"

CCylinder::CCylinder(double density, double baseRadius, double height)
	: CSolidBody("Cylinder", density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
	if (density <= 0)
	{
		throw std::runtime_error("Density can not be equal zero or less then zero");
	}

	if (baseRadius <= 0 || height <= 0)
	{
		throw std::runtime_error("BaseRadius, height can not be equal zero or less then zero");
	}
}

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return M_PI * pow(GetBaseRadius(), 2) * GetHeight();
}

void CCylinder::AppendProperties(std::ostream& strm) const
{
	strm << "\tbase radius = " << GetBaseRadius() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
}

#include "Cone.h"

CCone::CCone(double density, double baseRadius, double height)
	: CSolidBody("Cone", density)
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

double CCone::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return (0.33) * M_PI * pow(GetBaseRadius(), 2) * GetHeight();
}

void CCone::AppendProperties(std::ostream& strm) const
{
	strm << "\tbase radius = " << GetBaseRadius() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
}

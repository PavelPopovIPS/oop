﻿#include "Cone.h"

CCone::CCone(double density, double baseRadius, double height)
	: CBody("Cone", density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
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
	// return (1 / 3) * M_PI * pow(m_baseRadius, 2) * m_height; // возвращает  0  ???
	return (1.0 / 3.0) * M_PI * pow(GetBaseRadius(), 2) * GetHeight();
}

void CCone::AppendProperties(std::ostream& strm) const
{
	strm << "\tbase radius = " << GetBaseRadius() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
}

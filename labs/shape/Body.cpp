#include "stdafx.h"
#include "Body.h"

CBody::CBody(const std::string& type)
	: m_type(type)
{
}

double CBody::GetWeightInWater() const
{
	return (GetDensity() - WATER_DENSITY) * g * GetVolume();
}

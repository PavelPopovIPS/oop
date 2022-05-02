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

bool CBody::HasParent() const
{
	if (m_pParent == nullptr)
	{
		return true;
	}
	return false;
}

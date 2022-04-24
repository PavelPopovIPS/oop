#include "Compound.h"

double CCompound::GetDensity() const
{
	return GetMass() / GetVolume();
}

double CCompound::GetVolume() const
{
	double volume = 0.0;

	for (auto p : m_childShapeCollection)
	{
		volume += p->GetVolume();
	}
	return volume;
}

double CCompound::GetMass() const
{
	double mass = 0.0;

	for (auto p : m_childShapeCollection)
	{
		mass += p->GetMass();
	}
	return mass;
}

bool CCompound::AddChildBody(std::shared_ptr<CBody>& child)
{
	m_childShapeCollection.push_back(child);

	return true;
}

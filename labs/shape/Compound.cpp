#include "Compound.h"

CCompound::CCompound()
	: CBody("Compound Shape")
{
}

double CCompound::GetDensity() const
{
	if (GetVolume() != 0)
	{
		return GetMass() / GetVolume();
	}
	else
	{
		return 0.0;
	}
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

std::string CCompound::ToString() const
{
	std::string str = m_type;
	str.append(" Start \n");
	str.append("Contain:\n");

	for (auto p : m_childShapeCollection)
	{
		str.append(p->ToString());
	}

	std::ostringstream strm;
	strm << "Summary:" << std::endl
		 << std::setprecision(10)
		 << "\tdensity = " << GetDensity() << std::endl
		 << "\tvolume = " << GetVolume() << std::endl
		 << "\tmass = " << GetMass() << std::endl
		 << "\tweight in water = " << GetWeightInWater() << std::endl;

	str.append(strm.str());

	str.append(m_type);
	str.append(" End \n");

	return str;
}

bool CCompound::AddChildBody(std::shared_ptr<CBody> child)
{
	if (child == nullptr)
	{
		throw std::runtime_error("Shape can not be nullptr");
	}

	if (child->HasParent())
	{
		throw std::runtime_error("Added shape can not have parent");
	}

	if (this->IsParent(child))
	{
		throw std::runtime_error("Compound shape can not be added in itself");
	}

	// не получается передать this как shared_ptr
	child->SetParent(this);

	m_childShapeCollection.push_back(child);

	return true;
}

bool CCompound::IsEmpty() const
{
	if (m_childShapeCollection.size() == 0)
	{
		return true;
	}
	return false;
}

bool CCompound::IsParent(std::shared_ptr<CBody> shape) const
{
	if (this == shape.get())
	{
		return true;
	}

	if (this->m_pParent == nullptr)
	{
		return false;
	}

	return m_pParent->IsParent(shape);
}

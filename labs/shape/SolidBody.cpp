#include "SolidBody.h"

CSolidBody::CSolidBody(const std::string& type, double density)
	: CBody(type)
	, m_density(density)
{
}

double CSolidBody::GetDensity() const
{
	return m_density;
}

double CSolidBody::GetMass() const
{
	return GetDensity() * GetVolume();
}

std::string CSolidBody::ToString() const
{
	std::ostringstream strm;
	strm << m_type << ":" << std::endl
		 << std::setprecision(10)
		 << "\tdensity = " << GetDensity() << std::endl
		 << "\tvolume = " << GetVolume() << std::endl
		 << "\tmass = " << GetMass() << std::endl
		 << "\tweight in water = " << GetWeightInWater() << std::endl;
	AppendProperties(strm);
	return strm.str();
}

bool CSolidBody::IsParent([[maybe_unused]] std::shared_ptr<CBody>) const
{
	return false;
}

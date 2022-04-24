#include "Parallelepiped.h"

CParalellepiped::CParalellepiped(double density, double width, double height, double depth)
	: CSolidBody("Paralellepiped", density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{
}

double CParalellepiped::GetWidth() const
{
	return m_width;
}

double CParalellepiped::GetHeight() const
{
	return m_height;
}

double CParalellepiped::GetDepth() const
{
	return m_depth;
}

double CParalellepiped::GetVolume() const
{
	return GetWidth() * GetHeight() * GetDepth();
}

void CParalellepiped::AppendProperties(std::ostream& strm) const
{
	strm << "\twidth = " << GetWidth() << std::endl;
	strm << "\theight = " << GetHeight() << std::endl;
	strm << "\tdepth = " << GetDepth() << std::endl;
}

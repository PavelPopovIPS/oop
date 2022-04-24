#pragma once

#include "SolidBody.h"

class CParalellepiped : public CSolidBody
{
public:
	CParalellepiped(double density, double width, double height, double depth);
	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_width;
	double m_height;
	double m_depth;
};

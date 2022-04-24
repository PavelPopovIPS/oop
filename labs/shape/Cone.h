#pragma once

#include "SolidBody.h"

class CCone : public CSolidBody
{
public:
	CCone(double density, double baseRadius, double height);
	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_baseRadius;
	double m_height;
};

#pragma once

#include "SolidBody.h"

class CSphere : public CSolidBody
{
public:
	CSphere(double density, double radius);
	double GetRadius() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_radius;
};

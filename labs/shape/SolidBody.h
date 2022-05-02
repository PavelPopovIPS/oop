#pragma once

#include "Body.h"

class CSolidBody : public CBody
{
public:
	CSolidBody(const std::string& type, double density);

	double GetDensity() const override;
	virtual double GetVolume() const = 0;
	double GetMass() const override;
	std::string ToString() const override;

	bool IsParent(std::shared_ptr<CBody> shape) const override;

private:
	virtual void AppendProperties(std::ostream& strm) const = 0;

	double m_density;
};

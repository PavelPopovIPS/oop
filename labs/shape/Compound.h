#pragma once

#include "Body.h"

class CCompound : public CBody
{
public:
	double GetDensity() const override;
	double GetVolume() const override;
	double GetMass() const override;

	bool AddChildBody(std::shared_ptr<CBody>& child);

private:
	std::vector<std::shared_ptr<CBody>> m_childShapeCollection;
};

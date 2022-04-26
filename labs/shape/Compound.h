#pragma once

#include "Body.h"

class CCompound : public CBody
{
public:
	CCompound();

	double GetDensity() const override;
	double GetVolume() const override;
	double GetMass() const override;
	std::string ToString() const override;

	bool AddChildBody(std::shared_ptr<CBody> child);
	bool IsEmpty() const;

private:
	std::vector<std::shared_ptr<CBody>> m_childShapeCollection;
};

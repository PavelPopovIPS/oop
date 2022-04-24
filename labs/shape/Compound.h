#pragma once

#include "Body.h"

class CCompound : public CBody
{
public:
	double GetVolume() const override;

	bool AddChildBody(CBody& child);

private:
	std::vector<std::shared_ptr<CBody>> m_childShapeCollection;
};

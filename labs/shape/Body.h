#pragma once

#include "stdafx.h"

class CBody
{
public:
	CBody(const std::string& type);

	virtual double GetDensity() const = 0;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const = 0;
	virtual std::string ToString() const = 0;

	double GetWeightInWater() const;
	bool HasParent() const;
	virtual ~CBody() = default;

protected:
	std::string m_type;
	std::shared_ptr<CBody> m_pParent = nullptr;
};

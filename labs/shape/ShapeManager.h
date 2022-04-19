#pragma once

#include "stdafx.h"
#include "Body.h"
#include "Cone.h"
#include "Parallelepiped.h"
#include "Sphere.h"

class CShapeManager
{
public:
	CShapeManager();
	void InitShapeManager();
	bool Info(std::istream&);

private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actionMap;

	void PrintUsageInfo();
	std::optional<double> ParseDensity(std::istream& args);

	bool SetSphereToCollection(std::istream& args);
	bool SetParallelepipedToCollection(std::istream& args);
	bool SetConeToCollection(std::istream& args);
	std::vector<std::shared_ptr<CBody>> m_shapeCollection;
};

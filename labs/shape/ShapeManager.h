#pragma once

#include "stdafx.h"
#include "Body.h"
#include "Compound.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

class CShapeManager
{
public:
	CShapeManager();
	void InitShapeManager();
	bool Info(std::istream&);
	bool PrintHeaviestShapeInfo(std::istream&);
	bool PrintLightestShapeInfo(std::istream&);

private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actionMap;

	void PrintUsageInfo();
	std::optional<double> ParseDensity(std::istream& args);
	std::optional<double> ParseBaseRadius(std::istream& args);
	std::optional<double> ParseHeight(std::istream& args);

	bool SetSphereToCollection(std::istream& args);
	bool SetParallelepipedToCollection(std::istream& args);
	bool SetConeToCollection(std::istream& args);
	bool SetCylinderToCollection(std::istream& args);
	bool SetCompoundToCollection(std::istream& args);

	std::shared_ptr<CBody> FindHeaviestShape(std::istream& args);
	std::shared_ptr<CBody> FindLightestShape(std::istream& args);

	std::vector<std::shared_ptr<CBody>> m_shapeCollection;
};

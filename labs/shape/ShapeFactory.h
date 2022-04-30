#pragma once

#include "stdafx.h"
#include "Body.h"
#include "Compound.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

class CShapeFactory
{
public:
	CShapeFactory();
	std::optional<std::shared_ptr<CBody>> ParseShape(std::string& parseShapeAction, std::istream& args);

private:
	std::shared_ptr<CBody> ParseSphere(std::istream& args);
	std::shared_ptr<CBody> ParseParallelepiped(std::istream& args);
	std::shared_ptr<CBody> ParseCone(std::istream& args);
	std::shared_ptr<CBody> ParseCylinder(std::istream& args);

	double ParseDensity(std::istream& args);
	double ParseBaseRadius(std::istream& args);
	double ParseHeight(std::istream& args);

	std::shared_ptr<CBody> ParseCompoundShape();

	using ParseShapeHandler = std::function<std::shared_ptr<CBody>(std::istream& args)>;
	using ParseShapeActionMap = std::map<std::string, ParseShapeHandler>;
	ParseShapeActionMap m_parseShapeActionMap;
};

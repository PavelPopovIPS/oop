#pragma once

#include "stdafx.h"
#include "Body.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Sphere.h"

class CParser
{
public:
	std::shared_ptr<CBody> ParseSphere(std::istream& args);
	std::shared_ptr<CBody> ParseParallelepiped(std::istream& args);
	std::shared_ptr<CBody> ParseCone(std::istream& args);
	std::shared_ptr<CBody> ParseCylinder(std::istream& args);

private:
	std::optional<double> ParseDensity(std::istream& args);
	std::optional<double> ParseBaseRadius(std::istream& args);
	std::optional<double> ParseHeight(std::istream& args);
};

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
	std::shared_ptr<CBody> CreateSphere(std::istream& args);
	std::shared_ptr<CBody> CreateParallelepiped(std::istream& args);
	std::shared_ptr<CBody> CreateCone(std::istream& args);
	std::shared_ptr<CBody> CreateCylinder(std::istream& args);
	std::shared_ptr<CCompound> CreateCompoundShape();

private:
	double ParseDensity(std::istream& args);
	double ParseBaseRadius(std::istream& args);
	double ParseHeight(std::istream& args);
};

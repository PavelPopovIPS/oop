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
	bool AddShape(std::shared_ptr<CBody> shape);
	bool PrintHeaviestShapeInfo(std::istream& args);
	bool PrintLightestShapeInWaterInfo(std::istream& args);
	bool PrintInfo(std::istream& args);

private:
	std::shared_ptr<CBody> FindHeaviestShape();
	std::shared_ptr<CBody> FindLightestShapeInWater();

	std::vector<std::shared_ptr<CBody>> m_shapeCollection;
};

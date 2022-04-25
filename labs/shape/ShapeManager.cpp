#include "ShapeManager.h"

bool CShapeManager::AddShape(std::shared_ptr<CBody> shape)
{
	m_shapeCollection.push_back(shape);
	return true;
}

bool CShapeManager::PrintHeaviestShapeInfo(std::istream&)
{
	std::shared_ptr<CBody> p_heaviestShape = FindHeaviestShape();
	std::cout << p_heaviestShape->ToString() << std::endl;

	return true;
}

bool CShapeManager::PrintLightestShapeInfo(std::istream&)
{
	std::shared_ptr<CBody> p_lightestShape = FindLightestShape();
	std::cout << p_lightestShape->ToString() << std::endl;

	return true;
}

bool CShapeManager::PrintInfo(std::istream&)
{
	for (auto p : m_shapeCollection)
	{
		std::cout << p->ToString() << std::endl;
	}
	return true;
}

std::shared_ptr<CBody> CShapeManager::FindHeaviestShape()
{
	double heaviestShapeMass = 0;
	std::shared_ptr<CBody> p_heaviestShape;

	for (auto p : m_shapeCollection)
	{
		double mass = p->GetMass();

		if (mass > heaviestShapeMass)
		{
			p_heaviestShape = p;
			heaviestShapeMass = mass;
		}
	}
	return p_heaviestShape;
}

std::shared_ptr<CBody> CShapeManager::FindLightestShape()
{
	double lightestShapeWeightInWater = 0;
	std::shared_ptr<CBody> p_lightestShape;

	for (auto p : m_shapeCollection)
	{
		double weightInWater = p->GetWeightInWater();

		if (weightInWater < lightestShapeWeightInWater)
		{
			p_lightestShape = p;
			lightestShapeWeightInWater = weightInWater;
		}
	}
	return p_lightestShape;
}

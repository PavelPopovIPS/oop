#include "ShapeManager.h"

bool CShapeManager::AddShape(std::shared_ptr<CBody> shape)
{
	if (shape == nullptr)
	{
		throw std::runtime_error("Shape can not be nullptr");
	}

	m_shapeCollection.push_back(shape);
	return true;
}

bool CShapeManager::PrintHeaviestShapeInfo(std::istream&)
{
	std::shared_ptr<CBody> p_heaviestShape = FindHeaviestShape();

	if (p_heaviestShape == nullptr)
	{
		throw std::runtime_error("There are no shapes in collection");
	}

	std::cout << p_heaviestShape->ToString() << std::endl;

	return true;
}

bool CShapeManager::PrintLightestShapeInWaterInfo(std::istream&)
{
	std::shared_ptr<CBody> p_lightestShape = FindLightestShapeInWater();

	if (p_lightestShape == nullptr)
	{
		throw std::runtime_error("There are no shapes in collection");
	}

	std::cout << p_lightestShape->ToString() << std::endl;

	return true;
}

bool CShapeManager::PrintInfo(std::istream&)
{
	if (m_shapeCollection.size() == 0)
	{
		throw std::runtime_error("There are no shapes in collection");
	}

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

std::shared_ptr<CBody> CShapeManager::FindLightestShapeInWater()
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

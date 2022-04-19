#include "ShapeManager.h"
using namespace std::placeholders;

CShapeManager::CShapeManager()
	: m_actionMap({
		{ "Info", bind(&CShapeManager::Info, this, std::placeholders::_1) },
		{ "Sphere", bind(&CShapeManager::SetSphereToCollection, this, std::placeholders::_1) },
		{ "Parallelepiped", bind(&CShapeManager::SetParallelepipedToCollection, this, std::placeholders::_1) },
	})
{
}

void CShapeManager::InitShapeManager()
{
	PrintUsageInfo();
	std::cout << ">>";

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string action;
		strm >> action;

		auto it = m_actionMap.find(action);
		if (it != m_actionMap.end())
		{
			it->second(strm);
		}
		else
		{
			std::cout << "Unknown command!" << std::endl;
		}

		std::cout << "\n>>";
	}
}

bool CShapeManager::Info([[maybe_unused]] std::istream&)
{
	for (auto p : m_shapeCollection)
	{
		std::cout << p->ToString() << std::endl;
	}
	return true;
}

void CShapeManager::PrintUsageInfo()
{
	std::cout << "Usage:\n"
			  << "\tEnter shapes with [parameters]. [Parameters] are numbers\n\n"
			  << "\tSolid shapes:\n"
			  << "\t\tSphere [density] [radius]\n"
			  << "\t\tParallelepiped [density] [width] [height] [depth]\n"
			  << "\t\tCone [density] [base radius] [height]\n"
			  << "\t\tCylinder [density] [base radius] [height]\n\n";
}

std::optional<double> CShapeManager::ParseDensity(std::istream& args)
{
	double density;
	args >> density;

	if (!args)
	{
		std::cout << "Density is not number" << std::endl;
		return std::nullopt;
	}

	if (density == 0)
	{
		std::cout << "Density can not be zero" << std::endl;
		return std::nullopt;
	}
	return density;
}

bool CShapeManager::SetSphereToCollection(std::istream& args)
{
	auto density = ParseDensity(args);
	if (!density)
	{
		return false;
	}

	double radius;
	if (!(args >> radius))
	{
		std::cout << "Radius is not number" << std::endl;
		return false;
	}

	if (radius <= 0)
	{
		std::cout << "Radius must be greater then 0" << std::endl;
		return false;
	}

	auto sphere = std::make_shared<CSphere>(*density, radius);
	m_shapeCollection.push_back(sphere);

	return true;
}

bool CShapeManager::SetParallelepipedToCollection(std::istream& args)
{
	auto density = ParseDensity(args);
	if (!density)
	{
		return false;
	}

	double width;
	double height;
	double depth;
	if (!(args >> width >> height >> depth))
	{
		std::cout << "Width or height or depth is not number" << std::endl;
		return false;
	}

	if (width <= 0 || height <= 0 || depth <= 0)
	{
		std::cout << "width, height and depth must be greater then 0" << std::endl;
		return false;
	}

	auto sphere = std::make_shared<CParalellepiped>(*density, width, height, depth);
	m_shapeCollection.push_back(sphere);

	return true;
}

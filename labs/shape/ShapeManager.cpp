#include "ShapeManager.h"
using namespace std::placeholders;

CShapeManager::CShapeManager()
	: m_actionMap({
		{ "Info", bind(&CShapeManager::Info, this, std::placeholders::_1) },
		{ "Sphere", bind(&CShapeManager::SetSphereToCollection, this, std::placeholders::_1) },
		{ "Parallelepiped", bind(&CShapeManager::SetParallelepipedToCollection, this, std::placeholders::_1) },
		{ "Cone", bind(&CShapeManager::SetConeToCollection, this, std::placeholders::_1) },
		{ "Cylinder", bind(&CShapeManager::SetCylinderToCollection, this, std::placeholders::_1) },
	})
{
}
//вынести парсер в отдельный класс
// передавать парсер по ссылке при создании менеджера

// хранение вектора в отдельном классе
// переименоват appManager
//выисление макс массы моно вынести в отдельную функции в утилитиы или вычислять там где хранится вектор, может нет
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
			  << "\tEnter shapes with [parameters]. [Parameters] must be numbers.\n\n"
			  << "\tSolid shapes:\n"
			  << "\t\tSphere [density] [radius]\n"
			  << "\t\tParallelepiped [density] [width] [height] [depth]\n"
			  << "\t\tCone [density] [base radius] [height]\n"
			  << "\t\tCylinder [density] [base radius] [height]\n\n"
			  << "\tCommands:\n"
			  << "\t\tInfo - get information about shapes\n\n";
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

	if (density <= 0)
	{
		std::cout << "Density can not be zero" << std::endl;
		return std::nullopt;
	}
	return density;
}

std::optional<double> CShapeManager::ParseBaseRadius(std::istream& args)
{
	double baseRadius;
	args >> baseRadius;

	if (!args)
	{
		std::cout << "BaseRadius are not number" << std::endl;
		return std::nullopt;
	}

	if (baseRadius <= 0)
	{
		std::cout << "BaseRadius must be greater then 0" << std::endl;
		return std::nullopt;
	}

	return baseRadius;
}

std::optional<double> CShapeManager::ParseHeight(std::istream& args)
{
	double height;
	args >> height;
	if (!args)
	{
		std::cout << "Height are not number" << std::endl;
		return std::nullopt;
	}

	if (height <= 0)
	{
		std::cout << "Height must be greater then 0" << std::endl;
		return std::nullopt;
	}

	return height;
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
		std::cout << "Width or height or depth are not number" << std::endl;
		return false;
	}

	if (width <= 0 || height <= 0 || depth <= 0)
	{
		std::cout << "Width, height and depth must be greater then 0" << std::endl;
		return false;
	}

	auto paralellepiped = std::make_shared<CParalellepiped>(*density, width, height, depth);
	m_shapeCollection.push_back(paralellepiped);

	return true;
}

bool CShapeManager::SetConeToCollection(std::istream& args)
{
	auto density = ParseDensity(args);
	auto baseRadius = ParseBaseRadius(args);
	auto height = ParseHeight(args);
	if (!density || !baseRadius || !height)
	{
		return false;
	}

	auto cone = std::make_shared<CCone>(*density, *baseRadius, *height);
	m_shapeCollection.push_back(cone);

	return true;
}

bool CShapeManager::SetCylinderToCollection(std::istream& args)
{
	auto density = ParseDensity(args);
	auto baseRadius = ParseBaseRadius(args);
	auto height = ParseHeight(args);
	if (!density || !baseRadius || !height)
	{
		return false;
	}

	auto cone = std::make_shared<CCylinder>(*density, *baseRadius, *height);
	m_shapeCollection.push_back(cone);

	return true;
}

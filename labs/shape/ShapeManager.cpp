#include "ShapeManager.h"
using namespace std::placeholders;

CShapeManager::CShapeManager()
	: m_actionMap({
		{ "Info", bind(&CShapeManager::Info, this, std::placeholders::_1) },
		{ "Sphere", bind(&CShapeManager::SetSphereToCollection, this, std::placeholders::_1) },
	})
{
}

void CShapeManager::InitShapeManager()
{
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
	std::cout << "information" << std::endl;
	return true;
}

bool CShapeManager::SetSphereToCollection(std::istream& args)
{
	double radius;
	args >> radius;

	if (!args)
	{
		std::cout << "Radius is not number" << std::endl;
		return false;
	}

	if (radius == 0)
	{
		std::cout << "Radius can not be zero" << std::endl;
		return false;
	}
	std::cout << radius << std::endl;

	return true;
}

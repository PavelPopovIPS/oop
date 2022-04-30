#include "Looper.h"
using namespace std::placeholders;

CLooper::CLooper(CShapeFactory& shapeFactory, CShapeManager& shapeManager)
	: m_shapeFactory(shapeFactory)
	, m_shapeManager(shapeManager)
	, m_commonActionMap({
		  { "Info", bind(&CShapeManager::PrintInfo, &m_shapeManager, std::placeholders::_1) },
		  { "HeaviestShape", bind(&CShapeManager::PrintHeaviestShapeInfo, &m_shapeManager, std::placeholders::_1) },
		  { "LightestShapeInWater", bind(&CShapeManager::PrintLightestShapeInfo, &m_shapeManager, std::placeholders::_1) },
	  })
	, m_createShapeActionMap({
		  { "Sphere", bind(&CShapeFactory::CreateSphere, m_shapeFactory, std::placeholders::_1) },
		  { "Parallelepiped", bind(&CShapeFactory::CreateParallelepiped, m_shapeFactory, std::placeholders::_1) },
		  { "Cone", bind(&CShapeFactory::CreateCone, m_shapeFactory, std::placeholders::_1) },
		  { "Cylinder", bind(&CShapeFactory::CreateCylinder, m_shapeFactory, std::placeholders::_1) },
		  { "CompoundStart", bind(&CLooper::InitCompoundShapeLooper, this, std::placeholders::_1) },
	  })
{
}

void CLooper::Init()
{
	PrintUsageInfo();

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string action;
		strm >> action;

		if (IsCommonAction(action, strm))
		{
			auto commonActionIterator = m_commonActionMap.find(action);
			commonActionIterator->second(strm);
		}

		if (IsCreateShapeAction(action, strm))
		{
			try
			{
				auto createShapeActionIterator = m_createShapeActionMap.find(action);
				m_shapeManager.AddShape(createShapeActionIterator->second(strm));
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		if (!IsCommonAction(action, strm) && !IsCreateShapeAction(action, strm))
		{
			std::cout << "Unknown command!" << std::endl;
		}

		std::cout << "\n>>";
	}
}

bool CLooper::IsCommonAction(const std::string& action, std::istream& args)
{
	auto commonActionIterator = m_commonActionMap.find(action);
	if (commonActionIterator != m_commonActionMap.end())
	{
		return true;
	}
	return false;
}

bool CLooper::IsCreateShapeAction(const std::string& action, std::istream& args)
{
	auto commonActionIterator = m_createShapeActionMap.find(action);
	if (commonActionIterator != m_createShapeActionMap.end())
	{
		return true;
	}
	return false;
}

std::shared_ptr<CBody> CLooper::InitCompoundShapeLooper([[maybe_unused]] std::istream& args)
{
	std::cout << "Add shapes or CompoundEnd for close compound shape\n\n"
			  << ">>";

	std::shared_ptr<CCompound> compoundShape = m_shapeFactory.CreateCompoundShape();

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string action;
		strm >> action;

		if (IsCompoundEndAction(action, compoundShape))
		{
			return compoundShape;
		}

		if (IsCreateShapeAction(action, strm))
		{
			try
			{
				auto createShapeActionIterator = m_createShapeActionMap.find(action);
				compoundShape->AddChildBody(createShapeActionIterator->second(strm));
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		if (!IsCreateShapeAction(action, strm) && !IsCompoundEndAction(action, compoundShape))
		{
			std::cout << "Unknown command! Add shapes or CompoundEnd for close compound shape" << std::endl;
		}

		std::cout << "\n>>";
	}

	return compoundShape;
}

bool CLooper::IsCompoundEndAction(const std::string& action, std::shared_ptr<CCompound>& compoundShape)
{
	if (action == "CompoundEnd")
	{
		if (compoundShape->IsEmpty())
		{
			throw std::runtime_error("Compound Shape was not created. It should contain one or more solid shapes");
		}

		std::cout << "Compound Shape was created" << std::endl;
		return true;
	}
	return false;
}

void CLooper::PrintUsageInfo()
{
	std::cout << "Usage:\n"
			  << "\tEnter shapes with [parameters]. [Parameters] must be numbers.\n\n"
			  << "\tSolid shapes:\n"
			  << "\t\tSphere [density] [radius]\n"
			  << "\t\tParallelepiped [density] [width] [height] [depth]\n"
			  << "\t\tCone [density] [base radius] [height]\n"
			  << "\t\tCylinder [density] [base radius] [height]\n\n"
			  << "\tCompound shapes:\n"
			  << "\t\tCompoundStart\n"
			  << "\t\t\tAdd solid and compound shapes\n"
			  << "\t\tCompoundEnd\n\n"
			  << "\tCommands:\n"
			  << "\t\tInfo - get information about shapes\n"
			  << "\t\tHeaviestShape - print heaviest shape\n"
			  << "\t\tLightestShapeInWater - print lightest shape in water\n\n"
			  << ">>";
}

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
	  })
{
}

void CLooper::Init()
{
	PrintUsageInfo();

	std::cout << ">>";

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string action;
		strm >> action;

		bool stateCommonAction = FindCommonAction(action, strm);
		std::shared_ptr<CBody> p_shape = FindCreateShapeAction(action, strm);

		if (p_shape != nullptr)
		{
			m_shapeManager.AddShape(p_shape);
		}

		if (!stateCommonAction && !p_shape)
		{
			std::cout << "Unknown command!" << std::endl;
		}

		std::cout << "\n>>";
	}
}

std::shared_ptr<CBody> CLooper::InitCompoundShapeLooper()
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

		std::shared_ptr<CBody> p_shape = FindCreateShapeAction(action, strm);

		if (p_shape != nullptr)
		{
			compoundShape->AddChildBody(p_shape);
		}

		if (action == "CompoundEnd")
		{
			if (compoundShape->IsEmpty())
			{
				throw std::runtime_error("Compound Shape was not created. Id should contain one or more solid shapes");
			}

			std::cout << "Compound Shape was created" << std::endl;
			return compoundShape;
		}

		if (!p_shape && action != "CompoundEnd")
		{
			std::cout << "Unknown command! Add shapes or CompoundEnd for close compound shape" << std::endl;
		}

		std::cout << "\n>>";
	}

	return compoundShape;
}

bool CLooper::FindCommonAction(const std::string& action, std::istream& args)
{
	auto commonActionIterator = m_commonActionMap.find(action);
	if (commonActionIterator != m_commonActionMap.end())
	{
		commonActionIterator->second(args);
		return true;
	}
	return false;
}

std::shared_ptr<CBody> CLooper::FindCreateShapeAction(const std::string& action, std::istream& args)
{
	std::shared_ptr<CBody> p_shape;
	auto createShapeActionIterator = m_createShapeActionMap.find(action);
	try
	{
		if (createShapeActionIterator != m_createShapeActionMap.end())
		{
			return createShapeActionIterator->second(args);
		}

		if (action == "CompoundStart")
		{
			return InitCompoundShapeLooper();
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return nullptr;
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
			  << "\t\tLightestShapeInWater - print lightest shape in water\n\n";
}

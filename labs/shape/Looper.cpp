#include "Looper.h"
using namespace std::placeholders;

CLooper::CLooper(CShapeFactory& shapeFactory, CShapeManager& manager)
	: m_shapeFactory(shapeFactory)
	, m_shapeManager(manager)
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

		auto commonActionIterator = m_commonActionMap.find(action);
		if (commonActionIterator != m_commonActionMap.end())
		{
			commonActionIterator->second(strm);
		}

		std::optional<std::shared_ptr<CBody>> shape;

		try
		{
			auto createShapeActionIterator = m_createShapeActionMap.find(action);

			if (createShapeActionIterator != m_createShapeActionMap.end())
			{
				std::shared_ptr<CBody> shape = createShapeActionIterator->second(strm);
				m_shapeManager.AddShape(shape);
			}

			if (action == "CompoundStart")
			{
				std::shared_ptr<CBody> shape = InitCompoundShapeLooper();
				m_shapeManager.AddShape(shape);
			}

			if (commonActionIterator == m_commonActionMap.end()
				&& createShapeActionIterator == m_createShapeActionMap.end()
				&& action != "CompoundStart")
			{
				std::cout << "Unknown command!" << std::endl;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		std::cout << "\n>>";
	}
}

std::shared_ptr<CBody> CLooper::InitCompoundShapeLooper()
{
	std::shared_ptr<CCompound> compoundShape = std::make_shared<CCompound>();

	std::cout << "Add shapes or CompoundEnd for close compound shape\n\n"
			  << ">>";

	// попробовать перенести цикл в лупер, сделать его дочерним от родительского
	// разделить метод на меньшие функции
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string action;
		strm >> action;

		auto createShapeActionIterator = m_createShapeActionMap.find(action);
		if (createShapeActionIterator != m_createShapeActionMap.end())
		{
			try
			{
				std::shared_ptr<CBody> shape = createShapeActionIterator->second(strm);
				compoundShape->AddChildBody(shape);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		if (action == "CompoundStart")
		{
			try
			{
				std::shared_ptr<CBody> shape = InitCompoundShapeLooper();
				compoundShape->AddChildBody(shape);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
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

		if (createShapeActionIterator == m_createShapeActionMap.end() && action != "CompoundStart")
		{
			std::cout << "Unknown command! Add shapes or CompoundEnd for close compound shape" << std::endl;
		}

		std::cout << "\n>>";
	}
	return compoundShape;
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

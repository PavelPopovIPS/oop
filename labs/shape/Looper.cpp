#include "Looper.h"
using namespace std::placeholders;

CLooper::CLooper(CParser& parser, CShapeManager& manager)
	: m_parser(parser)
	, m_shapeManager(manager)
	, m_commonActionMap({
		  { "Info", bind(&CShapeManager::PrintInfo, &m_shapeManager, std::placeholders::_1) },
		  { "HeaviestShape", bind(&CShapeManager::PrintHeaviestShapeInfo, &m_shapeManager, std::placeholders::_1) },
		  { "LightestShapeInWater", bind(&CShapeManager::PrintLightestShapeInfo, &m_shapeManager, std::placeholders::_1) },
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

		auto itCommonAction = m_commonActionMap.find(action);
		if (itCommonAction != m_commonActionMap.end())
		{
			itCommonAction->second(strm);
		}

		std::optional<std::shared_ptr<CBody>> shape;

		try
		{
			shape = m_parser.ParseShape(action, strm);
			if (shape)
			{
				m_shapeManager.AddShape(*shape);
			}

			if (itCommonAction == m_commonActionMap.end() && !shape)
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

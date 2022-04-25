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
	, m_parseShapeActionMap({
		  { "Sphere", bind(&CParser::ParseSphere, m_parser, std::placeholders::_1) },
		  { "Parallelepiped", bind(&CParser::ParseParallelepiped, m_parser, std::placeholders::_1) },
		  { "Cone", bind(&CParser::ParseCone, m_parser, std::placeholders::_1) },
		  { "Cylinder", bind(&CParser::ParseCylinder, m_parser, std::placeholders::_1) },
		  { "CompoundStart", bind(&CLooper::ParseCompoundShapeInfo, this, std::placeholders::_1) },
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

		auto itShapeAction = m_parseShapeActionMap.find(action);
		if (itShapeAction != m_parseShapeActionMap.end())
		{
			std::shared_ptr<CBody> shape = itShapeAction->second(strm);
			m_shapeManager.AddShape(shape);
		}

		if (itCommonAction == m_commonActionMap.end() && itShapeAction == m_parseShapeActionMap.end())
		{
			std::cout << "Unknown command!" << std::endl;
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

std::shared_ptr<CBody> CLooper::ParseCompoundShapeInfo(std::istream& args)
{
	std::shared_ptr<CCompound> compoundShape = std::make_shared<CCompound>();

	std::cout << "Add shapes or CompoundEnd for close compound shape" << std::endl;
	std::cout << ">>";

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string action;
		strm >> action;

		if (action == "CompoundStart")
		{
			ParseCompoundShapeInfo(strm);
		}

		auto itShapeAction = m_parseShapeActionMap.find(action);
		if (itShapeAction != m_parseShapeActionMap.end())
		{
			std::shared_ptr<CBody> shape = itShapeAction->second(strm);
			compoundShape->AddChildBody(shape);
		}

		if (action == "CompoundEnd")
		{
			std::cout << "Compound Shape was created" << std::endl;
			break;
		}

		if (itShapeAction == m_parseShapeActionMap.end())
		{
			std::cout << "Unknown command! Add shapes or CompoundEnd for close compound shape" << std::endl;
		}

		std::cout << "\n>>";
	}
	return compoundShape;
}

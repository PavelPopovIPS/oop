#include "Looper.h"
using namespace std::placeholders;

CLooper::CLooper(CParser& parser, CShapeManager& manager)
	: m_parser(parser)
	, m_shapeManager(manager)
	, m_commonActionMap({
		  { "Info", bind(&CShapeManager::PrintInfo, m_shapeManager, std::placeholders::_1) },
		  { "HeaviestShape", bind(&CShapeManager::PrintHeaviestShapeInfo, m_shapeManager, std::placeholders::_1) },
		  { "LightestShapeInWater", bind(&CShapeManager::PrintLightestShapeInfo, m_shapeManager, std::placeholders::_1) },
		  { "CompoundStart", bind(&CLooper::ReadCompoundShapeInfo, this, std::placeholders::_1) },
	  })
	, m_parseShapeActionMap({
		  { "Sphere", bind(&CParser::ParseSphere, m_parser, std::placeholders::_1) },
		  { "Parallelepiped", bind(&CParser::ParseParallelepiped, m_parser, std::placeholders::_1) },
		  { "Cone", bind(&CParser::ParseCone, m_parser, std::placeholders::_1) },
		  { "Cylinder", bind(&CParser::ParseCylinder, m_parser, std::placeholders::_1) },
	  })
{
}
//вынести парсер в отдельный класс и передавать парсер по ссылке при создании менеджера
// хранение вектора в отдельном классе
// переименоват в appManager или looper
// вычисление макс массы можно вынести в отдельную функции в утилитиы или вычислять там где хранится вектор, может нет

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

		auto it = m_commonActionMap.find(action);
		if (it != m_commonActionMap.end())
		{
			it->second(strm);
		}

		auto it2 = m_parseShapeActionMap.find(action);
		if (it2 != m_parseShapeActionMap.end())
		{
			it2->second(strm);
		}
		else
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

bool CLooper::ReadCompoundShapeInfo(std::istream& args)
{
	auto compoundShape = std::make_shared<CCompound>();

	double density = 1;
	double radius = 2;
	auto sphere = std::make_shared<CSphere>(density, radius);
	compoundShape->AddChildBody(sphere);
	m_shapeManager.AddShape(compoundShape);
	return true;
}

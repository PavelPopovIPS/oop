#include "Parser.h"

CParser::CParser()
	: m_parseShapeActionMap({
		{ "Sphere", bind(&CParser::ParseSphere, this, std::placeholders::_1) },
		{ "Parallelepiped", bind(&CParser::ParseParallelepiped, this, std::placeholders::_1) },
		{ "Cone", bind(&CParser::ParseCone, this, std::placeholders::_1) },
		{ "Cylinder", bind(&CParser::ParseCylinder, this, std::placeholders::_1) },
	})
{
}

std::optional<std::shared_ptr<CBody>> CParser::ParseShape(std::string& parseShapeAction, std::istream& args)
{
	auto itShapeAction = m_parseShapeActionMap.find(parseShapeAction);

	if (itShapeAction != m_parseShapeActionMap.end())
	{
		std::shared_ptr<CBody> shape = itShapeAction->second(args);
		return shape;
	}

	if (parseShapeAction == "CompoundStart")
	{
		std::shared_ptr<CBody> shape = ParseCompoundShape();
		return shape;
	}

	return std::nullopt; // Unknown command!
}

std::shared_ptr<CBody> CParser::ParseSphere(std::istream& args)
{
	double density = ParseDensity(args);

	double radius;
	if (!(args >> radius))
	{
		throw std::runtime_error("Radius is not number\n");
	}

	if (radius <= 0)
	{
		throw std::runtime_error("Radius must be greater then 0\n");
	}

	std::cout << "Sphere was created" << std::endl;
	return std::make_shared<CSphere>(density, radius);
}

std::shared_ptr<CBody> CParser::ParseParallelepiped(std::istream& args)
{
	double density = ParseDensity(args);
	double width;
	double height;
	double depth;
	if (!(args >> width >> height >> depth))
	{
		throw std::runtime_error("Width or height or depth are not number\n");
	}

	if (width <= 0 || height <= 0 || depth <= 0)
	{
		throw std::runtime_error("Width, height and depth must be greater then 0\n");
	}

	std::cout << "Parallelepiped was created" << std::endl;
	return std::make_shared<CParalellepiped>(density, width, height, depth);
}

std::shared_ptr<CBody> CParser::ParseCone(std::istream& args)
{
	double density = ParseDensity(args);
	double baseRadius = ParseBaseRadius(args);
	double height = ParseHeight(args);

	std::cout << "Cone was created" << std::endl;
	return std::make_shared<CCone>(density, baseRadius, height);
}

std::shared_ptr<CBody> CParser::ParseCylinder(std::istream& args)
{
	double density = ParseDensity(args);
	double baseRadius = ParseBaseRadius(args);
	double height = ParseHeight(args);

	std::cout << "Cylinder was created" << std::endl;
	return std::make_shared<CCylinder>(density, baseRadius, height);
}

double CParser::ParseDensity(std::istream& args)
{
	double density;
	args >> density;

	if (!args)
	{
		throw std::runtime_error("CParser is not number\n");
	}

	if (density <= 0)
	{
		throw std::runtime_error("Density can not be zero\n");
	}

	return density;
}

double CParser::ParseBaseRadius(std::istream& args)
{
	double baseRadius;
	args >> baseRadius;

	if (!args)
	{
		throw std::runtime_error("BaseRadius are not number\n");
	}

	if (baseRadius <= 0)
	{
		throw std::runtime_error("BaseRadius must be greater then 0\n");
	}

	return baseRadius;
}

double CParser::ParseHeight(std::istream& args)
{
	double height;
	args >> height;
	if (!args)
	{
		throw std::runtime_error("Height are not number\n");
	}

	if (height <= 0)
	{
		throw std::runtime_error("Height must be greater then 0\n");
	}

	return height;
}

std::shared_ptr<CBody> CParser::ParseCompoundShape()
{
	std::shared_ptr<CCompound> compoundShape = std::make_shared<CCompound>();
	std::cout << "Add shapes or CompoundEnd for close compound shape\n\n"
			  << ">>";

	std::string line;
	while (std::getline(std::cin, line))
	{
		std::istringstream strm(line);

		std::string parseShapeAction;
		strm >> parseShapeAction;

		auto itShapeAction = m_parseShapeActionMap.find(parseShapeAction);
		if (itShapeAction != m_parseShapeActionMap.end())
		{
			std::shared_ptr<CBody> shape;
			try
			{
				shape = itShapeAction->second(strm);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
				continue;
			}

			compoundShape->AddChildBody(shape);
		}

		if (parseShapeAction == "CompoundStart")
		{
			std::shared_ptr<CBody> shape = ParseCompoundShape();
			compoundShape->AddChildBody(shape);
		}

		if (parseShapeAction == "CompoundEnd")
		{
			std::cout << "Compound Shape was created" << std::endl;
			return compoundShape;
		}

		if (itShapeAction == m_parseShapeActionMap.end() && parseShapeAction != "CompoundStart")
		{
			std::cout << "Unknown command! Add shapes or CompoundEnd for close compound shape" << std::endl;
		}

		std::cout << "\n>>";
	}

	return compoundShape;
}

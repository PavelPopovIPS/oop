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

	return std::nullopt;
}

std::shared_ptr<CBody> CParser::ParseSphere(std::istream& args)
{
	auto density = ParseDensity(args);
	if (!density)
	{
		// TODO: throw
	}

	double radius;
	if (!(args >> radius))
	{
		std::cout << "Radius is not number" << std::endl;
		// TODO: throw
	}

	if (radius <= 0)
	{
		std::cout << "Radius must be greater then 0" << std::endl;
		// TODO: throw
	}

	return std::make_shared<CSphere>(*density, radius);
}

std::shared_ptr<CBody> CParser::ParseParallelepiped(std::istream& args)
{
	auto density = ParseDensity(args);
	if (!density)
	{
		// TODO: throw
	}

	double width;
	double height;
	double depth;
	if (!(args >> width >> height >> depth))
	{
		// TODO: throw
		std::cout << "Width or height or depth are not number" << std::endl;
	}

	if (width <= 0 || height <= 0 || depth <= 0)
	{
		// TODO: throw
		std::cout << "Width, height and depth must be greater then 0" << std::endl;
	}

	return std::make_shared<CParalellepiped>(*density, width, height, depth);
}

std::shared_ptr<CBody> CParser::ParseCone(std::istream& args)
{
	auto density = ParseDensity(args);
	auto baseRadius = ParseBaseRadius(args);
	auto height = ParseHeight(args);
	if (!density || !baseRadius || !height)
	{
		// TODO: throw
	}

	return std::make_shared<CCone>(*density, *baseRadius, *height);
}

std::shared_ptr<CBody> CParser::ParseCylinder(std::istream& args)
{
	auto density = ParseDensity(args);
	auto baseRadius = ParseBaseRadius(args);
	auto height = ParseHeight(args);
	if (!density || !baseRadius || !height)
	{
		// TODO: throw
	}

	return std::make_shared<CCylinder>(*density, *baseRadius, *height);
}

std::optional<double> CParser::ParseDensity(std::istream& args)
{
	double density;
	args >> density;

	if (!args)
	{
		std::cout << "CParser is not number" << std::endl;
		return std::nullopt;
	}

	if (density <= 0)
	{
		std::cout << "Density can not be zero" << std::endl;
		return std::nullopt;
	}
	return density;
}

std::optional<double> CParser::ParseBaseRadius(std::istream& args)
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

std::optional<double> CParser::ParseHeight(std::istream& args)
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
			std::shared_ptr<CBody> shape = itShapeAction->second(strm);
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
